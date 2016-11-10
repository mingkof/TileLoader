#include "Writer.h"
#include "BundleParamDef.h"

// ��׼ c

// 
#include <stdlib.h>
#include <stdio.h>
#include <direct.h>

#include <sstream>

#include <windows.h>

// google 
#include "glog/logging.h"


Writer::Writer()
{
	m_pBundle = nullptr;
	m_pBundlx = nullptr;
	m_tBundleID.nLevel = 0;
	m_tBundleID.nBeginRow = 0;
	m_tBundleID.nBeginCol = 0;
}

Writer::~Writer()
{

}

int Writer::createBundle(const BundleID& tNo, const std::string& sDir)
{
	//�½��ȼ��ļ���
	char szTemp[50] = {0};

	std::string sDirLevel;
	sprintf(szTemp, "L%02d", tNo.nLevel);
	{
		std::stringstream ss;
		ss << sDir << "/" << szTemp;
		sDirLevel = ss.str();
	}

	_mkdir(sDirLevel.c_str());

	sprintf(szTemp, "R%04xC%04x.bundl", tNo.nBeginRow, tNo.nBeginCol);
	
	std::string sBundle="";
	{
		std::stringstream ss;
		ss << sDirLevel << "/" << szTemp << "e";
		sBundle = ss.str();
	}

	std::string sBundlx = "";
	{
		std::stringstream ss;
		ss << sDirLevel << "/" << szTemp << "x";
		sBundlx = ss.str();
	}

	m_pBundlx = fopen(sBundlx.c_str(), "wb+");
	if (!m_pBundlx)
	{
		return R_FAIL;
	}

	const char szBomHead[16] = { 0x03, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00 };
	const char szBomEnd[16] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
	char szBundlxContext[BUNDLX_CONTENT_SIZE];

	for (int i = 0; i < 16384; ++i)
	{
		char* p = szBundlxContext + i*BUNDLX_NODE_SIZE;
		int nTemp = (60 + i * 4);
		memcpy(p, &nTemp, 4);
	}

	fseek(m_pBundlx, 0, SEEK_SET);
	fwrite(szBomHead, sizeof(char), BUNDLX_DOM, m_pBundlx);
	fwrite(szBundlxContext, sizeof(char), BUNDLX_CONTENT_SIZE, m_pBundlx);
	fwrite(szBundlxContext, sizeof(char), BUNDLX_DOM, m_pBundlx);

	m_pBundle = fopen(sBundle.c_str(), "wb+");
	if (!m_pBundle)
		return R_FAIL;
	
	// д���ļ�ͷ�� �ο�http://www.360doc.com/content/15/0711/22/25340375_484316325.shtml
	char szHead[BUNDLE_HEADER_SIZE] = {
		0x03, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x5F, 0x69, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00,

		// ��Ч��Ƭ��										
		0x00, 0x00, 0x00, 0x00,

		0x00, 0x00, 0x00, 0x00,

		// �ļ���С
		0x30, 0x00, 0x00, 0x00,

		0x00, 0x00, 0x00, 0x00,
		0x28, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00,

		// ��ʼ��
		0x00, 0x00, 0x00, 0x00,

		// ������
		0x03, 0x00, 0x00, 0x00,

		// ��ʼ��
		0x00, 0x40, 0x00, 0x00,

		// ������
		0x5F, 0x69, 0x00, 0x00
	};

	int nEndRow = tNo.nBeginRow + 128;
	int nEndCol = tNo.nBeginCol + 128;

	memcpy(szHead + BUNDLE_POS_BEGINROW, &tNo.nBeginRow, INT_SIZE);
	memcpy(szHead + BUNDLE_POS_BEGINCOL, &tNo.nBeginCol, INT_SIZE);
	memcpy(szHead + BUNDLE_POS_ENDROW, &nEndRow, INT_SIZE);
	memcpy(szHead + BUNDLE_POS_ENDCOL, &nEndCol, INT_SIZE);

	fwrite(szHead, sizeof(char), BUNDLE_HEADER_SIZE, m_pBundle);

	// д��յ�ƫ��
	int nOffsets[BUNDLE_MAX_TILE_NUM] = { 0 };
	fwrite((const char*)nOffsets, sizeof(int), BUNDLE_MAX_TILE_NUM, m_pBundle);

	m_tBundleID = tNo;

	return R_SUCCESS;
}

void Writer::close()
{
	fclose(m_pBundlx);
	fclose(m_pBundle);
}

int Writer::writePngToBundle(char* szPng, int nPngSize, const TileID& tTileID, std::string* pErrorMsg)
{
	int nOffset = _writeToBundle(szPng, nPngSize, m_pBundle, pErrorMsg);

	if (R_FAIL == nOffset)
	{
		return R_FAIL;
	}

	// �������
	int nBundleRowIdx = tTileID.row - m_tBundleID.nBeginRow;
	int nBundleColIdx = tTileID.col - m_tBundleID.nBeginCol;

	if ((nBundleRowIdx < 0 || nBundleRowIdx >= 128) || (nBundleColIdx < 0 || nBundleColIdx >= 128))
	{
		*pErrorMsg = "��������";
		
		std::stringstream ss;
		std::string s = ss.str();
		ss << nBundleRowIdx << "," << nBundleColIdx;

		LOG(INFO) << "Խ��row:" << nBundleRowIdx << ",col:" << nBundleColIdx;

		return R_FAIL;
	}

	int nTileInBundleIndex = (nBundleColIdx << 7) + nBundleRowIdx;

	int nPngOffsetInBundlx = nTileInBundleIndex * BUNDLX_NODE_SIZE + BUNDLX_DOM;
	
	fseek(m_pBundlx, nPngOffsetInBundlx, SEEK_SET);

	if (1 != fwrite((const char*)(&nOffset), 5, 1, m_pBundlx))
	{
		LOG(ERROR) << "дbundlx����";
	}

	return R_SUCCESS;
}

std::string Writer::getFileName(const BundleID& tNo, const std::string& sDir) const
{
	//�½��ȼ��ļ���
	char szTemp[50] = { 0 };

	std::string sDirLevel;
	sprintf(szTemp, "L%02d", tNo.nLevel);
	{
		std::stringstream ss;
		ss << sDir << "/" << szTemp;
		sDirLevel = ss.str();
	}

	_mkdir(sDirLevel.c_str());

	sprintf(szTemp, "R%04xC%04x.bundl", tNo.nBeginRow, tNo.nBeginCol);

	std::string sBundle = "";
	{
		std::stringstream ss;
		ss << sDirLevel << "/" << szTemp << "e";
		sBundle = ss.str();
	}

	return sBundle;
}

int Writer::_writeToBundle(char* szPng, int nPngSize, FILE* pFile, std::string* pErrorMsg)
{
	// ���
	if (!pFile)
	{
		if (!pErrorMsg)
			*pErrorMsg = "�ļ�ָ�����";

		return R_FAIL;
	}

	///���ļ�ָ���ƶ��ļ���β
	fseek(pFile, 0, SEEK_END);  

	///�����ǰ�ļ�ָ������ļ���ʼ���ֽ���
	long int nFileSize = ftell(pFile); 

	// ��д���png���ļ��е�ƫ����
	int nOffset = nFileSize;
	
	/// д��png�ļ���С
	int ret_code = fwrite(&nPngSize, sizeof(int), 1, pFile);
	if (ret_code < (int)nPngSize)
	{
		if (ferror(pFile))
		{
			*pErrorMsg = "д�ļ�����";
			return R_FAIL;
		}
	}

	// д��png�ļ�
	ret_code = fwrite(szPng, sizeof(char), nPngSize, pFile);
	if (ret_code < (int)nPngSize)
	{
		if (ferror(pFile))
		{
			*pErrorMsg = "д�ļ�����";
			return R_FAIL;
		}
	}
	
	// �����ļ�ͷ
	int nTemp = 0;

	// ������Ч��Ƭ��
	fseek(pFile, BUNDLE_POS_TILECOUNT, SEEK_SET);
	fread(&nTemp, sizeof(int), 1, pFile);
	++nTemp;
	fseek(pFile, BUNDLE_POS_TILECOUNT, SEEK_SET);
	fwrite((char*)(&nTemp), INT_SIZE, 1, pFile);

	// �����ļ���С
	nTemp = nOffset + INT_SIZE + nPngSize;
	fseek(pFile, BUNDLE_POS_FILESIZE, SEEK_SET);
	fwrite((char*)(&nTemp), INT_SIZE, 1, pFile);

	return nOffset;
}

