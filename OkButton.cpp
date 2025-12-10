#include "OkButton.h"
#include"Engine/SceneManager.h"
#include"Player1.h"
#include"CharacterIcons.h"
#include<fstream>
#include<sstream>
#include "Mouse.h"

using std::ifstream;
using std::ofstream;
using std::ios;

OkButton::OkButton(GameObject* parent) : Object2D(parent)
{
	LoadSprite("Assets//Image//OkButton.png");
	transform_.position_ = { 1280 / 2 - graphSizeF_.halfX(),600,0};

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
			file << "-1" << std::endl;
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
	Object2D::Update();
}

void OkButton::Draw()
{
	Object2D::Draw();
}

void OkButton::DeviceEvent(const DoubleClickEvent& event)
{
	switch (event.button)
	{
	case LEFT:
		for (int i = 0; i < MAX_SELECT_CHARACTER; i++) {
			CharacterIcons* pCIcons = GetParent()->FindGameObject<CharacterIcons>();
			int num = 0;
			for (auto itr : pCIcons->GetpCIcons()) {
				string fileName = "Assets//Character//SelectCharacter.csv";
				int tartgerRow = i + 1;
				string newData = std::to_string(itr->GetCreateNum());
				updateCSVRow(fileName, tartgerRow, newData);
			}
		}
		SceneManager::Instance()->ChangeScene(SceneManager::SCENE_ID::SCENE_ID_SET);
		break;
	case RIGHT:
		break;
	case MIDDLE:
		break;
	default:
		break;
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