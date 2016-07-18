/*!
 * \file Capabilities.h
 * \author Baldwin
 * \brief һ��WMTS��Capabilities
 *
 * TODO: long description
 * \date ���� 2015
 * \copyright	Copyright (c) 2015, �������ƺ�ͨ�����Զ����Ƽ����޹�˾\n
	All rights reserved.
 */
#ifndef CAPABILITIES_H__
#define CAPABILITIES_H__

#include <map>
#include <string>
#include <memory>
//#include <QMap>
//#include <QString>
//#include <QSharedPointer>

#include "TileMatrixSet.h"

class Capabilities
{
public:
	Capabilities();

	void setIdentifier(const std::string& qsIdentifier);
	std::string getIdentifier();

	// Provider ��

	// layer ��

	// tilematrixset

	/// @pTileMatrixSet ���ϴ����Ķ����緵��Ϊtrue�����߲��ù������������ڣ�����false��Ҫ�����߹�������������
	bool addTileMatrixSet(std::shared_ptr<TileMatrixSet> pTileMatrixSet);

	/// ��ȡ��Ƭ����
	std::shared_ptr<TileMatrixSet> getTileMatrixSet(const std::string& qsIdentifier) const;

	/// ɾ����Ƭ��֤��
	int removeTileMatrixSet(const std::string& qsIdentifier);

private:
	std::string m_qsUrl;
	// ��Ƭ���󼯵ļ���
	std::map<std::string, std::shared_ptr<TileMatrixSet> > m_mpQs2TMS_;
};

#endif // CAPABILITIES_H__