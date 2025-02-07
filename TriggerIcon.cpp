#include "TriggerIcon.h"
#include"Player1.h"
#include"TriggerSetUIFrame.h"

TriggerIcon::TriggerIcon(GameObject* parent) : Object3D(parent)
{
	position = { 0,0,0 };
	initialPosition_ = { 0,0,0 };
	alreadySet_ = false;
	settingNum_ = 0;
}

TriggerIcon::~TriggerIcon()
{
}

void TriggerIcon::Update()
{
	Player1* pPl1 = GetParent()->GetParent()->FindGameObject<Player1>();
	XMFLOAT2 mousePos = pPl1->GetMousePos();
	TriggerSetUIFrame* pTSUF = GetParent()->FindGameObject<TriggerSetUIFrame>();
	if (PointInBox(mousePos, { position.x,position.y }, { (float)graphSize_.x, (float)graphSize_.y })) {
		if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {
			position = { mousePos.x - graphSize_.halfX,mousePos.y - graphSize_.halfY ,0.0f };
		}
		else {
			int num = 0;
			for (auto itr : pTSUF->GetSIFPosition()) {
				if (PointInBox({ position.x,position.y }, itr, pTSUF->GetSIFGraphSize())) {
					position = { itr.x,itr.y ,0.0f };
					settingNum_ = num;

				} 
				num++;
			}
		}
	}
	/*if (position.x != initialPosition_.x && position.x != initialPosition_.y) {
		position = initialPosition_;
	}*/
}

void TriggerIcon::Draw()
{
	DrawGraph(position.x, position.y, hModel, TRUE);
}

void TriggerIcon::Load(const std::string& _fileName)
{
	fileName_ = _fileName;
	hModel = LoadGraph(fileName_.c_str());
	assert(hModel >= 0);
	GetGraphSize(hModel, &graphSize_.x, &graphSize_.y);
	graphSize_.halfX = graphSize_.x / 2.0f;
	graphSize_.halfY = graphSize_.y / 2.0f;
}
