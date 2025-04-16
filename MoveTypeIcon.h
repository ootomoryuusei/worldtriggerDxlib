#pragma once
#include "Icon.h"

class MoveTypeIcon :
    public Icon
{
public:
	MoveTypeIcon(GameObject* parent);
	~MoveTypeIcon();
	void Update() override;
	void Draw() override;

	/*void SetIconName(string _iconName) { iconName = _iconName; }
	string GetIconName() { return iconName; }*/
	bool GetClicked() { return clicked; }
	void SetClicked(bool _clicked) { clicked = _clicked; }
private:
	/*string iconName;*/
	XMFLOAT2 space;
	bool clicked;
};

