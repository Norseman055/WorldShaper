#pragma once

class PCSTree;

class Skeleton {
public:
	PCSTree* getBones() const;
	void setBones(PCSTree* const bones);

	int getNumLevels() const;
	void setNumLevels(const int);

	Skeleton(const char*);
	~Skeleton();

private:
	PCSTree* bones;
	char* name;
	int numBones;
	int numLevels;
};