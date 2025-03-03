#pragma once
#include "../../Util/common.h"

//�첽������
//��Ʒ�Ϊ���̺߳ͼ����߳�
// ּ�ڼ����߳̽��м����ļ� ���߳���ִ��Link Obj


class AsyncJob
{
public:
	AsyncJob();
	virtual ~AsyncJob() = 0 {};



	enum //����״̬
	{
		JS_NONE,
		JS_FAIL,
		JS_DELETE,
	};

	enum //����״̬
	{
		LS_PENDING,//�ȴ���
		LS_LOADED,//���غ�
		LS_FAIL, // error
	};

	enum // JOB TYPE
	{
		JT_FILE,
		JT_RESOURCE,
		JT_TEXTURE,
		JT_MATERIAL,
		JT_ANIM,
		JT_ACTOR,
		JT_MAP,
		JT_FONT,
	};

	unsigned int m_uiLoadState;
	unsigned m_uiJobState;
	virtual void MainThreadProcess() = 0;
	virtual void AsyncThreadProcess() = 0;
	virtual unsigned int GetJobType() const = 0;
};


class FileJob : public AsyncJob
{
public:

	FileJob(string strFileName);
	virtual ~FileJob() = 0;
	virtual void MainThreadProcess() = 0;
	virtual void AsyncThreadProcess();
	virtual unsigned int GetJobType() const
	{
		return JT_FILE;
	}
	string m_fileName;
protected:
	unsigned char* m_pBuffer;
	unsigned int m_uiSize;
	unsigned int m_resHash;
};
