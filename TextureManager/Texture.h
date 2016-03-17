#pragma once

#include "TextureTypes.h"

class Texture {
public:
	TextureType getType() const;
	unsigned int getTextureID() const;

	Texture( const char*, const TextureType );
	~Texture();

private:
	void setupTexture( const char * filename );

private:
	TextureType type;
	unsigned int textureID;
};