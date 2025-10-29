#include "Icon.h"

Icon::Icon(GameObject* parent) : Object3D(parent)
{
}

Icon::Icon(GameObject* parent,const string& name) : Object3D(parent,name)
{
}

Icon::~Icon()
{
}

void Icon::Update()
{
}

void Icon::Draw()
{
	DrawGraph(position.x, position.y, hModel, TRUE);
#if 0
	DrawBoxAA(position.x, position.y, position.x + GetGraphSizeF_2D().x, position.y + GetGraphSizeF_2D().y, GetColor(255, 0, 0), FALSE);
#endif
}

void Icon::Load(const std::string& _fileName)
{
	fileName_ = _fileName;
	hModel = LoadGraph(fileName_.c_str());
	assert(hModel >= 0);
	GetGraphSize(hModel,  &graphSize_.x, &graphSize_.y);
	graphSize_.halfX = graphSize_.x / 2;
	graphSize_.halfY = graphSize_.y / 2;
	graphSizeF_ = {(float)graphSize_.x,(float)graphSize_.y, (float)graphSize_.halfX, (float)graphSize_.halfY};
}

bool Icon::IsInMousePoint(XMFLOAT2 m_pos)
{
	if (PointInBox(m_pos, { position.x, position.y }, { graphSizeF_.x,graphSizeF_.y })) {
		return true;
	}
	return false;
}
