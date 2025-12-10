#pragma once
#include "Object2D.h"
class BackGround :
    public Object2D
{
public:
	BackGround(GameObject* parent);
	~BackGround();
	void Update() override;
	void Draw() override;
private:

};

