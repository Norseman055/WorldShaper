#pragma once

#include "Model.h"

class GenericModel : public Model {
public:
	const char* getName() const;

	GenericModel(const char*);

private:
	// NO DEFAULT CONSTRUCTOR! NAME THE MODEL!
	GenericModel() = delete;

	char* name;
};