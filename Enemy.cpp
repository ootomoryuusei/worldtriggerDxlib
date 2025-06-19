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
            selected = true; // ���Ɉ�x true �ɂ���
            for (auto& itr : randomselect) {
                if (itr == num) {
                    selected = false; // ����Ă����蒼��
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
