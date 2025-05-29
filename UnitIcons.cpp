#include "UnitIcons.h"
#include"TileIcons.h"
#include"Mouse.h"

UnitIcons::UnitIcons(GameObject* parent) : Icon(parent),selectCharNum_(MAX_SELECT_CHARACTER*2,-1)
{

}

UnitIcons::~UnitIcons()
{
	delete (pSelecting_ptr);
}

void UnitIcons::Initialize()
{
	TileIcons* pTIcons = GetParent()->FindGameObject<TileIcons>();

	csv_ = new CsvReader();
	csv_->Load("Assets//Character//SelectCharacter.csv");

	for (int y = 0; y < MAX_SELECT_CHARACTER * 2; y++) {
		selectCharNum_[y] = (csv_->GetInt(0, y + 1));
	}

	

	int num = 0;
	for (int y = 0; y < selectCharNum_.size(); y++) {
		csv_->Load("Assets//Character//CharacterStatus.csv");
		std::string graphName;
		graphName = csv_->GetString(1, selectCharNum_[y]);
		std::string flPath;
		DLC = "Assets//Image//CharacterIcon//CIcon//";
		flPath = DLC + graphName;
		VECTOR pos;
		int tilenum;
		bool isSeted = false;
		UnitIcon* pUIcon = Instantiate<UnitIcon>(this);
		pUIcon->Load(flPath);
		while (!isSeted) {
			int randX = GetRand(MAX_MAP_WIDTH - 1);
			int randY = GetRand(0);
			tilenum = randX + 1 * randY;
			pos = pTIcons->GetpTIcon()[tilenum]->Get3DPosition();

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
		pUIcon->SetMoveMent(tilenum);
		MYTRIGGER myTrigger;
		for (int x = 0;x < 4;x++) {
			string TriggerName = csv_->GetString(10 + x, selectCharNum_[y]);
			myTrigger.myTrigger[0].trigger[x].triggerName = TriggerName;
		}
		for (int x = 0;x < 4;x++) {
			string TriggerName = csv_->GetString(14 + x, selectCharNum_[y]);
			myTrigger.myTrigger[1].trigger[x].triggerName = TriggerName;
		}
		pUIcon->SetMyTrigger(myTrigger);
		pUIcons_.push_back(pUIcon);
		num++;
	}
	canVisible_ = true;
	moveMentSet = false;
}

void UnitIcons::Update()
{
	Mouse* pMouse = GetParent()->FindGameObject<Mouse>();
	XMFLOAT2 mousePos = pMouse->GetMousePos();

	if (canVisible_) {
		// 全アイコンを初期化（表示ON・選択解除）
		for (auto& itr : pUIcons_) {
			if (!itr->GetCanVisible()) {
				itr->SetCanVisible(true);
			}
			itr->SetSelecting(false); // まず全て非選択にする
		}

		// 1つだけ選択処理
		if (pSelecting_ptr != nullptr) {
			if (pMouse->IsPressed(Mouse::LEFT)) {
				pSelecting_ptr->SetSelecting(true);
				return;
			}
			else {
				pSelecting_ptr = nullptr;
			}
		}


		for (auto itr = pUIcons_.rbegin();itr != pUIcons_.rend();++itr) {
			XMFLOAT2 leftUp = { (*itr)->Get3DPosition().x,(*itr)->Get3DPosition().y };
			XMFLOAT2 distance = { (*itr)->GetGraphSizeF_2D().x,(*itr)->GetGraphSizeF_2D().y };
			if (PointInBox(mousePos, leftUp, distance)) {
				pSelecting_ptr = *itr;
				pSelecting_ptr->SetSelecting(true);
				break;
			}
			
		}

		if (moveMentSet) {
			for (auto& itr : pUIcons_) {
				itr->SetStep(THIRD);
				moveMentSet = false;
			}
		}
	}
	else {
		for (auto& itr : pUIcons_) {
			itr->SetCanVisible(false);
		}
	}
}
