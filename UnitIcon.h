#pragma once
#include "Icon.h"
#include<deque>

class Trigger;
class TriggersArcIcon;

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
	void AddMoveMent(int _moveMent) { moveMent.push_back(_moveMent); }

	void SetMyTrigger(MYTRIGGER _myTrigger) { myTrigger = _myTrigger; }
	bool GetSet() { return set; }
private:

	vector<int> moveMent;
	deque<int> dq_moveMent;

	array<Trigger*, MAX> hands_;

	bool firstSet;
	bool moveing;

	int maxMoveMent;

	float totalTime;
	float elapsedTime;

	MYTRIGGER myTrigger;
	bool set;

	TriggersArcIcon* pArcs_;
};

