#pragma once
#include "Camera.h"
#include "Volume.h"
#include "Shader.h"

class Aura {
private:
	Shader *shader;
public:
	Aura();
	~Aura();
	void render(Camera* camera, Volume *volume);
};