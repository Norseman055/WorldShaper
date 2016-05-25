#pragma once

#include <PCSTree\PCSNode.h>

class Bone : public PCSNode {
public:
	char* getName() const;

	Bone(const char*);
	virtual ~Bone();

private:
	char* name;
public:
	int parentIndex;
	unsigned int level;
};