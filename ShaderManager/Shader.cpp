#include "Shader.h"

#define GLEW_STATIC
#include "glew\glew.h"
#include "GLFW\glfw3.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

ShaderType Shader::getType() const {
	return this->type;
}

unsigned int Shader::getShaderID() const {
	return this->shaderProgram;
}

void Shader::setupGLSLShaders( const char* shaderName ) {
	printf( "      Compiling GLSL shaders and creating shader program...\n" );

	// Make fragment and vertex shader name
	int nameLen = strlen( shaderName );
	char* vertExt = ".vert\0";
	char* fragExt = ".frag\0";
	char* vertShaderName = new char[nameLen + 6];
	char* fragShaderName = new char[nameLen + 6];
	memcpy( vertShaderName, shaderName, nameLen );
	memcpy( &vertShaderName[nameLen], vertExt, 6 );
	memcpy( fragShaderName, shaderName, nameLen );
	memcpy( &fragShaderName[nameLen], fragExt, 6 );

	int status;
	char errorMessage[4096];  // Big enough to hold any reasonable error message
	FILE* vertF;

	auto vertexShaderSrc = new char[2048];
	fopen_s( &vertF, vertShaderName, "rb" );
	if ( !vertF ) {
		perror( "      Could not load vertex shader file " );
		return;
	}
	int charCount = fread( vertexShaderSrc, 1, 2048, vertF );
	vertexShaderSrc[charCount] = '\0';	// Add on a null character to terminate the string
	fclose( vertF );

	// Now send the source to OpenGL and compile the vertex shader
	printf( "      Making vertex shader..." );
	this->vertexShader = glCreateShader( GL_VERTEX_SHADER );
	glShaderSource( this->vertexShader, 1, const_cast< const char ** >(&vertexShaderSrc), nullptr );
	glCompileShader( this->vertexShader );
	glGetShaderiv( this->vertexShader, GL_COMPILE_STATUS, &status );
	if ( status == GL_FALSE )	// false indicates a compile error
	{
		glGetShaderInfoLog( this->vertexShader, 4096, nullptr, errorMessage );
		printf( errorMessage );
		printf( "\n" );
		return;
	}
	printf( "  Success!\n" );

	// Now load and compile the fragment shader
	auto fragmentShaderSrc = new char[2048];
	FILE* fragF;
	fopen_s( &fragF, fragShaderName, "rb" );
	if ( !fragF ) {
		perror( "      Could not load fragment shader file " );
		return;
	}
	charCount = fread( fragmentShaderSrc, 1, 2048, fragF );
	fragmentShaderSrc[charCount] = '\0';
	fclose( fragF );

	// Now compile the fragment shader
	printf( "      Making fragment shader..." );
	this->fragmentShader = glCreateShader( GL_FRAGMENT_SHADER );
	glShaderSource( this->fragmentShader, 1, const_cast< const char ** >(&fragmentShaderSrc), nullptr );
	glCompileShader( this->fragmentShader );
	glGetShaderiv( this->fragmentShader, GL_COMPILE_STATUS, &status );
	if ( status != 1 )	// then there was a compile error 0 = fail, 1 = pass
	{
		glGetShaderInfoLog( this->fragmentShader, 4096, nullptr, errorMessage );
		printf( errorMessage );
		printf( "\n" );
		exit( EXIT_FAILURE );
	}
	printf( "  Success!\n" );

	printf( "      Compiling GLSL shader..." );
	this->shaderProgram = glCreateProgram();
	glAttachShader( this->shaderProgram, this->vertexShader );
	glAttachShader( this->shaderProgram, this->fragmentShader );
	glLinkProgram( this->shaderProgram );

	glGetObjectParameterivARB( this->shaderProgram, GL_OBJECT_LINK_STATUS_ARB, &status );
	if ( status != 1 ) {
		printf( "Program and Shaders objects failed to link.\n" );
		glGetProgramInfoLog( this->shaderProgram, 4096, nullptr, errorMessage );
		printf( errorMessage );
		printf( "\n\n" );
		exit( EXIT_FAILURE );
	}
	printf( "  Success!\n" );
}

Shader::Shader( const ShaderType inType, const char* shaderName )
	: type( inType ) {
	setupGLSLShaders( shaderName );
}

Shader::~Shader() { }