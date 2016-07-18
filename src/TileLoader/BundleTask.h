#ifndef GENERALWORK_H__
#define GENERALWORK_H__


#include "Work.h"
#include <string>
#include "config.h"

class Progress;

class BundleTask : public Work
{
	enum
	{
		R_FAIL = -1,
		R_SUCCESS = 0,
	};

public:
	BundleTask(Config* p, Progress* progress);
	~BundleTask();

	virtual void* run() override;

public:
	// ��Ƭ�ȼ�
	int m_nLevel;

	// ��ʼ���кţ����������кŵĴ洢
	int m_nDownLoadBeginRow;
	int m_nDownLoadBeginCol;

	// ����С��������е���Ƭ���������������
	int m_nMaxRow;
	int m_nMaxCol;

private:
	// ��Դ���Ӵ�ģ��
	std::string m_sUrlTemplate;

	// ��Դ���Ŀ¼
	std::string m_sOutDir;

	Progress* m_pProgress;

};

#endif // generalwork_h__