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

	bool GetClicked() { return clicked; }
	void SetClicked(bool _clicked) { clicked = _clicked; }

	auto GetSerchResult() { return serchAroundTileNum; }

	vector<int> SerchAroundTileNum(int _CenterNum, int _renge);
private:
	bool prevMouse;
	bool currentMouse;
	/*string iconName;*/
	XMFLOAT2 space;
	bool clicked;

	void TypeMove();
	void SimpleMove();

	vector<int> serchAroundTileNum;
};

