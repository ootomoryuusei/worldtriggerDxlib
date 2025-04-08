#pragma once
#include "Icon.h"
class UnitIcon :
    public Icon
{
public:
	UnitIcon(GameObject* parent);
	~UnitIcon();
	void Update() override;
	void Draw() override;

private:
	bool prevMouse;
	bool currentMouse;
	bool doubleClicked;
	int lastClickTime;
	int doubleClickTime;
	int now;
};

