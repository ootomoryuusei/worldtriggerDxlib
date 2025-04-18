#pragma once
#include "Icon.h"
#include<vector>

using std::vector;

class UnitIcon :
    public Icon
{
public:
	UnitIcon(GameObject* parent);
	~UnitIcon();
	void Initialize() override;
	void Update() override;
	void Draw() override;

	auto GetMoveMent() { return moveMent; }
	void SetMoveMent(int _moveMent) { moveMent.push_back(_moveMent); }
private:

	vector<int> moveMent;
};

