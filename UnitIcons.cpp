#include "UnitIcons.h"
#include"TileIcons.h"

UnitIcons::UnitIcons(GameObject* parent) : GameObject(parent),selectCharNum_(MAX_SELECT_CHARACTER,-1)
{

}

UnitIcons::~UnitIcons()
{
}

void UnitIcons::Initialize()
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

	int num = 0;
	for (int y = 0; y < MAX_SELECT_CHARACTER; y++) {
		std::string graphName;
		graphName = csv_->GetString(FN2DLine, selectCharNum_[y]);
		std::string flPath;
		DLC = "Assets//Image//CharacterIcon//CIcon//";
		flPath = DLC + graphName;
		VECTOR pos;
		for (int j = 0; j < 2; j++) {
			bool isSeted = false;
			UnitIcon* pUIcon = Instantiate<UnitIcon>(this);
			pUIcon->Load(flPath);
			while (!isSeted) {
				int randX = GetRand(MAX_MAP_WIDTH - 1);
				int randY = GetRand(0);
				pos = pTIcons->GetpTIcon()[randX + 1 * randY]->Get3DPosition();

				bool isOk = false;
				for (auto& itr : pUIcons_) {
					if (itr->Get3DPosition().x == pos.x && itr->Get3DPosition().y == pos.y && itr->Get3DPosition().z == pos.z) {
						isOk = true;
						break;
					}
				}
				if (!isOk) {
					isSeted = true;
				}
			}
			string IconName = graphName;
			pUIcon->SetIconName(IconName);
			pUIcon->Set3DPosition(pos);
			pUIcon->SetCreateNum(num);
			pUIcons_.push_back(pUIcon);
			num++;
		}
	}
}

void UnitIcons::Update()
{
}
