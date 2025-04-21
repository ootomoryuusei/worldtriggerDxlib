#pragma once
#include "Icon.h"
class MoveMentsLoad :
    public Icon
{
public:
	MoveMentsLoad(GameObject* parent);
	~MoveMentsLoad();
	void Initialize() override;
	void Update() override;
	void Draw() override;

private:

};

