#include "ShealdIcon.h"
#include"Player1.h"
#include"TriggerSetUIFrame.h"

ShealdIcon::ShealdIcon(GameObject* parent) : Object3D(parent)
{
	position = { 0,0,0 };
}

ShealdIcon::~ShealdIcon()
{
}

void ShealdIcon::Load(const std::string& _fileName)
{
	hModel = LoadGraph(_fileName.c_str());
	assert(hModel >= 0);
	GetGraphSize(hModel, &graphSize_.x, &graphSize_.y);
	graphSize_.halfX = graphSize_.x / 2.0f;
	graphSize_.halfY = graphSize_.y / 2.0f;
}

void ShealdIcon::Update()
{
	Player1* pPl1 = GetParent()->FindGameObject<Player1>();
	XMFLOAT2 mousePos = pPl1->GetMousePos();
	TriggerSetUIFrame* pTSUF = GetParent()->FindGameObject<TriggerSetUIFrame>();
	if (PointInBox(mousePos, { position.x,position.z }, { (float)graphSize_.x, (float)graphSize_.y })) {
		if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {
			position = { mousePos.x - graphSize_.halfX,0.0f,mousePos.y - graphSize_.halfY };
		}
		else {
			for (auto itr : pTSUF->GetSIFPosition()) {
				if (PointInBox({ position.x,position.z },itr,pTSUF->GetSIFGraphSize())) {
					position = { itr.x,0.0f,itr.y };
				}
			}
		}
	}
}

void ShealdIcon::Draw()
{
	DrawGraph(position.x,position.z , hModel, TRUE);
}
