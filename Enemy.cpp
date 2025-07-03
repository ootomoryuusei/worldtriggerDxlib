#include "Enemy.h"
#include"Engine/CsvReader.h"
#include"CharacterGroup.h"
#include"Tile.h"

#include"CharacterFactory.h"

#include"Characters.h"


Enemy::Enemy(GameObject* parent) : Object3D(parent)
{
}

Enemy::~Enemy()
{
}

void Enemy::Initialize()
{
	csv_ = new CsvReader();
	csv_->Load("Assets//Character//CharacterStatus.csv");
	std::vector<int> randomselect;
    std::vector<string> selectCharacterName;
    for (int x = 0; x < MAX_SELECT_CHARACTER; x++) {
        int num;
        bool selected = false;
        while (!selected) {
            num = GetRand(csv_->GetHeight() - 2) + 1;
            selected = true; // ‰¼‚Éˆê“x true ‚É‚·‚é
            for (auto& itr : randomselect) {
                if (itr == num) {
                    selected = false; // ”í‚Á‚Ä‚½‚ç‚â‚è’¼‚·
                    break;
                }
            }
        }
        randomselect.push_back(num);
        selectCharacterName.push_back(csv_->GetString(0, num));
    }

    Characters* pCharacter = GetParent()->FindGameObject<Characters>();
    Group<Character>* enemyGroup = pCharacter->GetEnemyGroup();

    for (auto& itr : selectCharacterName) {
        for (int i = 0;i < 2;i++) {
            Character* pChracter = CharacterFactory::Instance().Create(itr, enemyGroup);
        }
    }

    pTile_ = GetParent()->FindGameObject<Tile>();
    list<Character*> characters = pCharacters_->FindGameObjects<Character>();
    for (auto& itr : characters) {
        int rand_posX = GetRand(pTile_->GetTileX());
        int rand_posY = GetRand(1);
        rand_posY = rand_posY + (pTile_->GetTileX() - 2);
        VECTOR initialPosition = pTile_->GetTilesData(rand_posX,rand_posY).position;
        itr->Set3DPosition(initialPosition);
        itr->SetRotateY(90.0f);
    }
}

void Enemy::Update()
{
}

void Enemy::Draw()
{
}
