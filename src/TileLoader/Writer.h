#ifndef THP_BUNDLE_WRITER_H__
#define THP_BUNDLE_WRITER_H__

/// ��׼c
#include <stdio.h>

/// ��׼c++
#include <string>


#include "ParamDef.h"

class Bundle;
/*!
 * \class BundleReader
 *
 * \brief ArcGis ��Ƭ����ѹ���ļ���ȡ��
 * \detail bundle��bundlx������ͬһĿ¼�£��������ļ��������bundle�ļ�����ͬ
 * \author Baldwin
 * \date ���� 2015
 */
class Writer
{
public:

	enum
	{
		R_FAIL = -1,
		R_SUCCESS = 0,
	};
	Writer();
	~Writer();

	// �����ļ������ļ�ʱ����ļ�����
	int createBundle(const BundleID& tNo, const std::string& sDir);

	void close();

	int writePngToBundle(char* szPng, int nPngSize, const TileID& tTileID, std::string* pErrorMsg);

	std::string getFileName(const BundleID& tNo, const std::string& sDir) const;
private:
	/// ����д����Ƭ�� �ļ��е�ƫ��λ��		
	int _writeToBundle(char* szPng, int nPngSize, FILE* pFile, std::string* pErrorMsg);

	FILE* m_pBundle;
	FILE* m_pBundlx;

	BundleID m_tBundleID;
};


#endif // THP_BUNDLE_WRITER_H__
