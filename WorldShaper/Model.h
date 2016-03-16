#pragma once

#include "ModelTypes.h"

class Model {
public:
	Model()
		: type(Model_None)
	{ }

	virtual ~Model() = 0;

protected:
	ModelType type;
};