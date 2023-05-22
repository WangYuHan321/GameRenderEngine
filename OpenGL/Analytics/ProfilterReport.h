#pragma once

#include <string>
#include <iostream>
#include <map>

class ProfilterReport final
{
	struct Action final
	{
		std::string name;
		double duration;
		double percentage;
		uint64_t calls;
	};

	double elaspedTime;
};

