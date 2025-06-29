#pragma once
#include "Character.h"
#include "CharacterFactory.h"
#include"AutoRegister.h"

class Amatori_Chika :
    public Character
{
public:
	Amatori_Chika(GameObject* parent);
	~Amatori_Chika();
	void Initialize() override;
	void Update() override;
	void Draw() override;
private:
	static AutoRegister<Amatori_Chika,CharacterFactory> register_;
};

