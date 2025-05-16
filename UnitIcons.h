#pragma once
#include "Icon.h"
#include"UnitIcon.h"
#include"Engine/CsvReader.h"
#include<vector>

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

	void SetMoveMentSet(bool _moveMentSet) { moveMentSet = _moveMentSet; }
	bool GetMoveMentSet() { return moveMentSet; }
private:
	vector<UnitIcon*> pUIcons_;
	UnitIcon* pSelecting_ptr;
	vector<int> selectCharNum_;
	CsvReader* csv_;
	int FNSCNLine;
	int FN2DLine;
	string DLC;

	bool moveMentSet;
};

