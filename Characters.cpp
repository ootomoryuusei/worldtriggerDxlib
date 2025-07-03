#include "Characters.h"

Characters::Characters(GameObject* parent) : GameObject(parent,"Characters")
{
}

void Characters::Initialize()
{
	playerGroup_ = Instantiate<Group<Character>>(this);
    enemyGroup_ = Instantiate<Group<Character>>(this);
}

vector<Character*> Characters::GetAllCharacters() const
{
    vector<Character*> all;
    if (playerGroup_) {
        const auto& players = playerGroup_->GetAll();
        all.insert(all.end(), players.begin(), players.end());
    }
    if (enemyGroup_) {
        const auto& enemies = enemyGroup_->GetAll();
        all.insert(all.end(), enemies.begin(), enemies.end());
    }
    return all;
}
