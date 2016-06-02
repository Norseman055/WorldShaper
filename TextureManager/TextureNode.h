#pragma once

#include "NodeLink.h"
#include "TextureTypes.h"

class Texture;

class TextureNode : public NodeLink<Texture*> {
public:
	TextureType getType() const;

	TextureNode(Texture* const texture);
	~TextureNode();

private:
	TextureType type;
};