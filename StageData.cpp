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
	for (int y = 0; y < csv_->GetHeight();y++) {
		for (int x = 0;x < csv_->GetWidth(0);x++) {
		}
	}
}

void StageData::Update()
{
}

void StageData::Draw()
{
}
