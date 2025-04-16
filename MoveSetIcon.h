#pragma once
#include "Icon.h"
#include"Engine/CsvReader.h"
#include<vector>

using std::vector;

class MoveSetIcon :
    public Icon
{
public:
	MoveSetIcon(GameObject* parent);
	~MoveSetIcon();
	void Initialize() override;
	void Update() override;
	void Draw() override;
private:
	CsvReader* csv_;
	//string iconName;
	XMFLOAT2 space;
	int maxSetMove;
	vector<string> moveName;
};

