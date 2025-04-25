#pragma once
#include "Engine/GameObject.h"
#include"TriggersArcIcon.h"

class TriggersArcIcons :
    public GameObject
{
public:
	TriggersArcIcons(GameObject* parent);
	~TriggersArcIcons();
	void Initialize() override;
	void Update() override;
	/*void Draw() override;*/

	const auto& GetpTriggersArcIcon_() const { return pTriggersArcIcon_; }
private:
	vector<TriggersArcIcon*> pTriggersArcIcon_;
};

