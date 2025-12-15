#pragma once
#include "Icon.h"
#include<vector>

using std::vector;

class CharacterSetUIFrame;

class TriggerSetButton :
    public Icon
{
public:
	TriggerSetButton(GameObject* parent);
	~TriggerSetButton();
	void Update() override;
	void Draw() override;

	void DeviceEvent(const ClickEvent& event) override;

	bool GetClicked() { return clicked_; }
private:
	//SIZE_2D graphSize_; //アイコンの画像サイズ
	/*vector<XMFLOAT2> ButtonPosition_;
	CharacterSetUIFrame* pCFrame_;*/

	bool clicked_;
	bool prevClicked_;
};

