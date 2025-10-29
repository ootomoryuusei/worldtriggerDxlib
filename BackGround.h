#pragma once
#include "Icon.h"
class BackGround :
    public Icon
{
public:
	BackGround(GameObject* parent);
	~BackGround();
	void Update() override;
	void Draw() override;
private:

};

