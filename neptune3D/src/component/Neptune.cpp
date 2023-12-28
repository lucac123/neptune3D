#include "Neptune.h"
#include <GLFW/glfw3.h>

Neptune::Neptune(int resolution, float cellSize, float viscosity)
    : resolution(resolution), cellSize(cellSize), viscosity(viscosity)
{
    glGenVertexArrays(1, &this->emptyVertexArray);

    this->generateTextureFields();
    this->generateShaders();

    this->framebuffer = new FrameBuffer(1);

	this->fluidVolume = new Volume(this->substance);
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
    delete this->jacobiShader;
    delete this->divergenceShader;
    delete this->subtractGradientShader;
    delete this->copyShader;


    delete this->framebuffer;

    glDeleteVertexArrays(1, &this->emptyVertexArray);
}

void Neptune::timeStep(float deltaTime) {
    glBindVertexArray(this->emptyVertexArray);

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
    float time = static_cast<float> (glfwGetTime());
    this->addForce(this->velocity, this->velocityOut, deltaTime, glm::vec3(this->resolution / 2, this->resolution / 4, this->resolution / 2), glm::vec3(10*glm::sin(time), 10*glm::cos(time), 10));
    this->addForce(this->velocityOut, this->velocity, deltaTime, glm::vec3(this->resolution/2, 3 * this->resolution/4, this->resolution), glm::vec3(0.0f, -500.0f, 2.0f));
    this->copy(this->velocity, this->velocityOut);
    this->advect(this->velocityOut, this->velocity, deltaTime);
    this->diffuse(this->velocity, this->velocityOut, deltaTime);
    this->project(this->velocityOut, this->velocity, deltaTime);
    this->calculateBoundary();
}

void Neptune::substanceStep(float deltaTime) {
    this->addSubstance(this->substance, this->substanceOut, deltaTime, glm::vec3(this->resolution / 2, this->resolution / 4, this->resolution / 2));

    this->transport(this->substanceOut, this->velocity, this->substance, deltaTime);
    //this->dissipate(this->substance, this->substanceOut, deltaTime);
    //this->copy(this->substanceOut, this->substance);
}


void Neptune::generateTextureFields() {
    this->velocity = new TextureField(nullptr, GL_RGB16F, this->resolution, this->resolution, this->resolution);
    this->velocityOut = new TextureField(nullptr, GL_RGB16F, this->resolution, this->resolution, this->resolution);

    this->pressure = new TextureField(nullptr, GL_R16F, this->resolution, this->resolution, this->resolution);
    this->pressureOut = new TextureField(nullptr, GL_R16F, this->resolution, this->resolution, this->resolution);
    this->velocityDivergence = new TextureField(nullptr, GL_R16F, this->resolution, this->resolution, this->resolution);
    this->substance = new TextureField(nullptr, GL_RGB16F, this->resolution, this->resolution, this->resolution);
    this->substanceOut = new TextureField(nullptr, GL_RGB16F, this->resolution, this->resolution, this->resolution);
}

void Neptune::generateShaders() {
    this->addForceShader = new Shader("vert/neptune.vert", "geom/neptune.geom", "frag/add_force.frag");
    this->addForceShader->use();
    this->addForceShader->setUniform("uVelocity", 0);

    this->advectShader = new Shader("vert/neptune.vert", "geom/neptune.geom", "frag/advect.frag");
    this->advectShader->use();
    this->advectShader->setUniform("uVelocity", 0);

    this->jacobiShader = new Shader("vert/neptune.vert", "geom/neptune.geom", "frag/jacobi.frag");

    this->divergenceShader = new Shader("vert/neptune.vert", "geom/neptune.geom", "frag/divergence.frag");
    this->divergenceShader->use();
    this->divergenceShader->setUniform("uCellSize", this->cellSize);

    this->subtractGradientShader = new Shader("vert/neptune.vert", "geom/neptune.geom", "frag/subtract_gradient.frag");
    this->subtractGradientShader->use();
    this->subtractGradientShader->setUniform("uCellSize", this->cellSize);
    this->subtractGradientShader->setUniform("uVectorField", 0);
    this->subtractGradientShader->setUniform("uScalarField", 1);


    this->copyShader = new Shader("vert/neptune.vert", "geom/neptune.geom", "frag/copy.frag");

    this->addSubstanceShader = new Shader("vert/neptune.vert", "geom/neptune.geom", "frag/add_substance.frag");
    this->addSubstanceShader->setUniform("uSubstance", 0);
}

void Neptune::addForce(TextureField *inputField, TextureField *outputField, float deltaTime, glm::vec3 forcePos, glm::vec3 force, float forceRadius) {
    this->addForceShader->use();
    this->addForceShader->setUniform("uDeltaTime", deltaTime);
    this->addForceShader->setUniform("uForcePos", forcePos);
    this->addForceShader->setUniform("uForce", force);
    this->addForceShader->setUniform("uForceRadius", forceRadius);

    this->framebuffer->bindTexture(outputField);

    inputField->bind();

    glDrawArrays(GL_POINTS, 0, this->resolution);
}

void Neptune::advect(TextureField* inputField, TextureField* outputField, float deltaTime) {
    this->advectShader->use();
    this->advectShader->setUniform("uDeltaTime", deltaTime);
    this->advectShader->setUniform("uInputField", 0);
    this->advectShader->setUniform("uTransportField", 0);
    this->framebuffer->bindTexture(outputField);

    inputField->bind();

    glDrawArrays(GL_POINTS, 0, this->resolution);

}
void Neptune::diffuse(TextureField* inputField, TextureField* outputField, float deltaTime) {
    this->jacobiShader->use();
    this->jacobiShader->setUniform("uXField", 0);
    this->jacobiShader->setUniform("uBField", 0);
    float alpha = this->cellSize * this->cellSize * this->cellSize / (this->viscosity * deltaTime);
    this->jacobiShader->setUniform("uAlpha", alpha);
    this->jacobiShader->setUniform("uBeta", alpha + 6.0f);

    this->framebuffer->bindTexture(outputField);
    inputField->bind();

    glDrawArrays(GL_POINTS, 0, this->resolution);

    for (int i = 0; i < 50 / 2; i++) {
        this->framebuffer->bindTexture(inputField);
        outputField->bind();

        glDrawArrays(GL_POINTS, 0, this->resolution);

        this->framebuffer->bindTexture(outputField);
        inputField->bind();

        glDrawArrays(GL_POINTS, 0, this->resolution);
    }
}
void Neptune::project(TextureField* inputField, TextureField* outputField, float deltaTime) {
    this->calculateDivergence(inputField);

    this->calculatePressure();

    this->subtractGradientShader->use();
    this->framebuffer->bindTexture(outputField);

    inputField->bind(GL_TEXTURE0);
    this->pressure->bind(GL_TEXTURE1);
}

void Neptune::copy(TextureField* inputField, TextureField* outputField) {
    this->copyShader->use();
    this->framebuffer->bindTexture(outputField);
    inputField->bind();

    glDrawArrays(GL_POINTS, 0, this->resolution);
}

void Neptune::calculateDivergence(TextureField* inputField) {
    this->divergenceShader->use();
    this->divergenceShader->setUniform("uVectorField", 0);

    this->framebuffer->bindTexture(this->velocityDivergence);
    inputField->bind();

    glDrawArrays(GL_POINTS, 0, this->resolution);
}

void Neptune::calculatePressure() {
    // Clear pressure field from previous iteration
    this->framebuffer->bindTexture(this->pressure);
    glClear(GL_COLOR_BUFFER_BIT);

    this->jacobiShader->use();
    this->jacobiShader->setUniform("uXField", 0);
    this->jacobiShader->setUniform("uBField", 1);
    float alpha = -1 * this->cellSize * this->cellSize * this->cellSize;
    this->jacobiShader->setUniform("uAlpha", alpha);
    this->jacobiShader->setUniform("uBeta", 6.0f);

    this->velocityDivergence->bind(GL_TEXTURE1);
    for (int i = 0; i < 80 / 2; i++) {
        this->framebuffer->bindTexture(this->pressureOut);
        this->pressure->bind();

        glDrawArrays(GL_POINTS, 0, this->resolution);

        this->framebuffer->bindTexture(this->pressure);
        this->pressureOut->bind();

        glDrawArrays(GL_POINTS, 0, this->resolution);
    }
}

void Neptune::calculateBoundary() {

}

void Neptune::addSubstance(TextureField* inputField, TextureField* outputField, float deltaTime, glm::vec3 position, float amount, float radius) {
    this->addSubstanceShader->use();
    this->addSubstanceShader->setUniform("uDeltaTime", deltaTime);
    this->addSubstanceShader->setUniform("uTime", static_cast<float>(glfwGetTime()));
    this->addSubstanceShader->setUniform("uAmount", amount);
    this->addSubstanceShader->setUniform("uPosition", position);
    this->addSubstanceShader->setUniform("uRadius", radius);

    this->framebuffer->bindTexture(outputField);
    inputField->bind();
    glDrawArrays(GL_POINTS, 0, this->resolution);
}
void Neptune::transport(TextureField* inputField, TextureField* transportField, TextureField *outputField, float deltaTime) {
    this->advectShader->use();
    this->advectShader->setUniform("uDeltaTime", deltaTime);
    this->advectShader->setUniform("uInputField", 0);
    this->advectShader->setUniform("uTransportField", 1);

    inputField->bind(GL_TEXTURE0);
    transportField->bind(GL_TEXTURE1);

    this->framebuffer->bindTexture(outputField);
    glDrawArrays(GL_POINTS, 0, this->resolution);
}
void Neptune::dissipate(TextureField* inputField, TextureField* outputField, float deltaTime) {

}