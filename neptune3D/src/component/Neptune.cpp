#include "Neptune.h"

float* generateScalarField(int width, int height, int depth, float scale);

Neptune::Neptune(int resolution)
    : resolution(resolution)
{
    float* data = generateScalarField(this->resolution, this->resolution, this->resolution, 1.0f);
	this->volumeField = new TextureField(nullptr, GL_RGB, this->resolution, this->resolution, this->resolution);
	this->fluidVolume = new Volume(this->volumeField);
    this->framebuffer = new FrameBuffer(1);

    this->neptuneShader = new Shader("vert/neptune.vert", "geom/neptune.geom", "frag/neptune.frag");

	delete[] data;
}
Neptune::~Neptune() {
	delete this->fluidVolume;
	delete this->volumeField;

    delete this->neptuneShader;
    delete this->framebuffer;
}

void Neptune::timeStep(float deltaTime) {
    this->framebuffer->bind();
    glViewport(0, 0, this->resolution, this->resolution);
    this->neptuneShader->use();
    this->framebuffer->bindTexture(this->volumeField);
    glDrawArrays(GL_POINTS, 0, this->resolution);
    this->framebuffer->unbind();
    glViewport(0, 0, 1920, 1080);
}

Volume *Neptune::getVolume() {
	return this->fluidVolume;
}


float* generateScalarField(int width, int height, int depth, float scale) {
    float* field = new float[height * width * depth * 3];
    float threshold = 0.3f;
    int index = 0;
    for (int i = 0; i < width; i++)
        for (int j = 0; j < height; j++)
            for (int k = 0; k < depth; k++) {
                field[index++] = sin(i/10);
                field[index++] = cos(j/25);
                field[index++] = sin(k/50);
            }
    return field;
}