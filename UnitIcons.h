#pragma once
#include "Icon.h"
#include"UnitIcon.h"
#include"Engine/CsvReader.h"
#include<vector>

class MoveSelectIcon;
class MoveSetIcon;

using std::vector;

class UnitIcons :
	public Icon
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

	bool moveMentSet;
};

