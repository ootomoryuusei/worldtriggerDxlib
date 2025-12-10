#include "UnitIcons.h"
#include"TileIcons.h"
#include"Mouse.h"
#include"GroupManager.h"
#include"Map.h"
#include"Engine/Global.h"

UnitIcons::UnitIcons(GameObject* parent) : Object2D(parent)
{

}

UnitIcons::~UnitIcons()
{
	//SAFE_DELETE(pSelecting_ptr);
}

void UnitIcons::Initialize()
{
	const auto& pMap = GetParent()->FindGameObject<Map>();
	pGroupManager_ = GetParent()->FindGameObject<GroupManager>();
	const auto& pTIcons = dynamic_cast<TileIcons*>(pGroupManager_->GetGroup("TileIconGroup"));

	csv_ = new CsvReader();
	csv_->Load("Assets//Character//SelectCharacter.csv");

	for (int y = 1;y < csv_->GetHeight();y++) {
		std::string graphName;
		graphName = csv_->GetString(0,y);
		std::string flPath;
		DLC = "Assets//Image//CharacterIcon//CIcon//";
		flPath = DLC + graphName + ".png";
		XMFLOAT3 pos;
		int tilenum;
		bool isSeted = false;
		UnitIcon* pUIcon = Instantiate<UnitIcon>(this);
		pUIcon->LoadSprite(flPath);
		VECTOR rand = {0,0,0};
		while (!isSeted) {
			rand.x = GetRand(MAX_MAP_WIDTH - 1);
			rand.y = MAX_MAP_HIGHT -1;
			pos = pTIcons->GetpTIcon()[rand.y][rand.x]->GetPosition();

			bool isOk = false;
			for (auto& itr : pUIcons_) {
				if (itr->GetPosition() == pos) {
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
		pUIcon->SetPosition(pos);
		pUIcon->SetCreateNum(y - 1);
		pUIcon->AddMoveMent(rand,"");
		MYTRIGGER myTrigger;
		for (int x = 0;x < 4;x++) {
			string TriggerName = csv_->GetString(1 + x, y);
			myTrigger.myTrigger[RIGHT].trigger[x].triggerName = TriggerName;
		}
		for (int x = 0;x < 4;x++) {
			string TriggerName = csv_->GetString(5 + x, y);
			myTrigger.myTrigger[LEFT].trigger[x].triggerName = TriggerName;
		}
		pUIcon->SetMyTrigger(myTrigger);
		pUIcons_.push_back(pUIcon);
	}
	moveMentSet = false;

	pSelecting_ptr = nullptr;

	pMoveSelectIcon_ = GetParent()->FindGameObject<MoveSelectIcon>();
	pMoveSetIcon_ = GetParent()->FindGameObject<MoveSetIcon>();
}

void UnitIcons::Update()
{
	// 1‚Â‚¾‚¯‘I‘ðˆ—
	/*if (pSelecting_ptr != nullptr) {
		if (pMouse->IsPressed(Mouse::LEFT)) {
			pSelecting_ptr->SetSelecting(true);
			return;
		}else {
			pSelecting_ptr = nullptr;
		}
	}*/


	/*for (auto itr = pUIcons_.rbegin();itr != pUIcons_.rend();++itr) {
		XMFLOAT2 leftUp = { (*itr)->Get3DPosition().x,(*itr)->Get3DPosition().y };
		XMFLOAT2 distance = { (*itr)->GetGraphSizeF_2D().x,(*itr)->GetGraphSizeF_2D().y };
		if (PointInBox(mousePos, leftUp, distance)) {
			pSelecting_ptr = *itr;
			pSelecting_ptr->SetSelecting(true);
			break;
		}		
	}*/

	for (auto& itr : pUIcons_) {
		if (itr->GetSet()) {
			pSelecting_ptr = itr;
			pMoveSelectIcon_->Enter(); //update‹–‰Â
			pMoveSelectIcon_->Visible(); //draw‹–‰Â
			pMoveSetIcon_->Enter(); //update‹–‰Â
			pMoveSetIcon_->Visible(); //draw‹–‰Â
		}
	}
	if (pSelecting_ptr != nullptr) {
		if (!pSelecting_ptr->GetSet()) {
			pSelecting_ptr = nullptr;
			pMoveSelectIcon_->Leave(); //update‹‘”Û
			pMoveSelectIcon_->Invisible(); //draw‹‘”Û
			pMoveSetIcon_->Leave(); //update‹‘”Û
			pMoveSetIcon_->Invisible(); //draw‹‘”Û
		}
	}
}
