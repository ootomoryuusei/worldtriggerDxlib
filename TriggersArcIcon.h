#pragma once
#include "Icon.h"
#include"TriggerArcIcon.h"

class TriggersArcIcon :
    public Icon
{
public:
	struct TRIGGER_ARC_ICON{
		TriggerArcIcon* pMainArc;
		TriggerArcIcon* pSubArc;
	};

	TriggersArcIcon(GameObject* parent);
	~TriggersArcIcon();
	void Initialize() override;
	void Update() override;
	/*void Draw() override;*/

	const auto& GetpTriggerArcIcon() const { return pTriggerArcIcon; }
private:
	TRIGGER_ARC_ICON pTriggerArcIcon;
};

