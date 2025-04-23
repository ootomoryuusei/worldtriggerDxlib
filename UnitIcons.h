#pragma once
#include "Engine/GameObject.h"
#include"UnitIcon.h"
#include"Engine/CsvReader.h"
#include<vector>

using std::vector;

class UnitIcons :
    public GameObject
{
public:
	UnitIcons(GameObject* parent);
	~UnitIcons();
	void Initialize() override;
	void Update() override;
	/*void Draw() override;*/

	auto GetpUnitIcons() { return pUIcons_; }
private:
	vector<UnitIcon*> pUIcons_;
	vector<int> selectCharNum_;
	CsvReader* csv_;
	int FNSCNLine;
	int FN2DLine;
	string DLC;
};

