#include "UnitIcons.h"
#include"TileIcons.h"
#include"Mouse.h"
#include"MoveSelectIcon.h"
#include"MoveSetIcon.h"
#include"Engine/Global.h"

UnitIcons::UnitIcons(GameObject* parent) : Icon(parent)
{

}

UnitIcons::~UnitIcons()
{
	//SAFE_DELETE(pSelecting_ptr);
}

void UnitIcons::Initialize()
{
	TileIcons* pTIcons = GetParent()->FindGameObject<TileIcons>();

	csv_ = new CsvReader();
	csv_->Load("Assets//Character//SelectCharacter.csv");

	for (int y = 1;y < csv_->GetHeight();y++) {
		std::string graphName;
		graphName = csv_->GetString(0,y);
		std::string flPath;
		DLC = "Assets//Image//CharacterIcon//CIcon//";
		flPath = DLC + graphName + ".png";
		VECTOR pos;
		int tilenum;
		bool isSeted = false;
		UnitIcon* pUIcon = Instantiate<UnitIcon>(this);
		pUIcon->Load(flPath);
		while (!isSeted) {
			int randX = GetRand(MAX_MAP_WIDTH - 1);
			int randY = MAX_MAP_HIGHT -1;
			tilenum = randY * randY - randX;
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
		pUIcon->SetCreateNum(y - 1);
		pUIcon->AddMoveMent(tilenum);
		MYTRIGGER myTrigger;
		for (int x = 0;x < 4;x++) {
			string TriggerName = csv_->GetString(1 + x, y);
			myTrigger.myTrigger[0].trigger[x].triggerName = TriggerName;
		}
		for (int x = 0;x < 4;x++) {
			string TriggerName = csv_->GetString(5 + x, y);
			myTrigger.myTrigger[1].trigger[x].triggerName = TriggerName;
		}
		pUIcon->SetMyTrigger(myTrigger);
		pUIcons_.push_back(pUIcon);
	}
	canVisible_ = true;
	moveMentSet = false;

	pSelecting_ptr = nullptr;

	pMoveSelectIcon_ = GetParent()->FindGameObject<MoveSelectIcon>();
	pMoveSetIcon_ = GetParent()->FindGameObject<MoveSetIcon>();
}

void UnitIcons::Update()
{
	Mouse* pMouse = GetParent()->FindGameObject<Mouse>();
	XMFLOAT2 mousePos = pMouse->GetMousePos();

	// 全アイコンを初期化（表示ON・選択解除）
	for (auto& itr : pUIcons_) {
		if (!itr->GetCanVisible()) {
			itr->SetCanVisible(true);
		}
		itr->SetSelecting(false); // まず全て非選択にする
	}

	// 1つだけ選択処理
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

	if (moveMentSet) {	
		for (auto& itr : pUIcons_) {
			itr->SetStep(THIRD);
			/*moveMentSet = false;*/
		}
	}else {
		for (auto& itr : pUIcons_) {
			itr->SetCanVisible(false);
		}
	}

	for (auto& itr : pUIcons_) {
		if (itr->GetSet()) {
			pSelecting_ptr = itr;
			pMoveSelectIcon_->Enter(); //update許可
			pMoveSelectIcon_->Visible(); //draw許可
			pMoveSetIcon_->Enter(); //update許可
			pMoveSetIcon_->Visible(); //draw許可
		}
	}
	if (pSelecting_ptr != nullptr) {
		if (!pSelecting_ptr->GetSet()) {
			pSelecting_ptr = nullptr;
			pMoveSelectIcon_->Leave(); //update拒否
			pMoveSelectIcon_->Invisible(); //draw拒否
			pMoveSetIcon_->Leave(); //update拒否
			pMoveSetIcon_->Invisible(); //draw拒否
		}
	}
}
