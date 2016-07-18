#ifndef PBFWORK_H__
#define PBFWORK_H___


#include "Work.h"
#include <string>
#include "config.h"

class Progress;

class ExplodeTask : public Work
{
	enum
	{
		R_FAIL = -1,
		R_SUCCESS = 0,
	};

public:
	ExplodeTask(Config* p, Progress* progress);
	~ExplodeTask();

	virtual void* run() override;

public:
	// ��Ƭ�ȼ�
	int m_nLevel;

	// ��ʼ���кţ����������кŵĴ洢
	int m_nRow;
	int m_nCol;

private:
	// ��Դ���Ӵ�ģ��
	std::string m_sUrlTemplate;

	// ��Դ���Ŀ¼
	std::string m_sOutDir;

	Progress* m_pProgress;

};

#endif // PBFWORK_H___