#pragma once
#include "Engine/GameObject.h"
#include<vector>
#include<string>

class CsvReader;

using std::vector;
using std::string;

class StageData :
    public GameObject
{
public:
	StageData(GameObject* parent);
	~StageData();
	void Initialize() override;
	void Update() override;
	void Draw() override;
private:
	CsvReader* csv_;
	vector<vector<string>> stageData_;
};

