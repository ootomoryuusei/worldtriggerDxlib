#include "OkButton.h"
#include"Engine/SceneManager.h"
#include"Player1.h"
#include"CharacterIcons.h"
#include<fstream>
#include<sstream>

using std::ifstream;
using std::ofstream;
using std::ios;

OkButton::OkButton(GameObject* parent) : Icon(parent)
{
	Load("Assets//Image//OkButton.png");
	position = { 1280 / 2 - GetGraphSizeF_2D().halfX,600,0 };
	canVisible_ = false;

	// ファイルを開く（上書きモード）
	std::ofstream file("Assets//Character//SelectCharacter.csv", std::ios::trunc);

	// ファイルが開けたか確認
	assert(file.is_open());

	// 一行ずつ書き込む
	for (int i = 0; i < MAX_SELECT_CHARACTER + 1; i++) {
		if (i == 0) {
			file << "SelectCharacterNum" << std::endl;
		}
		else {
			file << "NONE" << std::endl;
		}
	}
	// ファイルを閉じる
	file.close();
}

OkButton::~OkButton()
{
}

void OkButton::Update()
{
	if (canVisible_) {
		Player1* pPl1 = GetParent()->GetParent()->FindGameObject<Player1>();
		XMFLOAT2 mousePos = pPl1->GetMousePos();
		if (PointInBox(mousePos, { position.x,position.y }, { graphSizeF_.x,graphSizeF_.y })) {
			if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {
				for (int i = 0; i < MAX_SELECT_CHARACTER; i++) {
					CharacterIcons* pCIcons = GetParent()->FindGameObject<CharacterIcons>();
					int num = 0;
					for (auto itr : pCIcons->GetpCIcons()) {
						if (itr->GetInFrame()[i] == true) {
							string fileName = "Assets//Character//SelectCharacter.csv";
							int tartgerRow = i + 1;
							string newData = std::to_string(itr->GetNum());
							updateCSVRow(fileName, tartgerRow, newData);
						}
					}
				
				}
				SceneManager::Instance()->ChangeScene(SceneManager::SCENE_ID::SCENE_ID_PLAY);
			}
		}
	}
}

void OkButton::Draw()
{
	if (canVisible_) {
		DrawGraph(position.x, position.y, hModel, TRUE);
	}
}

void OkButton::updateCSVRow(const string& filename, int targetRow, const string& newData)
{
	ifstream file(filename);
	vector<string> rows;
	string line;
	int currentRow = 0;

	// ?? ファイルを1行ずつ読み込み、行データを保存
	while (getline(file, line)) {
		if (currentRow == targetRow) {
			rows.push_back(newData);  // ?? 指定行を新データに置き換え
		}
		else {
			rows.push_back(line);  // その他の行はそのまま
		}
		currentRow++;
	}
	file.close();

	// ?? ファイルを上書きモードで開いて、全データを書き直す
	ofstream outFile(filename, ios::trunc);
	for (const auto& row : rows) {
		outFile << row << "\n";
	}
	outFile.close();
}