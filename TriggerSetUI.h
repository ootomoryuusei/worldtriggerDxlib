#pragma once
#include "Icon.h"

class TriggerSetUI :
    public Icon
{
public:
	TriggerSetUI(GameObject* parent);
	~TriggerSetUI();
	void Update() override;
	void Draw() override;
private:
};

