#include "FrameBuffer.h"
#include <glad/glad.h>

FrameBuffer::FrameBuffer(unsigned int numAttachments) {
	glGenFramebuffers(1, &this->ID);
	this->bind();

	this->drawBuffers = new unsigned int[numAttachments];
	for (int i = 0; i < numAttachments; i++)
		this->drawBuffers[i] = GL_COLOR_ATTACHMENT0 + i;

	glDrawBuffers(numAttachments, this->drawBuffers);

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
}
void FrameBuffer::unbindTexture(unsigned int attachment) const {
	glFramebufferTexture(GL_FRAMEBUFFER, drawBuffers[attachment], 0, 0);
}

unsigned int FrameBuffer::getID() const {
	return this->ID;
}