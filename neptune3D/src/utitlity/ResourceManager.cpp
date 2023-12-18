#include "ResourceManager.h"

std::string *ResourceManager::readFile(const char* path) {
	std::ifstream file;
	file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try {
		file.open(path);
		std::stringstream fileStream;
		fileStream << file.rdbuf();
		file.close();

		return new std::string(fileStream.str());
	}
	catch (std::ifstream::failure& e) {
		std::cout << "ya messed up" << e.what() << std::endl;
	}
	return nullptr;
}
