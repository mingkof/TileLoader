/*!
 * \file TileMatrix.h
 * \author Baldwin
 * \brief ��Ƭ����
 *
 * TODO: long description
 * \date ���� 2015
 * \copyright	Copyright (c) 2015, �������ƺ�ͨ�����Զ����Ƽ����޹�˾\n
	All rights reserved.
 */

#ifndef TILEMATRIX_H__
#define TILEMATRIX_H__
#include <vector>
#include <string>
//#include <CGePoint2d.h>

// emulates mapbox::box2d
class bbox {
public:
	double minx;
	double miny;
	double maxx;
	double maxy;
	bbox(double _minx, double _miny, double _maxx, double _maxy) :
		minx(_minx),
		miny(_miny),
		maxx(_maxx),
		maxy(_maxy) { }

	double width() const {
		return maxx - minx;
	}

	double height() const {
		return maxy - miny;
	}
};

struct  point2d
{
	double x;
	double y;
};

//�����ܳ� 
//#define   EarthGirth  (40075016.6856)

class TileMatrix
{
	enum
	{
		e_success = 0,
		e_fail,
		e_outofRange,
	};
public:
	TileMatrix(double dbDPI, double dbMetersPerUnit);

	// ID
	std::string m_qsIdentifier;

	// ��ͼ�����߷�ĸ
	double m_dbScaleDenominator;

	// ��ӦTileMatrixSetָ����CRS
	point2d m_ptTopLeftCorner;

	// ��Ƭ��ȣ���λ������
	int m_nTileWidth;

	// ��Ƭ�߶ȣ���λ������
	int m_nTileHeight;

	// ��Ƭ�����ȣ���λ����Ƭ����
	int m_nMatrixWidth;

	// ��Ƭ����߶ȶȣ���λ����Ƭ����
	int m_nMatrixHeight;

	// �����ڲ���������Ϣ
	void improve();

	/// ��λ�������ڵ���Ƭ���к�
	/// ����Ϊ getSupportedCRS �µ�����
	int location(double xCRS, double yCRS, int& nCol, int& nRow) const;

	// CRS ������Ӧ����������
	int CRS2PixelCoordinate(double xCRS, double yCRS, int& xPixel, int& yPixel) const;

	int getTileBBox(int nCol, int nRow, bbox& box);

private:

	TileMatrix();

	// DPI: ÿӢ�����������1Ӣ�� = 0.0254��
	// OGC��׼DPIΪ 90.71��������0.028mm��Ϊһ�����ص������ȣ�
	// ���ͼʹ�ù��ұ�׼�涨��96 DPI���������ӵ�ͼ�淶����
	double m_dbDPI_;

	// CRS �ο�ϵ��һ����λ���ȶ�Ӧ������
	double m_dbMetersPerUnit;

	// ��ӦTileMatrixSetָ����CRS
	point2d m_ptBottomRightCorner_;

	// ÿ�����ش����CRS��λ����
	double m_dbPixelSpan_;

	// CRS (0.0,0.0)��Ӧ����������
	/// �������������ӳ�䵽һ�ŵ�ͼ��,���ĵ����������
	/// �����ĵ�=��γ��(0,0)
	point2d m_ptBitmapOrigo;

	//�����ܳ�
	//#define   EarthGirth  (40075016.6856)
};

#endif // TILEMATRIX_H__
