#pragma once

class Vect;
class Quat;

class Transform {
public:
	Vect* getTranslation() const;
	void setTranslation(const Vect* const);

	Quat* getRotation() const;
	void setRotation(const Quat* const);

	Vect* getScale() const;
	void setScale(const Vect* const);

	Transform();
	~Transform();

private:
	Vect* translation;
	Quat* rotation;
	Vect* scale;
};