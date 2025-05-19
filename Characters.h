#pragma once
#include "Object3D.h"
#include"Character.h"
#include<vector>

using std::vector;

class Characters :
    public Object3D
{
public:
	Characters(GameObject* parent);
	~Characters();
	void Initialize() override;
	void Update() override;
	void Draw() override;
private:
	vector<Character*> pCharacters;
};

