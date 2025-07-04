#pragma once
#include "GroupBase.h"
class IconGroup :
    public GroupBase
{
public:
	IconGroup(GameObject* parent);
	~IconGroup();
	void Initialize() override;
	void Update() override;
	void Draw() override;
private:

};

