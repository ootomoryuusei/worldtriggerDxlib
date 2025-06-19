#pragma once
#include "Object3D.h"
class CharacterData :
    public Object3D
{
public:
	CharacterData(GameObject* parent);
	~CharacterData();
	void Initialize() override;
	void Update() override;
	void Draw() override;
private:
};

