#pragma once
#include "Icon.h"

class TriggerSetUI :
    public Icon
{
public:
	TriggerSetUI(GameObject* parent);
	~TriggerSetUI();
	void Initialize() override;
	void Update() override;
	void Draw() override;
private:
};

