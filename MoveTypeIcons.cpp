#include "MoveTypeIcons.h"
#include"MoveSelectIcons.h"

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
	int fontHandle = CreateFontToHandle("行動タイプフォント", fontSize, fontThickness, DX_FONTTYPE_NORMAL);

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
		MoveSelectIcons* pMoveSelectIcons = GetParent()->GetParent()->FindGameObject<MoveSelectIcons>();
		VECTOR pos = pMoveSelectIcons->GetpMoveSelectIcons()[createNum_]->Get3DPosition();
		XMFLOAT2 graphSize = { pMoveSelectIcons->GetpMoveSelectIcons()[createNum_]->GetGraphSizeF_2D().x, pMoveSelectIcons->GetpMoveSelectIcons()[0]->GetGraphSizeF_2D().y };
		pMoveTypeIcon->Set3DPosition({ pos.x, pos.y + (graphSize.y / 2) * y, pos.z });
		pMoveTypeIcon->SetIconName(typeName);
		pMoveTypeIcon->SetFontHandle(fontHandle);
		pMoveTypeIcons_.push_back(pMoveTypeIcon);
	}
}

void MoveTypeIcons::Update()
{
	for (int y = 1; y < csv_->GetHeight(); y++) {
		MoveSelectIcons* pMoveSelectIcons = GetParent()->GetParent()->FindGameObject<MoveSelectIcons>();
		VECTOR pos = pMoveSelectIcons->GetpMoveSelectIcons()[createNum_]->Get3DPosition();
		XMFLOAT2 graphSize = { pMoveSelectIcons->GetpMoveSelectIcons()[createNum_]->GetGraphSizeF_2D().x, pMoveSelectIcons->GetpMoveSelectIcons()[0]->GetGraphSizeF_2D().y };
		pMoveTypeIcons_[y-1]->Set3DPosition({pos.x, pos.y + (graphSize.y / 2) * y, pos.z});
	}
}