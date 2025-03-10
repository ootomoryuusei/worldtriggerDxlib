#include "Icons.h"
#include "TriggerIcons.h"
#include"CharacterSelectUI.h"
#include"TriggerSetButton.h"
#include"Engine/CsvReader.h"

Icons::Icons(GameObject* parent) : Object3D(parent)
{
	for (int i = 0; i < MAX_SELECT_CHARACTER; i++) { //キャラクター分のトリガーセットUIを実体化
		TriggerSetUI* pTSUI = Instantiate<TriggerSetUI>(this);
		pTSUIs_.push_back(pTSUI);
	}
	Instantiate<CharacterSelectUI>(this);

	csv_ = new CsvReader();


	for (int i = 0; i < MAX_SELECT_CHARACTER; i++) { //キャラクター分のトリガーアイコンを実体化
		TriggerIcons* pTIcons = Instantiate<TriggerIcons>(this);
		pTIcons_.push_back(pTIcons);
	}

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
		pCIcon->Load(flPath);
		SIZE_2D IconSize = pCIcon->GetIconSize();
		VECTOR graphPos = { 0,300 + IconSize.y * (y - 1) ,0 };
		pCIcon->SetInitialPosition(graphPos);
		pCIcon->Set3DPosition(graphPos);
		pCIcons_.push_back(pCIcon);
	}

	for (int x = 0; x < MAX_SELECT_CHARACTER; x++) { //CharacerSetのフレームの位置決めとButtonの位置決め
		CharacterSetUIFrame* pCsuif = Instantiate<CharacterSetUIFrame>(this);
		VECTOR graphPos = { 780.0f + (pCsuif->GetGraphSizeF_2D().x + 30.0f) * x, 500 ,0 };
		pCsuif->Set3DPosition(graphPos);
		pCSUIFrames_.push_back(pCsuif);
		TriggerSetButton* pTsb = Instantiate<TriggerSetButton>(this);
		VECTOR ButtonPos = { graphPos.x + 10,graphPos.y + pCsuif->GetGraphSizeF_2D().y + 10 };
		pTsb->Set3DPosition(ButtonPos);
		pTSButtons_.push_back(pTsb);
	}

	//for (int x = 0; x < MAX_TRIGGER_HANDS; x++) { //TriggerSetのフレームの位置決め
	//	for (int y = 0; y < MAX_CAN_SET_TRIGGER; y++) {
	//		TriggerSetUIFrame* pTsuif = Instantiate<TriggerSetUIFrame>(this);;
	//		VECTOR graphPos = { 780.0f + 330.0f * x, 50.0f + (pTsuif->GetGraphSizeF_2D().y + 10) * y,0 };
	//		pTsuif->Set3DPosition(graphPos);
	//		pTSUIFrames_.push_back(pTsuif);
	//	}
	//}
	for (int i = 0; i < MAX_SELECT_CHARACTER; i++) {
		TriggerSetUIFrames* pTSUIFs = Instantiate<TriggerSetUIFrames>(this);
		pTSUIFSs_.push_back(pTSUIFs);
	}

	for (int y = 0; y < pCIcons_.size(); y++) { //button_の初期化
		std::vector<bool> CsSize;
		for (int x = 0; x < MAX_SELECT_CHARACTER; x++) {
			CsSize.push_back(false);
		}
		button_.push_back(CsSize);
	}
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
	size_t index = 0;
	for (auto itr : pTSButtons_) { //ボタンをクリックしたらトリガーセットできるようにフラグを立てる
		if (itr->GetClicked()) {
			pTSUIs_[index]->SetCanVisible(true);
			for (auto itr : pTSUIFSs_[index]->GetpTSUIFrames()) {
				itr->SetCanVisible(true);
			}
			pTIcons_[index]->SetCanVisible(true);
		}
		else {
			pTSUIs_[index]->SetCanVisible(false);
			for (auto itr : pTSUIFSs_[index]->GetpTSUIFrames()) {
				itr->SetCanVisible(false);
			}
			pTIcons_[index]->SetCanVisible(false);
		}
		index++;
	}

	index = 0;
	for (auto itr : pCIcons_) { //キャラクターがフレームにセットされたらボタンが見えるようにフラグを立てる
		for (int i = 0; i < MAX_SELECT_CHARACTER; i++) {
			if (itr->GetAlreadySet(i)) {
				button_[index][i] = true;
			}
			else {
				button_[index][i] = false;
			}
		}
		index++;
	}

	for (int x = 0; x < MAX_SELECT_CHARACTER; x++) {
		for (int y = 0; y < pCIcons_.size(); y++) {
			if (button_[y][x]) {
				pTSButtons_[x]->SetCanVisible(true);
				return;
			}
			else if (!button_[y][x]) {
				pTSButtons_[x]->SetCanVisible(false);
			}
		}
	}
}

void Icons::Draw()
{
}
