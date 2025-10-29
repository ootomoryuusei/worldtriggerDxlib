#pragma once
#include "Icon.h"
#include"TriggerArcIcon.h"
#include<array>

using std::array;

class TriggersArcIcon :
    public Icon
{
public:

	TriggersArcIcon(GameObject* parent);
	~TriggersArcIcon();
	void Initialize() override;
	void Update() override;
	/*void Draw() override;*/

	const auto& GetpTriggerArcIcon() const { return pTriggerArcIcon; }

private:
	array<TriggerArcIcon*,MAX> pTriggerArcIcon;
	TriggerArcIcon* pFirstSelect;
};

