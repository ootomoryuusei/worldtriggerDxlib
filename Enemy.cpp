#include "Enemy.h"
#include"Engine/CsvReader.h"

Enemy::Enemy(GameObject* parent) : Object3D(parent)
{
}

Enemy::~Enemy()
{
}

void Enemy::Initialize()
{
	csv_ = new CsvReader();
	csv_->Load("Assets//Character//Character//CharacterStatus.csv");
	std::vector<int> randomselect;
    for (int x = 0; x < MAX_SELECT_CHARACTER; x++) {
        int num;
        bool selected = false;
        while (!selected) {
            num = GetRand(csv_->GetHeight()) + 1;
            selected = true; // ‰¼‚Éˆê“x true ‚É‚·‚é
            for (auto& itr : randomselect) {
                if (itr == num) {
                    selected = false; // ”í‚Á‚Ä‚½‚ç‚â‚è’¼‚·
                    break;
                }
            }
        }
        randomselect.push_back(num);
    }
}

void Enemy::Update()
{
}

void Enemy::Draw()
{
}
