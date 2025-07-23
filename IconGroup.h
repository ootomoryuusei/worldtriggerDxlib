#pragma once
#include "TypedGroup.h"
#include"Icon.h"

class IconGroup :
	public TypedGroup<Icon>
{
public:
	IconGroup(GameObject* parent);
	~IconGroup();
	void Initialize() override;
	void Update() override;
	void Draw() override;
private:
};


