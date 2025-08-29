#pragma once
#include"Object3D.h"
#include<vector>
#include "Tile.h"

using std::vector;

class Tiles : public Object3D
{
public:
	Tiles(GameObject* parent);
	~Tiles();
	void Initialize() override;
	void Update() override;
	void Draw() override;
private:
	vector<vector<Tile>> pTiles;
};

