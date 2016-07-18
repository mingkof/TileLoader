#ifndef THREAD_H__
#define THREAD_H__

// std
#include <memory>

//
#include "pthread/pthread.h"

/// һ���������߳�
class Work;
class ThreadPool;
class Slave
{
public:
	Slave(ThreadPool* pool);
	~Slave();

	// ����ū��
	void Discipline();

	// �ɷ�����
	void distribute(std::shared_ptr<Work> task);

	// �ɻ�
	void notify();

	// ��Ϣ
	void wait();

	// ������ж���
	void rest();

	// �ж��Ƿ�����
	bool isDead();

	int getID();

	void join();

	void kill();

private:
	static void* doWorking(void* p);

	std::shared_ptr<Work> m_spWork;
	ThreadPool* m_pThreadPool;

	// 
	pthread_t m_thread;



	int m_nID;

	// ������
	pthread_mutex_t		m_Mutex;

	// �ȴ�����
	pthread_cond_t		m_cond;

	bool m_bDead;

	void lock();
	void unlock();
};

#endif // THREAD_H__