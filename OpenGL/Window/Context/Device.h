#pragma once
#include "../../Util/Singleton.h"
#include"../../Event/Event.h"
#include"../../Util/Utils.h"

enum class DeviceError
{
	NOT_INITIALIZED = 0x00010001,
	NO_CURRENT_CONTEXT = 0x00010002,
	INVALID_ENUM = 0x00010003,
	INVALID_VALUE = 0x00010004,
	OUT_OF_MEMORY = 0x00010005,
	API_UNAVAILABLE = 0x00010006,
	VERSION_UNAVAILABLE = 0x00010007,
	PLATFORM_ERROR = 0x00010008,
	FORMAT_UNAVAILABLE = 0x00010009,
	NO_WINDOW_CONTEXT = 0x0001000A
};

class Device: public CSingleton<Device>
{
private:
	Event<DeviceError, std::string> ErrorEvent;
	std::unordered_map<CursorShape, GLFWcursor*> m_cursor;

public:
	Device();
	~Device();

	void CreateCursor();
	void BindErrorwCallback();
	void DestroyCursors();
	void PollEvents() const;

	GLFWcursor* GetCursorInstance(CursorShape shape);

};

