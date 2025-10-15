#pragma once
#include "TypedGroup.h"
#include"TileIcon.h"
#include<vector>

class GroupManager;

using std::vector;

class TileIcons :
    public TypedGroup<TileIcon>
{
public:
	TileIcons(GameObject* parent);
	~TileIcons();
	void Initialize() override;
	void Update() override;
	const auto& GetpTIcon() const{ return pTIcons_; }
private:
	vector<vector<TileIcon*>> pTIcons_;
	GroupManager* pGroupManager_;
};

