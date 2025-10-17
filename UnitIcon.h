#pragma once
#include "Icon.h"
#include<deque>

class Trigger;
class TriggersArcIcon;
class MoveMentsLoad;
class GroupManager;
class TileIcons;

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
	void AddMoveMent(VECTOR _moveMent) { moveMent.push_back(_moveMent); }

	void SetMyTrigger(MYTRIGGER _myTrigger) { myTrigger = _myTrigger; }
	bool GetSet() { return set; }

	const auto& GetpTriggersArcIcon() { return pArcs_; }
	const auto& GetpMoveMentLoad() { return pLoad_; }
private:

	vector<VECTOR> moveMent;
	deque<VECTOR> dq_moveMent;

	array<Trigger*, MAX> hands_;

	bool firstSet;
	bool moveing;

	int maxMoveMent;

	float totalTime;
	float elapsedTime;

	MYTRIGGER myTrigger;
	bool set;

	GroupManager* pGroupManager_;
	TileIcons* pTileIcons_;
	TriggersArcIcon* pArcs_;
	MoveMentsLoad* pLoad_;
};

