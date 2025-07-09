#include "Enemy.h"
#include"Engine/CsvReader.h"
#include"CharacterGroup.h"
#include"Tile.h"

#include"CharacterFactory.h"

#include"GroupManager.h"


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

    auto* pGroupManager = GetParent()->FindGameObject<GroupManager>();
    auto* pEnemyGroup = pGroupManager->CreateGroup<CharacterGroup>("enemyGroup");

  
    for (auto& itr : selectCharacterName) {
        for (int i = 0;i < 2;i++) {
            Character* pCharacter = CharacterFactory::Instance().Create(itr, pEnemyGroup);
            auto pData = pCharacter->FindGameObject<CharacterData>();
            pData->SetName(itr);
            pData->DefaultSetStatus(itr);
            pData->DefaultSetMyTrigger(itr);
            pData->SetTarget("playerGroup");
            pCharacter->CreateTriggerInstance();
        }
    }

    list<Character*> characterlist = pEnemyGroup->FindGameObjects<Character>();
    pTile_ = GetParent()->FindGameObject<Tile>();
    for (auto& itr : characterlist) {
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
