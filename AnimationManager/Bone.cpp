#include "Bone.h"

#include <assert.h>
#include <string.h>

char* Bone::getName() const {
	return this->name;
}

Bone::Bone(const char* inName)
	: parentIndex(0), level(0) {
	assert(inName);
	int nameLen = strlen(inName);
	this->name = new char[nameLen + 1];
	strcpy(this->name, inName);
}

Bone::~Bone() { }