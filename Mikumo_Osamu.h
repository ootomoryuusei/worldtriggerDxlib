#pragma once
#include "Character.h"
#include"CharacterFactory.h"
#include"AutoRegister.h"

class Mikumo_Osamu :
    public Character
{
public:
	Mikumo_Osamu(GameObject* parent);
	~Mikumo_Osamu();
	void Update() override;
	void Draw() override;
private:
	static AutoRegister<Mikumo_Osamu,CharacterFactory> register_;
};
