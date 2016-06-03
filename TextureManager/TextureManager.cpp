#include "TextureManager.h"

#include "TextureNode.h"
#include "Texture.h"

void TextureManager::Startup() {
	printf("\n===== TEXTURE MANAGER : START =====\n");
	GetInstance();
	LoadTextures();
	printf("===== TEXTURE MANAGER : FINISHED STARTING =====\n\n");
}

void TextureManager::Shutdown() {
	Cleanup();
	DestroyInstance();
}

void TextureManager::AddTexture(const char* filename, const TextureType type) {
	// Only add texture to manager if unique texture. No need for duplicates.
	if(!Find(type)) {
		Add(new TextureNode(new Texture(filename, type)));
	}
}

void TextureManager::RemoveTexture(const TextureType type) {
	Remove(Find(type));
}

Texture* TextureManager::FindTexture(const TextureType type) {
	Texture* texture = nullptr;
	TextureNode* texturenode = Find(type);
	if(texturenode) {
		texture = texturenode->getData();
	}
	return texture;
}

void TextureManager::LoadTextures() {
	printf("TEXTURE MANAGER: Loading textures...\n");
	AddTexture("../TextureManager/Bricks.tga", TextureType::Texture_Brick);
}

TextureNode* TextureManager::Find(const TextureType type) {
	TextureNode* texture = nullptr;
	if(type != TextureType::Texture_None) {
		TextureNode* root = static_cast<TextureNode*>(GetObjectList()->getRoot());

		if(root) {
			TextureManager* instance = static_cast<TextureManager*>(GetInstance());
			texture = instance->findDepthFirst(root, type);
		}
	}
	return texture;
}

TextureNode* TextureManager::findDepthFirst(TextureNode* const walker, const TextureType type) const {
	TextureNode* texture = nullptr;

	if(walker->getType() == type) {
		texture = walker;
	} else {
		if(walker->getChild()) {
			texture = this->findDepthFirst(static_cast<TextureNode*>(walker->getChild()), type);
		}
		if(!texture && walker->getSibling()) {
			texture = this->findDepthFirst(static_cast<TextureNode*>(walker->getSibling()), type);
		}
	}
	return texture;
}