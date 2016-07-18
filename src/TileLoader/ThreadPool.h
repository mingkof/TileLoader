#ifndef THREADPOOL_H__
#define THREADPOOL_H__

// std
#include <vector>
#include <queue>
#include <memory>

// pthread
#include "pthread/pthread.h"

class Work;
class Slave;
class Progress;

class ThreadPool
{
public:
	ThreadPool(int MaxThreadNum);
	~ThreadPool();

	// �������
	// ������������
	int addWork(Work* pWork);

	// �����߳�
	void activate();

	// �����߳�
	void destory();

	// 
	void waitForFinishAndDestory();

	// �ж��̳߳��Ƿ�����
	bool isDead();

	// ��ȡ����߳���
	int getMaxThreadNumber();

	// ��������߳���
	void setMaxThreadNumber(int num);

	// ���ӿ����߳�
	void addFreeThread(Slave* p);

	// ���ӹ����߳�
	void addBusyThread(Slave* p);

	// 
	/// @brief     doWorking
	/// @detail    ThreadPool::doWorking
	/// @param[in] int * pRemainWorkNum ���ڹ����Ķ�����
	/// @param[in] int * pFreeThreadNum �����߳���
	/// @return    void*
	void* doWorking(int* pRemainWorkNum, int* pFreeThreadNum);

	// Ѳ������
	void* run();

	static Progress* getProgress();

	int getPatrolInterval();

	void kill();

	int getLowerLimit() const
	{
		return m_nLowerLimit;
	}
	void setLowerLimit(int nLimit)
	{
		m_nLowerLimit = nLimit;
	}

	int getUpperLimit() const
	{
		return m_nUpperLimit;
	}
	void setUpperLimit(int nLimit)
	{
		m_nUpperLimit = nLimit;
	}

	void setCond(pthread_cond_t* cond)
	{
		m_pCond = cond;
	}

	int getRemainWork()
	{

	}
private:

	int m_nMaxThreadNum;

	// �����̶߳�����
	pthread_mutex_t m_busyMutex;

	// �����̶߳�����
	pthread_mutex_t m_freeMutex;

	// ��������� 
	pthread_mutex_t m_taskQueueMutex;

	// ���������ź���
	pthread_cond_t m_taskQueueCond;

	std::queue<Slave*> m_queueBusySlave;
	std::queue<Slave*> m_queueFreeSlave;

	// �������
	std::queue< std::shared_ptr<Work> > m_qTasks;

	bool m_bDead;

	bool m_bWaitFinish;

	static int m_nPatrolTime;

	// �̳߳ؿ���ʱ��
	static long long int m_llEmptyTime;

	// ǰһ��Ѳ��ʱ���ֵĴ��ڹ���״̬�߳�
	static int m_nPreWorks;

	// �๤
	pthread_t m_tOverseer;

	// ���ȶ���
	static Progress* m_pProgress;

	// ����ص����������ޣ����������ﵽ����ʱ���ⷢ�Ϳ������������ź�
	int m_nLowerLimit;

	int m_nUpperLimit;

	// ����ﵽ�����Ƕ��ⷢ�͵��ź�
	pthread_cond_t * m_pCond;
};

#endif // ThreadPool_h__

