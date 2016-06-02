#include "TextureNode.h"

#include "Texture.h"

TextureType TextureNode::getType() const {
	return this->type;
}

TextureNode::TextureNode(Texture* const texture)
	: NodeLink(texture), type(texture->getType()) { }

TextureNode::~TextureNode() { }