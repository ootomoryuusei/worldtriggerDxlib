#include "CharacterIcons.h"
#include"Mouse.h"

CharacterIcons::CharacterIcons(GameObject* parent) : Icon(parent)
{
	csv_ = new CsvReader();
	csv_->Load("Assets//Character//CharacterStatus.csv");
	FN2DLine = 0;
	DLC = "Assets//Image//CharacterIcon//selectCIcon//";
	for (int x = 0; x < csv_->GetWidth(0); x++) {
		if (csv_->GetString(x, 0) == "FileName2D") {
			FN2DLine = x;
		}
	}
	for (int y = 1; y < csv_->GetHeight(); y++) {
		std::string graphName;
		graphName = csv_->GetString(FN2DLine, y);
		std::string flPath;
		flPath = DLC + graphName;
		CharacterIcon* pCIcon = Instantiate<CharacterIcon>(this);
		pCIcon->LoadSprite(flPath);
		OBJ_SIZE_F IconSize = pCIcon->GetGraphSizeF_2D();
		VECTOR graphPos = { 0,300 + IconSize.y * (y - 1) ,0 };
		pCIcon->SetPosition(graphPos);
		pCIcon->SetCreateNum(y);
		pCIcon->SetIconName(csv_->GetString(0, y));
		pCIcons_.push_back(pCIcon);
	}
}

CharacterIcons::~CharacterIcons()
{
}

void CharacterIcons::Update()
{
	//Mouse* pMouse = GetParent()->GetParent()->FindGameObject<Mouse>();
	//XMFLOAT2 mousePos = pMouse->GetMousePos();

	//// 1つだけ選択処理
	//for (auto& itr : pCIcons_) {
	//	XMFLOAT2 leftUp = { itr->GetPosition().x,itr->GetPosition().y };
	//	XMFLOAT2 distance = { itr->GetGraphSizeF_2D().x,itr->GetGraphSizeF_2D().y };
	//	if (PointInBox(mousePos, leftUp, distance)) {
	//		itr->SetSelecting(true); // 最初に見つけた1つだけ選択
	//		break; // 他の円弧は無視（同時選択防止）
	//	}
	//}
}

void CharacterIcons::Draw()
{
}
