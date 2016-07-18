#ifndef DISTRIBUTOR_H__
#define DISTRIBUTOR_H__

//stl
#include <vector>
#include <string>

//pthread
#include "pthread/pthread.h"

#include "WMTS/Capabilities.h"

class ThreadPool;

class Distributor
{
public:
	Distributor();
	virtual ~Distributor();

	// ��ʼ�ɷ�����
	virtual void start() = 0;

	// �߳�ִ�к���
	virtual void* run() = 0;


	/// @brief     WMTSGetRowCol
	/// @detail    Distributor::WMTSGetRowCol
	/// @param[in] int nLevel
	/// @param[in] double dbLeft
	/// @param[in] double dbTop
	/// @param[in] double dbRight
	/// @param[in] double dbBottom
	/// @param[in] int & nBeginRow
	/// @param[in] int & nBeginCol
	/// @param[in] int & nMaxRow ����м�1�������ʱ����������ֵ�ǲ������������ӵ�
	/// @param[in] int & nMaxCol ͬ��
	/// @return    bool
	bool WMTSGetRowCol(int nLevel, double dbLeft, double dbTop, double dbRight, double dbBottom,
		int& nBeginRow, int& nBeginCol, int& nMaxRow, int& nMaxCol);

	std::vector<int> *m_pVecLevels;
	double m_dbLeft;
	double m_dbTop;
	double m_dbRight;
	double m_dbBottom;
	ThreadPool *m_pPool;

	// ͶӰ��Ϣ
	std::string m_sTileMatirxSet;

	// Ԫ���ݶ���
	std::shared_ptr<Capabilities> m_spCapabilities;

protected:
	pthread_mutex_t* m_mutex;
	pthread_cond_t* m_cond;

	pthread_t* m_tThreadID;
};

// ����������������̳߳ص��������ޡ����������������
// ������Ƭ����ɢ�ķ�ʽ�洢�ڴ����ϵ����������
class ExplodeDistributor : public Distributor
{
public:
	ExplodeDistributor(std::vector<int>* pVec, ThreadPool* pPool, std::shared_ptr<Capabilities> spCapabilities, const std::string& sTileMatrixSet,
		double dbLeft,double  dbTop,double  dbRight,double  dbBottom);

	~ExplodeDistributor();

	// ��ʼ�ɷ�����
	void start() override;

	// �߳�ִ�к���
	void* run() override;
};

/// @class  BundleDistributor
/// @brief  ���ļ��洢��arcgisѹ����ʽcompact���ļ��� 
/// @author xueye
/// @date   ���� 2016
class BundleDistributor : public Distributor
{
public:
	BundleDistributor(std::vector<int>* pVec, ThreadPool* pPool, std::shared_ptr<Capabilities> spCapabilities, const std::string& sTileMatrixSet,
		double dbLeft, double  dbTop, double  dbRight, double  dbBottom);

	~BundleDistributor();

	// ��ʼ�ɷ�����
	void start() override;

	// �߳�ִ�к���
	void* run() override;
};





#endif // #define DISTRIBUTOR_H__

