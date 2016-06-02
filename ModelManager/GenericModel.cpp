#include "GenericModel.h"

#include <assert.h>
#include <string.h>

const char* GenericModel::getName() const {
	return this->name;
}

GenericModel::GenericModel(const char* inName)
	: Model(ModelType::Model_Generic) {
	assert(inName);
	int nameLen = strlen(inName);
	this->name = new char[nameLen + 1];
	strcpy(this->name, inName);
}