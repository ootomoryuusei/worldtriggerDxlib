#pragma once
#include "Character.h"

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
};

