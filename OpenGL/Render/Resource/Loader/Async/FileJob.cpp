#include "FileJob.h"
#include <filesystem>
AsyncJob::AsyncJob()
{
    m_uiLoadState = LS_PENDING;
    m_uiJobState = JS_NONE;
}
//AsyncJob::~AsyncJob()
//{
//}

FileJob::FileJob(string strFileName) :
    ::AsyncJob(),
    m_fileName(strFileName),
    m_resHash(SID(m_fileName)),
	m_pBuffer(nullptr)
{
}

FileJob::~FileJob()
{
	if (m_pBuffer)
	{
		EngineDelete m_pBuffer;
	}
}

void FileJob::AsyncThreadProcess()
{
    std::ifstream file(m_fileName, std::ios::binary | std::ios::ate);
    if (!file.is_open()) {
        m_uiJobState = JS_FAIL;
        LOG_ERROR("Error opening file: " + m_fileName);
    }

    m_uiSize = file.tellg();
    file.seekg(0, std::ios::beg);
    m_pBuffer = EngineNew unsigned char(m_uiSize);

    if (file.read((char*)m_pBuffer, m_uiSize)) {
        LOG("Read File Name %s", m_fileName.c_str());
        LOG("Read File size: %d", size);
    }
    else {
        m_uiJobState = JS_FAIL;
        LOG_ERROR("Error opening file: " + m_fileName);
    }

    file.close();
}