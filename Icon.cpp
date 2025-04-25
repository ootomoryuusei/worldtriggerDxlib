#include "Icon.h"

Icon::Icon(GameObject* parent) : Object3D(parent)
{
	/*hModel = LoadGraph(fileName_.c_str());
	assert(hModel >= 0);
	GetGraphSize(hModel, &graphSize_.x, &graphSize_.y);
	graphSizeF_ = { (float)graphSizeF_.x,(float)graphSizeF_.y, (float)graphSizeF_.halfX, (float)graphSizeF_.halfY };*/
}

Icon::~Icon()
{
}

void Icon::Update()
{
}

void Icon::Draw()
{
	if (canVisible_) {
		DrawGraph(position.x, position.y, hModel, TRUE);
#if 0
		DrawBoxAA(position.x, position.y, position.x + GetGraphSizeF_2D().x, position.y + GetGraphSizeF_2D().y, GetColor(255, 0, 0), FALSE);
#endif
	}

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
