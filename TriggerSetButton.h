#pragma once
#include "Object3D.h"
#include<vector>

using std::vector;

class CharacterSetUIFrame;

class TriggerSetButton :
    public Object3D
{
public:
	TriggerSetButton(GameObject* parent);
	~TriggerSetButton();
	void Update() override;
	void Draw() override;
private:
	SIZE_2D graphSize_; //アイコンの画像サイズ
	vector<XMFLOAT2> ButtonPosition_;
	CharacterSetUIFrame* pCFrame_;
};

