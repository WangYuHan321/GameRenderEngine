#include "Driver.h"

#include <GL/glew.h>
#include <string>
#include "../../Util/common.h"

Driver::Driver()
{
	InitGlew();
}

void Driver::InitGlew()
{
	const GLenum error = glewInit();
	if (error != GLEW_OK)
	{
		std::string message = "Error Init GLEW: ";
		std::string glewError = reinterpret_cast<const char*>(glewGetErrorString(error));
		Log(message + glewError);
	}
}