#pragma once

#include "../../Util/Singleton.h"


//glew ÏÔ¿¨³§ÉÌµÄ

class Driver
{
public:
	Driver(bool isDebugModel = true);
	~Driver() = default;

	void InitGlew();
	static void __stdcall GLDebugMessageCallback(uint32_t source, uint32_t type, uint32_t id, uint32_t severity,
		int32_t length, const char* message, const void* userParam);

};

