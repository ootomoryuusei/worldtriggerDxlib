#include "Icon.h"

Icon::Icon(GameObject* parent) : Object2D(parent)
{
}

Icon::Icon(GameObject* parent,const string& name) : Object2D(parent,name)
{
}

Icon::~Icon()
{
}

void Icon::Update()
{
	Object2D::Update();
}

void Icon::Draw()
{
	Object2D::Draw();
#if 0
	DrawBoxAA(position.x, position.y, position.x + GetGraphSizeF_2D().x, position.y + GetGraphSizeF_2D().y, GetColor(255, 0, 0), FALSE);
#endif
}
