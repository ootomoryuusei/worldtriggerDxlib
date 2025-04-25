#pragma once
#include "Icon.h"
class TriggerArcIcon :
    public Icon
{
public:
	TriggerArcIcon(GameObject* parent);
	~TriggerArcIcon();
	void Initialize() override;
	void Update() override;
	void Draw() override;

private:

};

