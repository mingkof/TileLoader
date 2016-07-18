/*!
 * \file TileMatrixSet.h
 * \author Baldwin
 * \brief WMTS������Ƭ����
 *
 * TODO: long description
 * \date ���� 2015
 * \copyright	Copyright (c) 2015, �������ƺ�ͨ�����Զ����Ƽ����޹�˾\n
	All rights reserved.
 */
#ifndef TILEMATRIXSET_H__
#define TILEMATRIXSET_H__

//#include <QSharedPointer>
//#include <QVector>
//#include <QMap>
//#include <QString>
#include "TileMatrix.h"

#include <string>
#include <vector>
#include <map>
#include <memory>


class TileMatrixSet
{
	enum
	{
		e_success = 0,
		e_fail
	};
public:
	void setIdentifier(const std::string& qsIdentifier);
	std::string getIdentifier() const;

	void setSupportedCRS(const std::string& qsCRS);
	std::string getSupportedCRS() const;

	/// ����һ����Ƭ��֤��0-success��1-ʧ��
	/// �����Ƕ��ϴ����Ķ�����ӳɹ�������߲���Ҫ��������������
	int addTileMatrix(std::shared_ptr<TileMatrix> spTileMatrix);

	std::shared_ptr<TileMatrix> getTileMatrix(const std::string& qsId) const;

	/// ��λ�������ڵ���Ƭ���к�
	/// ����Ϊ getSupportedCRS �µ�����
	/// @return 0-success 1-fail 2-���겻�ٷ�Χ��
	int location(double xCRS, double yCRS, const std::string& qsTileMatrixIdentifier, int& nCol, int& nRow);

	// ��ȡTileMatrix ����
	int getCount();

	// ��ȡ
	const std::vector< std::shared_ptr<TileMatrix> >& getTileMatries() const;

private:
	// ��ʾ �൱��ID
	std::string m_qsIdentifier_;

	// CRS SRID 
	std::string m_qsSupportedCRS_;

	std::map<std::string, std::shared_ptr<TileMatrix> > m_mpQstr2TileMatrix_;

	std::vector< std::shared_ptr<TileMatrix> > m_vTileMatries;
};

#endif // TILEMATRIXSET_H__