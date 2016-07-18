#include "ExplodeTask.h"
#include "Loader.h"
#include <memory>
#include "config.h"
#include "Loader.h"
#include "Writer.h"
#include "Progress.h"
#include "glog/logging.h"
#include <windows.h>

#include <io.h>
#include <direct.h>

// stl
#include <fstream>

// custom
#include "utiliyapi.h"


ExplodeTask::ExplodeTask(Config* p, Progress* progress):m_sUrlTemplate(p->getResourceUrl()),
	m_sOutDir(p->getOutDir()), m_nLevel(0), m_nCol(0),
	m_nRow(0)
{
	m_pProgress = progress;
}

ExplodeTask::~ExplodeTask()
{

}

void* ExplodeTask::run()
{
	Loader ld;

	std::string sErrMsg;

	std::shared_ptr<Tile> spTile(new Tile);

	std::string sOutFile;
	std::stringstream ss;
	ss << Config::Instance()->getOutDir() << "/" << m_nLevel << "/" << m_nCol;
	checkDestination(ss.str());
		
	ss << "/" << m_nRow << "." <<
		Config::Instance()->getSuffix();

	sOutFile = ss.str();

	bool bSuccess = false;

	long lCurlcode = 200;

	if (R_SUCCESS == ld.loadTile(m_sUrlTemplate, m_nLevel, m_nRow, m_nCol, spTile.get(), lCurlcode))
	{
		std::string sBuffer((char*)(spTile->pData), spTile->nSize);
		std::ofstream streamOutFile(sOutFile, std::ios_base::out | std::ios_base::binary);
		streamOutFile << sBuffer;
		streamOutFile.close();

		bSuccess = true;
	}
	else
	{
		// ����ȡ����ʸ����Ƭֱ��д����־
		if (lCurlcode == 403 || lCurlcode == 404)
		{
			sErrMsg = ld.getUrl(m_sUrlTemplate, m_nLevel, m_nRow, m_nCol);
		}
		else
		{
			int nSeconds = 0;
			while (1)
			{
				if (nSeconds > 10)
				{
					sErrMsg = ld.getUrl(m_sUrlTemplate, m_nLevel, m_nRow, m_nCol);
					break;
				}

				Sleep(1000);
				if (R_SUCCESS == ld.loadTile(m_sUrlTemplate, m_nLevel, m_nRow, m_nCol, spTile.get(), lCurlcode))
				{
					std::string sBuffer((char*)(spTile->pData), spTile->nSize);
					std::ofstream streamOutFile(sOutFile, std::ios_base::out | std::ios_base::binary);
					streamOutFile << sBuffer;
					streamOutFile.close();

					bSuccess = true;
					break;
				}

				if (lCurlcode == 403 || lCurlcode == 404)
				{
					sErrMsg = ld.getUrl(m_sUrlTemplate, m_nLevel, m_nRow, m_nCol);
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

			// дһ��������־
			LOG(ERROR) << "������Ƭʧ��" << sErrMsg;
		}
	}

	spTile->clear();

	return NULL;
}
