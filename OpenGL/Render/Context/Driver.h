#pragma once

#include "../../Util/Singleton.h"


//glew от©╗Ё╖ил╣д

class Driver : public CSingleton<Driver>
{
public:
	Driver();
	~Driver() = default;

	void InitGlew();

};

