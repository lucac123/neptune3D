#include "Volume.h"

Volume::Volume(TextureField* densityField)
	: densityField(densityField)
{
    float vertex_data[] = {
        //position		          //texel
        -0.5, -0.5, -0.5,         0, 0, 0,              // BACK FACE
         0.5,  0.5, -0.5,         1,  1, 0,
         0.5, -0.5, -0.5,         1, 0, 0,
         0.5,  0.5, -0.5,         1,  1, 0,
        -0.5, -0.5, -0.5,         0, 0, 0,
        -0.5,  0.5, -0.5,         0,  1, 0,

        -0.5, -0.5,  0.5,         0, 0,  1,             // FRONT FACE
         0.5, -0.5,  0.5,         1, 0,  1,
         0.5,  0.5,  0.5,         1,  1,  1,
         0.5,  0.5,  0.5,         1,  1,  1,
        -0.5,  0.5,  0.5,         0,  1,  1,
        -0.5, -0.5,  0.5,         0, 0,  1,

        -0.5,  0.5,  0.5,         0,  1,  1,            // LEFT FACE
        -0.5,  0.5, -0.5,         0,  1, 0,
        -0.5, -0.5, -0.5,         0, 0, 0,
        -0.5, -0.5, -0.5,         0, 0, 0,
        -0.5, -0.5,  0.5,         0, 0,  1,
        -0.5,  0.5,  0.5,         0,  1,  1,

         0.5,  0.5,  0.5,         1,  1,  1,            // RIGHT FACE
         0.5, -0.5, -0.5,         1, 0, 0,
         0.5,  0.5, -0.5,         1,  1, 0,
         0.5, -0.5, -0.5,         1, 0, 0,
         0.5,  0.5,  0.5,         1,  1,  1,
         0.5, -0.5,  0.5,         1, 0,  1,

        -0.5, -0.5, -0.5,         0, 0, 0,              // BOTTOM FACE
         0.5, -0.5, -0.5,         1, 0, 0,
         0.5, -0.5,  0.5,         1, 0,  1,
         0.5, -0.5,  0.5,         1, 0,  1,
        -0.5, -0.5,  0.5,         0, 0,  1,
        -0.5, -0.5, -0.5,         0, 0, 0,

        -0.5,  0.5, -0.5,         0,  1, 0,             // TOP FACE
         0.5,  0.5,  0.5,         1,  1,  1,
         0.5,  0.5, -0.5,         1,  1, 0,
         0.5,  0.5,  0.5,         1,  1,  1,
        -0.5,  0.5, -0.5,         0,  1, 0,
        -0.5,  0.5,  0.5,         0,  1,  1
    };

    glGenBuffers(1, &this->domainVertexBuffer);
    glGenVertexArrays(1, &this->domainVertexArray);

    glBindVertexArray(this->domainVertexArray);
    glBindBuffer(GL_ARRAY_BUFFER, this->domainVertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_data), vertex_data, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
}

Volume::~Volume() {
    glDeleteBuffers(1, &this->domainVertexBuffer);
    glDeleteVertexArrays(1, &this->domainVertexArray);
}

TextureField* Volume::getDensityField() {
    return this->densityField;
}

void Volume::setDensityField(TextureField* densityField) {
    this->densityField = densityField;
}

void Volume::bind() {
    glBindVertexArray(this->domainVertexArray);
}

void Volume::draw() {
    glDrawArrays(GL_TRIANGLES, 0, 36);
}