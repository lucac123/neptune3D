#include "PointStrip.h"
#include <glad/glad.h>

PointStrip::PointStrip(int resolution)
	:resolution(resolution)
{}

void PointStrip::draw() {
	glEnable(GL_PROGRAM_POINT_SIZE);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDrawArrays(GL_POINTS, 0, this->resolution);
}