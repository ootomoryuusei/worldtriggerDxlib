#include "ArcIcon.h"
#include"HitSquareArc.h"

ArcIcon::ArcIcon(GameObject* parent, const std::string& name) : Object2D(parent, name)
{
}

ArcIcon::~ArcIcon()
{
}

void ArcIcon::Initialize()
{
	Object2D::Initialize(); //Raycaster2D‚Ö“o˜^
	hitShape_ = new HitSquareArc(); // “–‚½‚è”»’èŒ`ó‚ğ‰~ŒÊê—plŠpŒ`‚Éİ’è
}

void ArcIcon::Update()
{
	SetScale(arcData_.rangeSize,arcData_.rangeSize,0);
	/*if (hModel_ < 0)return;
	hitSize_.set(baseSize_.size() * transform_.scale_);
	position_ = { transform_.position_.x + hitSize_.halfX(),transform_.position_.y + hitSize_.halfY()};
	scale_ = { transform_.scale_.x,transform_.scale_.y };*/
	Object2D::Update();
}

void ArcIcon::Draw()
{
	DrawCircleGaugeF(position_.x,position_.y,arcData_.percent, hModel_,arcData_.startPercent,scale_.x);
	hitShape_->DrawJudgmentRange(*this);
}

void ArcIcon::Release()
{
}
