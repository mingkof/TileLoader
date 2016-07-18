#ifndef PROGRESS_H__
#define PROGRESS_H__
#include <vector>

class Progress
{
public:
	Progress();
	~Progress();

	void setCount(int nCount);

	void setNow(int nNow);
	void addNow(int nAdded);

	// ��ȡ���Ȱٷ�������λ��%��������ֵ������100
	double getProgress();

	void addFail(int nFailed);

	// �ڱ�׼I/O��ʾ������Ϣ
	void Show2STD();

public:
	// ��¼���ɹ�������
	std::vector<void*> m_vecFailData;

private:
	int m_nCount;
	int m_nNow;
	int m_nFailCount;
};

#endif // PROGRESS_H__
