#include "UnitIcons.h"
#include"TileIcons.h"

UnitIcons::UnitIcons(GameObject* parent) : GameObject(parent),selectCharNum_(MAX_SELECT_CHARACTER,-1)
{
	TileIcons* pTIcons = GetParent()->FindGameObject<TileIcons>();

	csv_ = new CsvReader();
	csv_->Load("Assets//Character//SelectCharacter.csv");
	FNSCNLine = 0;
	for (int x = 0; x < csv_->GetWidth(0); x++) {
		if (csv_->GetString(x, 0) == "SelectCharacterNum") {
			FNSCNLine = x;
		}
	}

	for (int y = 0; y < MAX_SELECT_CHARACTER; y++) {
		selectCharNum_[y] = (csv_->GetInt(FNSCNLine, y + 1));
	}

	csv_->Load("Assets//Character//CharacterStatus.csv");

	FN2DLine = 0;
	for (int x = 0; x < csv_->GetWidth(0); x++) {
		if (csv_->GetString(x, 0) == "FileName2D") {
			FN2DLine = x;
		}
	}


	for (int y = 0; y < MAX_SELECT_CHARACTER; y++) {
		std::string graphName;
		graphName = csv_->GetString(FN2DLine, selectCharNum_[y]);
		std::string flPath;
		DLC = "Assets//Image//CharacterIcon//CIcon//";
		flPath = DLC + graphName;
		for (int j = 0; j < 2; j++) {
			UnitIcon* pUIcon = Instantiate<UnitIcon>(this);
			pUIcon->Load(flPath);
			int randX = GetRand(MAX_MAP_WIDTH - 1);
			int randY = GetRand(1);
			VECTOR pos = pTIcons->GetpTIcon()[randX + 1 * randY]->Get3DPosition();
			VECTOR center;
			/*center = { pos.x + pUIcon->GetGraphSizeF_2D().halfX,pos.y + pUIcon->GetGraphSizeF_2D().halfY,pos.z };*/
			pUIcon->Set3DPosition(pos);
			pUIcons_.push_back(pUIcon);
		}
	}
}

UnitIcons::~UnitIcons()
{
}

void UnitIcons::Update()
{
}
