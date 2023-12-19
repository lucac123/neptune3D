#include "ResourceManager.h"

const char* SHADER_BASE = "C:/Users/lchac/source/repos/neptune3D/neptune3D/shaders/";

std::string *ResourceManager::readShader(const char* cPath) {
	std::string path = std::string(SHADER_BASE) + std::string(cPath);
	std::ifstream file;
	file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try {
		file.open(path.c_str());
		std::stringstream fileStream;
		fileStream << file.rdbuf();
		file.close();

		return new std::string(fileStream.str());
	}
	catch (std::ifstream::failure& e) {
		std::cout << "ya messed up with " << cPath << " ==> " << path << std::endl << e.what() << std::endl;
	}
	return nullptr;
}
