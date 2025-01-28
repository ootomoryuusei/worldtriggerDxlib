#pragma once
#include "Object3D.h"
#include<vector>

using std::vector;

class TriggerSetUI :
    public Object3D
{
public:
	TriggerSetUI(GameObject* parent);
	~TriggerSetUI();
	void Update() override;
	void Draw() override;
private:
	SIZE_2D graphSize_; //アイコンの画像サイズ
	SIZE_2D SIFgraphSize; //キャラクターセレクトUIの画像サイズ
	vector<XMFLOAT2> SIUFPosition_;
	int hSlIcUIFrame_;
};

