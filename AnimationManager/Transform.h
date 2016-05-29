#pragma once

class Vect;
class Quat;

class Transform {
public:
	Vect* getTranslation() const;
	void setTranslation(Vect* const);

	Quat* getRotation() const;
	void setRotation(Quat* const);

	Vect* getScale() const;
	void setScale(Vect* const);

	Transform();
	~Transform();

private:
	Vect* translation;
	Quat* rotation;
	Vect* scale;
};