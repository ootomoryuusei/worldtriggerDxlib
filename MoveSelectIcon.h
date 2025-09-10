#pragma once
#include "Icon.h"
class MoveSelectIcon :
    public Icon
{
public:
	MoveSelectIcon(GameObject* parent);
	~MoveSelectIcon();
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
private:
	/*string iconName;*/
	XMFLOAT2 space;
	float scale;
};

