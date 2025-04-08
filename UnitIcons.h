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
	void Update() override;
	/*void Draw() override;*/

private:
	vector<UnitIcon*> pUIcons_;
	vector<int> selectCharNum_;
	CsvReader* csv_;
	int FNSCNLine;
	int FN2DLine;
	string DLC;
};

