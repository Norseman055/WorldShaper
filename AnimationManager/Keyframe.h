#pragma once

class Transform;

class Keyframe {
public:
	float getTime() const;
	void setTime(const float);

	int getNumTransforms() const;
	void setNumTransforms(const int);

	Transform* getTransforms() const;
	void setTransforms(Transform* const);

	Keyframe();
	~Keyframe();

private:
	float time;
	int numTransforms;
	Transform* transforms;
};