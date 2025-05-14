#pragma once
#include "Icon.h"
#include<stack>
#include<queue>

//class Mouse;
//class TileIcons;
//class MoveSetIcons;
//class MoveSelectIcons;
//class MoveTypesIcons;

using std::stack;
using std::queue;

class UnitIcon :
    public Icon
{
public:
	UnitIcon(GameObject* parent);
	~UnitIcon();
	void Initialize() override;
	void Update() override;
	void Draw() override;

	const auto& GetMoveMent() const{ return s_moveMent; }
	void SetMoveMent(int _moveMent) { s_moveMent.push(_moveMent); }
private:

	/*struct UNIT_DATA {
		int moveMent;
		float s_percent;
		float percent;
		int moveType;
	};*/
	stack<int> s_moveMent;
	queue<int> q_moveMent;

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

