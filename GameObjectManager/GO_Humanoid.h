#pragma once

#include "GameObject.h"

class GO_Humanoid : public GameObject {
public:
	enum struct HumanoidAnim {
		Anim_Shot,
		Anim_Punch,
		Anim_Run,
		Anim_Take001,
		Anim_BindPose
	};

	void setAnimation(const HumanoidAnim);

	void update(const float) const override;

	GO_Humanoid(const char*);
	~GO_Humanoid();

private:
	void setupHumanoid();

	HumanoidAnim currAnim;
};