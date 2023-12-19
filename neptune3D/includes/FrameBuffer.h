#pragma once
#include "TextureField.h"

class FrameBuffer
{
private:
	unsigned int ID;
	unsigned int* drawBuffers;
public:
	FrameBuffer(unsigned int numAttachments);
	~FrameBuffer();

	void bind() const;
	void unbind() const;

	void bindTexture(TextureField* texture, unsigned int attachment = 0) const;
	void unbindTexture(unsigned int attachment = 0) const;

	unsigned int getID() const;
};

