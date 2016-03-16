#pragma once

#include "PCSTree\PCSNode.h"

template<typename T>
class NodeLink : public PCSNode {
public:
	NodeLink( T* node )
		: PCSNode(), data( node ) { }

	T* getData() {
		return this->data;
	}

private:
	NodeLink() :
		PCSNode(), data( nullptr ) { }

	T* data;
};