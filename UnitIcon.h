#pragma once
#include "Icon.h"
#include<deque>

//class Mouse;
//class TileIcons;
//class MoveSetIcons;
//class MoveSelectIcons;
//class MoveTypesIcons;

using std::deque;

class UnitIcon :
    public Icon
{
public:
	UnitIcon(GameObject* parent);
	~UnitIcon();
	void Initialize() override;
	void Update() override;
	void Draw() override;

	const auto& GetMoveMent() const{ return moveMent; }
	void SetMoveMent(int _moveMent) { moveMent.push_back(_moveMent); }
private:

	/*struct UNIT_DATA {
		int moveMent;
		float s_percent;
		float percent;
		int moveType;
	};*/

	vector<int> moveMent;
	deque<int> dq_moveMent;

	bool firstSet;
	bool moveing;

	int maxMoveMent;

	float totalTime;
	float elapsedTime;

	VECTOR Lerp3D(VECTOR & start, VECTOR & goal, float percent);

	/*Mouse* pMouse_;
	TileIcons* pTileIcons_;
	MoveSetIcons* pMoveSetIcons_;
	MoveSelectIcons* pMoveSelectIcons_;
	MoveTypesIcons* pMoveTypesIcons_;*/
};

