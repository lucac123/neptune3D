#include "FrameBuffer.h"
#include <glad/glad.h>
#include <iostream>

void checkFramebufferErrors(const char* location);

FrameBuffer::FrameBuffer(unsigned int numAttachments) {
	glGenFramebuffers(1, &this->ID);
	this->bind();

	this->drawBuffers = new unsigned int[numAttachments];
	for (int i = 0; i < numAttachments; i++)
		this->drawBuffers[i] = GL_COLOR_ATTACHMENT0 + i;

	glDrawBuffers(numAttachments, this->drawBuffers);

	checkFramebufferErrors("construction");

	this->unbind();
}

FrameBuffer::~FrameBuffer() {
	delete this->drawBuffers;
	glDeleteFramebuffers(1, &this->ID);
}

void FrameBuffer::bind() const {
	glBindFramebuffer(GL_FRAMEBUFFER, this->ID);
}
void FrameBuffer::unbind() const {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBuffer::bindTexture(TextureField* texture, unsigned int attachment) const {
	glFramebufferTexture(GL_FRAMEBUFFER, drawBuffers[attachment], texture->getID(), 0);
	checkFramebufferErrors("texture binding");
}
void FrameBuffer::unbindTexture(unsigned int attachment) const {
	glFramebufferTexture(GL_FRAMEBUFFER, drawBuffers[attachment], 0, 0);
}

unsigned int FrameBuffer::getID() const {
	return this->ID;
}

void checkFramebufferErrors(const char* location) {
	switch (glCheckFramebufferStatus(GL_FRAMEBUFFER)) {
	case GL_FRAMEBUFFER_COMPLETE:
		//std::cout << "Framebuffer complete at " << location << std::endl;
		break;
	case GL_FRAMEBUFFER_UNDEFINED:
		std::cerr << "Framebuffer undefined at " << location << std::endl;
		break;
	case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
		std::cerr << "Framebuffer incomplete at " << location << std::endl;
		break;
	case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
		std::cerr << "Framebuffer incomplete missing at " << location << std::endl;
		break;
	default:
		std::cerr << "Framebuffer error detected at " << location << std::endl;
	}
}