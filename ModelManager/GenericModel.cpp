#include "GenericModel.h"

const char* GenericModel::getName() const {
	return this->name;
}

GenericModel::GenericModel(const char* inName)
	: Model(ModelType::Model_Generic), name(inName) { }