#pragma once
#include "TypedGroup.h"
#include"TileIcon.h"
#include<vector>

class GroupManager;
class Mouse;

using std::vector;

class TileIcons :
    public TypedGroup<TileIcon>
{
public:
	TileIcons(GameObject* parent);
	~TileIcons();
	void Initialize() override;
	void Update() override;
	void Draw() override;
	const auto& GetpTIcon() const{ return pTIcons_; }
private:
	vector<vector<TileIcon*>> pTIcons_;
	Mouse* pMouse_;
};

