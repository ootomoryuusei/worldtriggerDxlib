#pragma once
#include "Icon.h"
#include<vector>

class TileIcon;
class GroupManager;

using std::vector;

class TileIcons :
    public Icon
{
public:
	TileIcons(GameObject* parent);
	~TileIcons();
	void Initialize() override;
	void Update() override;
	const auto& GetpTIcon() const{ return pTIcons_; }
private:
	vector<TileIcon*> pTIcons_;
	GroupManager* pGroupManager_;
};

