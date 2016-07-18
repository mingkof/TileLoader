#include "BundleTask.h"
#include "Loader.h"
#include <memory>
#include "config.h"
#include "Loader.h"
#include "Writer.h"
#include "Progress.h"
#include "glog/logging.h"
#include <windows.h>

BundleTask::BundleTask(Config* p, Progress* progress):m_sUrlTemplate(p->getResourceUrl()),
	m_sOutDir(p->getOutDir()), m_nLevel(0), m_nDownLoadBeginCol(0),
	m_nDownLoadBeginRow(0), m_nMaxRow(0), m_nMaxCol(0)
{
	m_pProgress = progress;
}

BundleTask::~BundleTask()
{

}

void* BundleTask::run()
{
	Loader ld;

	Writer wt;
	BundleID tID;
	tID.nLevel = m_nLevel;

	// ȥ��128������
	tID.nBeginCol = (m_nDownLoadBeginCol >> 7) << 7;
	tID.nBeginRow = (m_nDownLoadBeginRow >> 7) << 7;

	wt.createBundle(tID, m_sOutDir);

	std::string sErrMsg;

	std::shared_ptr<Tile> spTile(new Tile);

	bool bSuccess = false;
	long lCurlcode = 200;
	for (int i = m_nDownLoadBeginCol; i < m_nMaxCol; ++i)
	{
		for (int j = m_nDownLoadBeginRow;j < m_nMaxRow; ++j)
		{
			if (R_SUCCESS == ld.loadTile( m_sUrlTemplate, m_nLevel, j, i, spTile.get(), lCurlcode))
			{
				TileID tileID;
				tileID.level = m_nLevel;
				tileID.row = j;
				tileID.col = i;

				if (R_SUCCESS == wt.writePngToBundle(spTile->pData, spTile->nSize, tileID, &sErrMsg))
				{
					bSuccess = true;
				}
				else
				{
					sErrMsg = ld.getUrl(m_sUrlTemplate, m_nLevel, j, i);
				}
			}
			else
			{
				if (lCurlcode == 403 || lCurlcode == 404)
				{
					//LOG(WARNING) << "download tile to file failed(file level row col code)," << wt.getFileName(tID, m_sOutDir) 
					//	<< "," << m_nLevel << "," << j << ","<< i << "," << lCurlcode;

					sErrMsg = ld.getUrl(m_sUrlTemplate, m_nLevel, j, i);
				}
				else
				{
					// �����������˯�������»�ȡ������10���������ȡ������д����־, ��������ȡ����Ƭ
					int nSeconds = 0;
					while (1)
					{
						if (nSeconds > 10)
						{
							sErrMsg = ld.getUrl(m_sUrlTemplate, m_nLevel, j, i);
							break;
						}

						Sleep(1000);
						if (R_SUCCESS == ld.loadTile(m_sUrlTemplate, m_nLevel, j, i, spTile.get(), lCurlcode))
						{
							TileID tileID;
							tileID.level = m_nLevel;
							tileID.row = j;
							tileID.col = i;

							if (R_SUCCESS == wt.writePngToBundle(spTile->pData, spTile->nSize, tileID, &sErrMsg))
							{
								bSuccess = true;
							}
							else
							{
								sErrMsg = ld.getUrl(m_sUrlTemplate, m_nLevel, j, i);
							}

							break;
						}

						++nSeconds;
					}
				}
			}
		
			if (m_pProgress)
			{
				if (bSuccess)
				{
					// �ɹ������ý���
					m_pProgress->addNow(1);
				}
				else
				{
					// ʧ�ܣ����ý��Ȳ���¼ʧ�ܵ�����
					m_pProgress->addFail(1);

					LOG(ERROR) << "��ȡ��Ƭʧ��," << sErrMsg;
				}
			}

			spTile->clear();
		}
	}

	wt.close();

	return NULL;
}
