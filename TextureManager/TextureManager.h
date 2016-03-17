#pragma once

#include "Manager.h"
#include "TextureTypes.h"

class TextureNode;
class Texture;

class TextureManager : public Manager<Texture> {
public:
	static void Startup();
	static void Shutdown();

	static void AddTexture( const char*, const TextureType );
	static void RemoveTexture( const TextureType );

	static Texture* FindTexture( const TextureType );

private:
	static void LoadTextures();
	static TextureNode* Find( const TextureType );

	TextureNode* findDepthFirst( TextureNode* const, const TextureType );
};