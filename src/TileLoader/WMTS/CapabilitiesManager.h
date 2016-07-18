#ifndef CAPABILITIESMANAGER_H__
#define CAPABILITIESMANAGER_H__
#include <QMap>
#include <QString>
#include <QSharedPointer>
#include "TileMatrixSet.h"
#include <CSingleton.h>
#include "Capabilities.h"

class CapabilitiesManager;

class CapabilitiesManager
{
public:
	DECLARE_SINGLETON(CapabilitiesManager);

	/// @pTileMatrixSet ���ϴ����Ķ����緵��Ϊtrue�����߲��ù������������ڣ�����false��Ҫ�����߹�������������
	bool addCapabilities(QSharedPointer<Capabilities> spCapabilities);

	/// ��ȡ
	QSharedPointer<Capabilities> getCapabilities(const QString& qsIdentifier) const;

	/// ɾ��
	int removeCapabilities(const QString& qsIdentifier);

private:
	// ��Ƭ��֤���ļ���
	QMap<QString, QSharedPointer<Capabilities> > m_mpQStr2Capabilites;
};


#endif // CAPABILITIESMANAGER_H__
