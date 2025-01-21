#pragma once
#include "Object3D.h"
class Weapon :
    public Object3D
{
public:
	Icon(GameObject* parent);
	~Icon();
	void Update() override;
	void Draw() override;
private:
};

