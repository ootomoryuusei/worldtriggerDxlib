#include "MoveTypeIcons.h"
#include"MoveSelectIcons.h"

MoveTypeIcons::MoveTypeIcons(GameObject* parent) : /*GameObject(parent,"MoveTypeIcons")*/ Icon(parent)
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
		VECTOR pos = pMoveSelectIcons->GetpMoveSelectIcons()[0]->Get3DPosition();
		XMFLOAT2 graphSize = { pMoveSelectIcons->GetpMoveSelectIcons()[0]->GetGraphSizeF_2D().x, pMoveSelectIcons->GetpMoveSelectIcons()[0]->GetGraphSizeF_2D().y };
		pMoveTypeIcon->Set3DPosition({pos.x, pos.y + (graphSize.y/2) * y, pos.z});
		pMoveTypeIcon->SetIconName(typeName);
		pMoveTypeIcon->SetFontHandle(fontHandle);
		pMoveTypeIcons_.push_back(pMoveTypeIcon);
	}
}

MoveTypeIcons::~MoveTypeIcons()
{
}

void MoveTypeIcons::Update()
{
}