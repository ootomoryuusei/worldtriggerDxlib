#include "ArcIcon.h"

ArcIcon::ArcIcon(GameObject* parent, const std::string& name) : Object2D(parent, name)
{
}

ArcIcon::~ArcIcon()
{
}

void ArcIcon::Initialize()
{
}

void ArcIcon::Update()
{
	SetScale(arcData_.rangeSize,arcData_.rangeSize,0);
	Object2D::Update();
}

void ArcIcon::Draw()
{
	DrawCircleGaugeF(position_.x,position_.y,arcData_.percent, hModel_,arcData_.startPercent,scale_.x);
}

void ArcIcon::Release()
{
}
