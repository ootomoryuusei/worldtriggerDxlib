#include"StageData.h"
#include"Engine/CsvReader.h"

StageData::StageData(GameObject* parent)
{
}

StageData::~StageData()
{
}

void StageData::Initialize()
{
	csv_ = new CsvReader();
	csv_->Load("Assets//Stage//SampleStage.csv");
	size.x = csv_->GetWidth(0);
	size.y = csv_->GetHeight();
	for (int y = 0; y < size.y;y++) {
		vector<string> row;
		for (int x = 0;x < size.x;x++) {
			row.push_back(csv_->GetString(x, y));
		}
		stageData_.push_back(row);
	}
}

void StageData::Update()
{
}

void StageData::Draw()
{
}
