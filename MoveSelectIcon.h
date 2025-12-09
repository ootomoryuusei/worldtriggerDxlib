#pragma once
#include "Icon.h"

class MoveTypeIcons;

class MoveSelectIcon :
    public Object2D
{
public:
	MoveSelectIcon(GameObject* parent);
	~MoveSelectIcon();
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

	void UpdateSub() override;
	void DrawSub() override;

	void DeviceEvent(const DragEvent& event) override;
	const auto& GetpMoveTypeIcons() const { return pMoveTypeIcons_; }
private:
	MoveTypeIcons* pMoveTypeIcons_;
	/*string iconName;*/
	XMFLOAT2 space;
	float scale;
};

