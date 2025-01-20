#pragma once
#include "Character.h"
class Mikumo_Osamu :
    public Character
{
public:
	Mikumo_Osamu(GameObject* parent);
	~Mikumo_Osamu();
	void Update() override;
	void Draw() override;
private:
};

