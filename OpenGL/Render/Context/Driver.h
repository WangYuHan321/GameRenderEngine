#pragma once

#include "../../Util/Singleton.h"


//glew �Կ����̵�

class Driver : public CSingleton<Driver>
{
public:
	Driver();
	~Driver() = default;

	void InitGlew();

};

