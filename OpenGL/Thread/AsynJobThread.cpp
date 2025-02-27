#include "AsynJobThread.h"
AsynJobThread::AsynJobThread()
{
	m_pResourceQueue.empty();
}

AsynJobThread::~AsynJobThread()
{
	m_pResourceQueue.empty();
}

void AsynJobThread::SafeAddJob(AsyncJob* job)
{
	m_pResourceQueue.push(job);
	if (m_pResourceQueue.size() != 0)
		Start();
}

void AsynJobThread::Run()
{
	while (!IsStopTrigger())
	{
		while (m_pResourceQueue.size() != 0)
		{
			AsyncJob* pJob = NULL;
			m_pResourceQueue.pop(pJob);
			pJob->AsyncThreadProcess();
		}
	}

}

string AsynJobThread::GetThreadName()const
{
	return "AsynJobThread";
}