#include "Neptune.h"

Neptune::Neptune(int resolution)
    : resolution(resolution)
{
    glGenVertexArrays(1, &this->emptyVertexArray);

    this->generateTextureFields();
    this->generateShaders();

    this->framebuffer = new FrameBuffer(1);

	this->fluidVolume = new Volume(this->velocity);
}
Neptune::~Neptune() {
	delete this->fluidVolume;
    delete this->velocity;
    delete this->velocityOut;
    delete this->pressure;
    delete this->pressureOut;
    delete this->velocityDivergence;
    delete this->substance;
    delete this->substanceOut;

    delete this->addForceShader;
    delete this->advectShader;
    delete this->diffuseShader;
    delete this->copyShader;


    delete this->framebuffer;

    glDeleteVertexArrays(1, &this->emptyVertexArray);
}

void Neptune::timeStep(float deltaTime) {
    this->framebuffer->bind();
    glViewport(0, 0, this->resolution, this->resolution);

    this->velocityStep(deltaTime);
    this->substanceStep(deltaTime);

    this->framebuffer->unbind();
}

Volume *Neptune::getVolume() {
	return this->fluidVolume;
}

void Neptune::velocityStep(float deltaTime) {
    this->addForce(this->velocity, this->velocityOut, deltaTime);
    this->advect(this->velocityOut, this->velocity, deltaTime);
    this->diffuse(this->velocity, this->velocityOut, deltaTime);
    this->copy(this->velocityOut, this->velocity);
    //this->project(deltaTime);
}

void Neptune::substanceStep(float deltaTime) {
    
}


void Neptune::generateTextureFields() {
    this->velocity = new TextureField(nullptr, GL_RGB16F, this->resolution, this->resolution, this->resolution);
    this->velocityOut = new TextureField(nullptr, GL_RGB16F, this->resolution, this->resolution, this->resolution);

    this->pressure = new TextureField(nullptr, GL_RGB16F, this->resolution, this->resolution, this->resolution);
    this->pressureOut = new TextureField(nullptr, GL_RGB16F, this->resolution, this->resolution, this->resolution);
    this->velocityDivergence = new TextureField(nullptr, GL_RGB16F, this->resolution, this->resolution, this->resolution);
    this->substance = new TextureField(nullptr, GL_RGB16F, this->resolution, this->resolution, this->resolution);
    this->substanceOut = new TextureField(nullptr, GL_RGB16F, this->resolution, this->resolution, this->resolution);
}

void Neptune::generateShaders() {
    this->addForceShader = new Shader("vert/neptune.vert", "geom/neptune.geom", "frag/add_force.frag");
    this->addForceShader->use();
    this->addForceShader->setUniform("uVelocity", 0);
    this->addForceShader->setUniform("uForceRadius", 100.0f);
    this->addForceShader->setUniform("uForcePos", (float)this->resolution/2, this->resolution/4, this->resolution/2);
    this->addForceShader->setUniform("uForce", 0.0f, 10.0f, 0.0f);

    this->advectShader = new Shader("vert/neptune.vert", "geom/neptune.geom", "frag/add_force.frag");
    this->advectShader->use();
    this->advectShader->setUniform("uVelocity", 0);

    this->diffuseShader = new Shader("vert/neptune.vert", "geom/neptune.geom", "frag/diffuse.frag");
    this->diffuseShader->use();

    this->copyShader = new Shader("vert/neptune.vert", "geom/neptune.geom", "frag/copy.frag");
}

void Neptune::addForce(TextureField *inputField, TextureField *outputField, float deltaTime) {
    this->addForceShader->use();
    this->addForceShader->setUniform("uDeltaTime", deltaTime);

    this->framebuffer->bindTexture(outputField);

    inputField->bind();

    glBindVertexArray(this->emptyVertexArray);
    glDrawArrays(GL_POINTS, 0, this->resolution);
}

void Neptune::advect(TextureField* inputField, TextureField* outputField, float deltaTime) {
    this->advectShader->use();
    this->advectShader->setUniform("uDeltaTime", deltaTime);
    this->framebuffer->bindTexture(outputField);

    inputField->bind();

    glBindVertexArray(this->emptyVertexArray);
    glDrawArrays(GL_POINTS, 0, this->resolution);

}
void Neptune::diffuse(TextureField* inputField, TextureField* outputField, float deltaTime) {
    this->diffuseShader->use();
    this->diffuseShader->setUniform("uDeltaTime", deltaTime);
    this->framebuffer->bindTexture(outputField);

    inputField->bind();
    
    glBindVertexArray(this->emptyVertexArray);
    glDrawArrays(GL_POINTS, 0, this->resolution);
}
void Neptune::project(TextureField* inputField, TextureField* outputField, float deltaTime) {

}

void Neptune::copy(TextureField* field1, TextureField* field2) {
    this->copyShader->use();
    this->framebuffer->bindTexture(field2);
    field1->bind();

    glBindVertexArray(this->emptyVertexArray);
    glDrawArrays(GL_POINTS, 0, this->resolution);
}