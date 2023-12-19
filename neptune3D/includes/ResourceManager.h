#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class ResourceManager
{
public:
	static std::string *readShader(const char* path);
};

