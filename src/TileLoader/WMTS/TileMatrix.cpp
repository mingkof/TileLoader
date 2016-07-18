#include "TileMatrix.h"


TileMatrix::TileMatrix(double dbDPI, double dbMetersPerUnit)
{
	m_dbDPI_ = dbDPI;
	m_dbMetersPerUnit = dbMetersPerUnit;
}

void TileMatrix::improve()
{
	// һ�����ر�ʾCRS��λ����
	m_dbPixelSpan_ = m_dbScaleDenominator * 0.02540 / m_dbDPI_ / m_dbMetersPerUnit;

	double dbTileSpanX = m_nTileWidth * m_dbPixelSpan_;
	double dbTileSpanY = m_nTileHeight * m_dbPixelSpan_;

	m_ptBottomRightCorner_.x = m_ptTopLeftCorner.x + (dbTileSpanX * m_nMatrixWidth);
	m_ptBottomRightCorner_.y = m_ptTopLeftCorner.y - (dbTileSpanY * m_nMatrixHeight);

	// ����crs(0, 0) ���Ӧ��ͼƬ��������
	// crs�����Ͻǵ��Ӧ��������(0, 0)
	double dbTemp = abs(m_ptTopLeftCorner.x / m_dbPixelSpan_) + 0.5;
	m_ptBitmapOrigo.x = floor( dbTemp );

	dbTemp = abs(m_ptTopLeftCorner.y / m_dbPixelSpan_) + 0.5;
	m_ptBitmapOrigo.y = floor( dbTemp );
}

// �������� ��ֵ������ֵ���������ӷ���
int approach(double dbVal)
{
	if(dbVal < 0)
	{
		return (int)floor( dbVal - 0.5 );
	}
	else
	{
		return (int)floor(dbVal + 0.5 );
	}
}

int TileMatrix::location(double xCRS, double yCRS, int& nCol, int& nRow) const
{
	// ������귶Χ
	if( xCRS < m_ptTopLeftCorner.x || xCRS > m_ptBottomRightCorner_.x ||	
		yCRS < m_ptBottomRightCorner_.y || yCRS > m_ptTopLeftCorner.y)
		return e_outofRange;

	// ���������crs(0,0)�ľ���
	int dbXPixelSpan = approach( (xCRS / m_dbPixelSpan_) );
	int dbYPixelSpan = approach( (yCRS / m_dbPixelSpan_) );

	// ����CRS(xCRS, yCRS) ��Ӧ����������
	// ��������
	int nXPixel = int(m_ptBitmapOrigo.x) + dbXPixelSpan;

	// ��Ϊ��������ϵ��CRS����ϵ��Y�᷽���෴����������ϵY������Ϊ������CRS����ϵY������Ϊ������
	int nYPixel = int(m_ptBitmapOrigo.y) - dbYPixelSpan;

	nCol = nXPixel / m_nTileWidth ;
	nRow = nYPixel / m_nTileHeight;

	return e_success;
}

int TileMatrix::CRS2PixelCoordinate(double xCRS, double yCRS, int& xPixel, int& yPixel) const
{
	// ������귶Χ
	if( xCRS < m_ptTopLeftCorner.x || xCRS > m_ptBottomRightCorner_.x ||	
		yCRS < m_ptBottomRightCorner_.y || yCRS > m_ptTopLeftCorner.y)
		return e_outofRange;

	// ���������crs(0,0)�ľ���
	int dbXPixelSpan = approach( (xCRS / m_dbPixelSpan_) );
	int dbYPixelSpan = approach( (yCRS / m_dbPixelSpan_) );

	// ����CRS(xCRS, yCRS) ��Ӧ����������
	// ��������
	xPixel = int(m_ptBitmapOrigo.x) + dbXPixelSpan;

	// ��Ϊ��������ϵ��CRS����ϵ��Y�᷽���෴����������ϵY������Ϊ������CRS����ϵY������Ϊ������
	yPixel = int(m_ptBitmapOrigo.y) - dbYPixelSpan;

	return e_success;
}

int TileMatrix::getTileBBox(int nCol, int nRow, bbox& box)
{
	// x����Ƭ������
	double dbTileSpanX = m_nTileWidth * m_dbPixelSpan_;

	// y����Ƭ������
	double dbTileSpanY = m_nTileHeight * m_dbPixelSpan_;

	box.minx = m_ptTopLeftCorner.x + nCol * dbTileSpanX;
	box.maxx = box.minx + dbTileSpanX;


	box.maxy = m_ptTopLeftCorner.y - nRow * dbTileSpanY;
	box.miny = m_ptTopLeftCorner.y + dbTileSpanY;
	
	return e_success;
}
