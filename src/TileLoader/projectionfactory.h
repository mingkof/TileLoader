#ifndef PROJECTIONFACTORY_H__
#define PROJECTIONFACTORY_H__

#include "projection.h"

// stl
#include <map>
#include <memory>

class ProjectionFactory
{
public:
	ProjectionFactory();
	~ProjectionFactory();

	/// @brief     loadFromJson ��json�ļ�����ͶӰ
	/// @detail    ProjectionFactory::loadFromJson
	/// @param[in] const std::string & sFile json�ļ�
	/// @return    int ���ص�ͶӰ����
	int loadFromJson(const std::string& sFile);

	std::shared_ptr<Projection> getProjection(int nSrid);

	static ProjectionFactory* Instance();
	static void deInstance();

private:
	std::map<int, std::shared_ptr<Projection> > m_mapProjects;

	static ProjectionFactory* _ins;
};

#endif // PROJECTIONFACTORY_H__
