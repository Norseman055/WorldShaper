#include "Texture.h"

#include "stb_lib.h"

#define GLEW_STATIC
#include "glew\glew.h"
#include "GLFW\glfw3.h"

TextureType Texture::getType() const {
	return this->type;
}

unsigned int Texture::getTextureID() const {
	return this->textureID;
}

void Texture::setupTexture( const char* filename ) {
	printf( "    Setting up OpenGL buffers for texture " );
	printf( filename );
	printf( "..." );

	int width, height, numComponents;
	unsigned char* imageData = stbi_load( filename, &width, &height, &numComponents, 0 );
	if(!imageData) {
		printf("  Failed! Error: ");
		printf(stbi_failure_reason());
		printf("\n");
		return;
	}

	glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );

	glGenTextures( 1, &this->textureID );
	glBindTexture( GL_TEXTURE_2D, this->textureID );
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData );

	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );

	printf(" Success!\n");
}

Texture::Texture( const char* filename, const TextureType inType )
	: type( inType ), textureID( 0 ) {
	this->setupTexture( filename );
}

Texture::~Texture() {
	glDeleteTextures( 1, &this->textureID );
}