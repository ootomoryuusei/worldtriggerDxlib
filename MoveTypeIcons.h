#pragma once
//#include "Engine/GameObject.h"
#include "Icon.h"
#include"Engine/CsvReader.h"
#include"MoveTypeIcon.h"

using std::vector;

class MoveTypeIcons :
    public Icon
{
public:
	MoveTypeIcons(GameObject* parent);
	~MoveTypeIcons();
	void Initialize() override;
	void Update() override;

	auto GetpMoveTypeIcons() { return pMoveTypeIcons_; }
private:
	vector<MoveTypeIcon*> pMoveTypeIcons_;
	CsvReader* csv_;
	int FNMTLine;
};

