#include "FileJob.h"
#include <filesystem>
AsyncJob::AsyncJob()
{
}
//AsyncJob::~AsyncJob()
//{
//}

FileJob::FileJob() :
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