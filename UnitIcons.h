#pragma once
#include"Object2D.h"
#include"UnitIcon.h"
#include"MoveSetIcon.h"
#include"MoveSelectIcon.h"
#include"Engine/CsvReader.h"
#include<vector>

class GroupManager;

using std::vector;

class UnitIcons :
	public Object2D
{
public:
	UnitIcons(GameObject* parent);
	~UnitIcons();
	void Initialize() override;
	void Update() override;
	/*void Draw() override;*/

	const auto& GetpUnitIcons() const { return pUIcons_; }
	const auto& GetpSelecting_ptr() const { return pSelecting_ptr; }
	const auto& GetpMoveSetIcon() const { return pMoveSetIcon_; }
	const auto& GetpMoveSelectIcon() const { return pMoveSelectIcon_; }

	void SetMoveMentSet(bool _moveMentSet) { moveMentSet = _moveMentSet; }
	bool GetMoveMentSet() { return moveMentSet; }
private:
	vector<UnitIcon*> pUIcons_;
	UnitIcon* pSelecting_ptr;
	CsvReader* csv_;
	string DLC;

	MoveSelectIcon* pMoveSelectIcon_;
	MoveSetIcon* pMoveSetIcon_;

	GroupManager* pGroupManager_;
	bool moveMentSet;
};

