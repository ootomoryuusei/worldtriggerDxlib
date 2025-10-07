#include "MoveTypeIcons.h"
#include"MoveSelectIcon.h"
#include"MoveTypeIcon.h"

MoveTypeIcons::MoveTypeIcons(GameObject* parent) : Icon(parent)
{
}

MoveTypeIcons::~MoveTypeIcons()
{
}

void MoveTypeIcons::Initialize()
{
	int fontSize = 32;
	int fontThickness = 5;
	fontHandle_ = CreateFontToHandle("行動タイプフォント", fontSize, fontThickness, DX_FONTTYPE_NORMAL);

	csv_ = new CsvReader();
	csv_->Load("Assets//Character//CharacterMoveTypes.csv");
	FNMTLine = 0;
	for (int x = 0; x < csv_->GetWidth(0); x++) {
		if (csv_->GetString(x, 0) == "MoveTypes") {
			FNMTLine = x;
		}
	}

	for (int y = 1; y < csv_->GetHeight(); y++) {
		std::string typeName;
		typeName = csv_->GetString(FNMTLine, y);
		MoveTypeIcon* pMoveTypeIcon = Instantiate<MoveTypeIcon>(this);
		MoveSelectIcon* pMoveSelectIcon = GetParent()->GetParent()->FindGameObject<MoveSelectIcon>();
		VECTOR pos = pMoveSelectIcon->Get3DPosition();
		XMFLOAT2 graphSize = { pMoveSelectIcon->GetGraphSizeF_2D().x, pMoveSelectIcon->GetGraphSizeF_2D().y };
		pMoveTypeIcon->Set3DPosition({ pos.x, pos.y + (graphSize.y / 2) * y, pos.z });
		pMoveTypeIcon->SetIconName(typeName);
		pMoveTypeIcon->SetFontHandle(fontHandle_);
		pMoveTypeIcons_.push_back(pMoveTypeIcon);
	}
	pSelectMovetypeIcon_ = nullptr;
}

void MoveTypeIcons::Update()
{
	for (int y = 1; y < csv_->GetHeight(); y++) {
		MoveSelectIcon* pMoveSelectIcon = GetParent()->GetParent()->FindGameObject<MoveSelectIcon>();
		VECTOR pos = pMoveSelectIcon->Get3DPosition();
		XMFLOAT2 graphSize = { pMoveSelectIcon->GetGraphSizeF_2D().x, pMoveSelectIcon->GetGraphSizeF_2D().y };
		pMoveTypeIcons_[y - 1]->Set3DPosition({ pos.x, pos.y + (graphSize.y / 2) * y, pos.z });
	}

	for (auto& itr : pMoveTypeIcons_) {
		if (itr->GetClicked()) {
			pSelectMovetypeIcon_ = itr;
			return;
		}
	}
}

void MoveTypeIcons::Draw()
{
}

void MoveTypeIcons::UpdateSub()
{
	for (auto* child : *GetChildList()) {
		if (IsEntered()) {
			child->Enter();
		}
		else {
			child->Leave();
		}
	}

	GameObject::UpdateSub();
}

void MoveTypeIcons::DrawSub()
{
	for (auto* child : *GetChildList()) {
		if (IsVisibled()) {
			child->Visible();
		}
		else {
			child->Invisible();
		}
	}

	GameObject::DrawSub();
}
