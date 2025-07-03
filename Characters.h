#pragma once
#include "Engine/GameObject.h"
#include"Group.h"
#include"Character.h"
#include<vector>

using std::vector;

class Characters :
    public GameObject
{
public:
    Characters(GameObject* parent);
    void Initialize() override;

    Group<Character>* GetPlayerGroup() { return playerGroup_; }
    Group<Character>* GetEnemyGroup() { return enemyGroup_; }

    vector<Character*> GetAllCharacters() const;
private:
    Group<Character>* playerGroup_ = nullptr;
    Group<Character>* enemyGroup_ = nullptr;
};

