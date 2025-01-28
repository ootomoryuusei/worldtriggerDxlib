#include "ShealdIcon.h"
#include"Player1.h"

ShealdIcon::ShealdIcon(GameObject* parent) : Object3D(parent)
{
	hModel = LoadGraph("Assets//Image//TriggerIcon//Sheald.png");
	assert(hModel >= 0);
	GetGraphSize(hModel, &graphSize_.x, &graphSize_.y);
	graphSize_.halfX = graphSize_.x / 2.0f;
	graphSize_.halfY = graphSize_.y / 2.0f;
}

ShealdIcon::~ShealdIcon()
{
}

void ShealdIcon::Update()
{
	Player1* pPl1 = GetParent()->FindGameObject<Player1>();
	XMFLOAT2 mousePos = pPl1->GetMousePos();
	if (PointInBox(mousePos, { position.x,position.z }, { graphSize_.x, graphSize_.y })) {
		if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {
			position = { mousePos.x - graphSize_.halfX,0.0f,mousePos.y - graphSize_.halfY };
		}
		else {
			for () {
				int i = 0;
				if (PointInBox({ position.x,position.z }, ,)) {
					WSPosition_[index] = itr;
				}
				i++;
			}
		}
	}
}

void ShealdIcon::Draw()
{
	DrawGraph(position.x,position.z , hModel, TRUE);
}
