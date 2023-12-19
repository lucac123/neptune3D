#pragma once
#include "Entity.h"
class PointStrip : Entity
{
private:
	int resolution;

public:
	PointStrip(int resolution);

	void draw();
};

