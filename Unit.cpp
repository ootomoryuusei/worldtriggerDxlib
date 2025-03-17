#include "Unit.h"

Unit::Unit(GameObject* parent) : Icon(parent)
{
	Load("Assets//Image//unit.png");
	/*position = {00, 0, 0 };*/
	canVisible_ = true;
}

Unit::~Unit()
{
}

void Unit::Update()
{
}
