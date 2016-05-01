#pragma once

class Animation {
public:
	const char* getName() const;

	Animation(const char*);
	~Animation();

private:
	const char* name;
};