/*
 * Physically Based Rendering
 * Copyright (c) 2017-2018 Michał Siejak
 */


#include <cstdio>
#include <string>
#include <memory>
#include <vector>

#include "SampleBrowser.h"

#include <iostream>
#include <chrono>
#include <unordered_map>


int main(int argc, char* argv[])
{

	SampleBrowser sampleBrowser;

	sampleBrowser.run();

	return 0;
}

