#ifndef PROJECTION_H__
#define PROJECTION_H__

// stl
#include <string>

class  Projection
{
public:
	 Projection(int nSrid, const std::string& sAuthName, int nAuthSrid, const std::string& sProj4Text, const std::string& sRefSysName);
	~Projection();

	/// @brief     trans ����ͶӰ
	/// @detail    Projection::trans ֻ֧����ͬ��׼��֮������ϵ��ͶӰ�任����γ�ȱ�����С����ʽ�Ķ�
	/// @param[in] int nSrid  Ŀ��ͶӰSrid
	/// @param[in] double dbPts ͶӰ�ĵ㼯����γ��������С����ʽ�Ķ�,��ά������ x,y,x,y...
	/// @param[in] int nCount ������
	/// @return    bool ͶӰ�ɹ�
	bool trans(int nSrid, double * dbPts, int nCount);

	const std::string& getPro4text() const
	{
		return m_sProj4text;
	}

	int getSRID() const
	{
		return m_nSrid;
	}
private:
	Projection();

	int m_nSrid;
	std::string m_sAuthName;
	int m_nAuthSrid;
	std::string m_sRefSysName;
	std::string m_sProj4text;
};

#endif // PROJECTION_H__
