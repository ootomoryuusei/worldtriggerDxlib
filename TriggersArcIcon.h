#pragma once
#include "Object2D.h"
#include"TriggerArcIcon.h"
#include<array>

using std::array;

class TriggersArcIcon :
    public Object2D
{
public:

	TriggersArcIcon(GameObject* parent);
	~TriggersArcIcon();
	void Initialize() override;
	void Update() override;
	/*void Draw() override;*/

	const auto& GetpTriggerArcIcon() const { return pTriggerArcIcon; }

private:
	array<TriggerArcIcon*, static_cast<size_t>(HANDS::MAX)> pTriggerArcIcon;
	TriggerArcIcon* pFirstSelect;
};

