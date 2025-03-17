#include "Icons.h"
#include"CharacterIcons.h"
#include "TriggerIcons.h"
#include"CharacterSelectUI.h"
#include"CharacterSetUIFrames.h"
#include"TriggerSetButton.h"
#include"OkButton.h"
#include"BackGround.h"
#include"Engine/CsvReader.h"

Icons::Icons(GameObject* parent) : Object3D(parent)
{
	Instantiate<BackGround>(this);
	Instantiate<CharacterSelectUI>(this);

	/*csv_ = new CsvReader();*/


	
	
	Instantiate<CharacterIcons>(this);
	//for (int x = 0; x < MAX_TRIGGER_HANDS; x++) { //TriggerSetのフレームの位置決め
	//	for (int y = 0; y < MAX_CAN_SET_TRIGGER; y++) {
	//		TriggerSetUIFrame* pTsuif = Instantiate<TriggerSetUIFrame>(this);;
	//		VECTOR graphPos = { 780.0f + 330.0f * x, 50.0f + (pTsuif->GetGraphSizeF_2D().y + 10) * y,0 };
	//		pTsuif->Set3DPosition(graphPos);
	//		pTSUIFrames_.push_back(pTsuif);
	//	}
	//}
	Instantiate<CharacterSetUIFrames>(this);
	Instantiate<OkButton>(this);
	//for (int y = 0; y < pCIcons_.size(); y++) { //button_の初期化
	//	std::vector<bool> CsSize;
	//	for (int x = 0; x < MAX_SELECT_CHARACTER; x++) {
	//		CsSize.push_back(false);
	//	}
	//	button_.push_back(CsSize);
	//}
}

Icons::~Icons()
{
}

void Icons::Update()
{
	//if (CheckHitKey(KEY_INPUT_RETURN)) { //Enterを押すとiconを置いた場所にtriggerがセットされる
	//	for (auto itr : pTIcons_) {
	//		int TriggerNameNum = 0;
	//		for (int y = 1; y < csv_->GetHeight(); y++) {
	//			int num = itr->GetFileName().find(DLC);
	//			std::string fOnlyName = itr->GetFileName().erase(num, DLC.size());
	//			if (fOnlyName == csv_->GetString(FN2DLine, y)) {
	//				TriggerNameNum = y;
	//			}
	//		}
	//		if (itr->GetSettingNum() > MAX_CAN_SET_TRIGGER -1) {
	//			int mainNum = itr->GetSettingNum() - MAX_CAN_SET_TRIGGER;
	//			trigger.Main[mainNum].trigger = csv_->GetString(0, TriggerNameNum);
	//		}
	//		else {
	//			int subNum = itr->GetSettingNum();
	//			trigger.Sub[subNum].trigger = csv_->GetString(0, TriggerNameNum);
	//		}


	//	}
	//}
	//size_t index = 0;
	//for (auto itr : pTSButtons_) { //ボタンをクリックしたらトリガーセットできるようにフラグを立てる
	//	if (itr->GetClicked()) {
	//		pTSUIs_[index]->SetCanVisible(true);
	//		for (auto itr : pTSUIFSs_[index]->GetpTSUIFrames()) {
	//			itr->SetCanVisible(true);
	//		}
	//		pTIcons_[index]->SetCanVisible(true);
	//	}
	//	else {
	//		pTSUIs_[index]->SetCanVisible(false);
	//		for (auto itr : pTSUIFSs_[index]->GetpTSUIFrames()) {
	//			itr->SetCanVisible(false);
	//		}
	//		pTIcons_[index]->SetCanVisible(false);
	//	}
	//	index++;
	//}

	//index = 0;
	//for (auto itr : pCIcons_) { //キャラクターがフレームにセットされたらボタンが見えるようにフラグを立てる
	//	for (int i = 0; i < MAX_SELECT_CHARACTER; i++) {
	//		if (itr->GetAlreadySet(i)) {
	//			button_[index][i] = true;
	//		}
	//		else {
	//			button_[index][i] = false;
	//		}
	//	}
	//	index++;
	//}

	/*for (int x = 0; x < MAX_SELECT_CHARACTER; x++) {
		for (int y = 0; y < pCIcons_.size(); y++) {
			if (button_[y][x]) {
				pTSButtons_[x]->SetCanVisible(true);
				return;
			}
			else if (!button_[y][x]) {
				pTSButtons_[x]->SetCanVisible(false);
			}
		}
	}*/
}

void Icons::Draw()
{
}
