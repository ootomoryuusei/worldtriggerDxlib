#include "Map.h"

Map::Map(GameObject* parent) : Icon(parent)
{
	Load("Assets//Image//Map.png");
	position = { 5, 20, 0 };
	canVisible_ = true;
}

Map::~Map()
{
}

void Map::Update()
{
}
