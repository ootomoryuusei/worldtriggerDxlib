#pragma once
#include"Object3D.h"
#include"Tile.h"
#include<vector>

using std::vector;

class Tiles : public Object3D
{
public:
	Tiles(GameObject* parent);
	~Tiles();
	void Initialize() override;
	void Update() override;
	void Draw() override;

	const auto& GetpTiles()const { return pTiles; }
private:
	vector<vector<Tile*>> pTiles;
};

