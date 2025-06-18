#pragma once
#include "Character.h"
class Kuga_Yuuma :
    public Character
{
public:
	Kuga_Yuuma(GameObject* parent);
	~Kuga_Yuuma();
	void Initialize() override;
	void Update() override;
	void Draw() override;
private:
};

