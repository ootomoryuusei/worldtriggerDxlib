#include "Object2D.h"
#include "Raycaster2D.h"
#include"SceneContext.h"
#include "Time.h"
#include <DxLib.h>
#include <algorithm>
#include <cmath>

Object2D::Object2D(GameObject* parent, const std::string& name)
    : GameObject(parent, name)
{
   /* transform_.position_ = { 0,0,0 };
    transform_.rotate_ = { 0,0,0 };
    transform_.scale_ = { 1,1,1 };
    hModel_ = -1;
    position_ = {0,0};
    pivot_ = { 0.5,0.5 };
    scale_ = { 1,1 };*/
}

Object2D::~Object2D()
{
}

void Object2D::Initialize()
{
    RegisterToRaycaster(); // Raycaster2D  登録
}

void Object2D::RegisterToRaycaster()
{
    auto* context = GetRootJob()->FindGameObject<SceneContext>();
    if (!context) return;
    raycaster2D_ = context->raycastManager->GetRaycaster2D();
	if (!raycaster2D_) return; // Raycaster2Dが存在しない場合は登録しない

    auto& list = raycaster2D_->elements_;
    if (std::find(list.begin(), list.end(), this) == list.end()) list.push_back(this);
}

void Object2D::UnregisterFromRaycaster()
{
	//if (!raycaster2D_) return; // Raycaster2Dが存在しない場合は登録解除しない
 //   auto& list = raycaster2D_->elements_;
 //   auto it = std::find(list.begin(), list.end(), this);
 //   if (it != list.end()) list.erase(it);
}

void Object2D::Release()
{
	UnregisterFromRaycaster(); // Raycaster2D  登録解除
}

void Object2D::Update()
{
    if (hModel_ < 0)return;
    position_ = { transform_.position_.x,transform_.position_.y };
    scale_ = { transform_.scale_.x,transform_.scale_.y };
    hitSize_.set(baseSize_.size() * transform_.scale_);
}

void Object2D::Draw()
{
	if (hModel_ < 0) return;
    DrawRotaGraph3(position_.x, position_.y, pivot_.x, pivot_.y, scale_.x, scale_.y, 0.0, hModel_, TRUE, FALSE);

	if (!hitShape_) return;
	hitShape_->DrawJudgmentRange(*this);
}

void Object2D::LoadSprite(const std::string& _filePath)
{
    fileName_ = _filePath;
    hModel_ = LoadGraph(fileName_.c_str());
    assert(hModel_ >= 0); //アサーション
    int sizeX, sizeY;
    GetGraphSize(hModel_, &sizeX, &sizeY);
    baseSize_.set(sizeX,sizeY,0);
    hitSize_.set(baseSize_.size());
}

XMFLOAT2 Object2D::ScreenToLocal(const XMFLOAT2& screenPos) const
{
    float w = hitSize_.x;
    float h = hitSize_.y;
    float cx = transform_.position_.x; 
    float cy = transform_.position_.y;

    float dx = screenPos.x - cx;
    float dy = screenPos.y - cy;

    float ca = cosf(-transform_.rotate_.z);
    float sa = sinf(-transform_.rotate_.z);
    float rx = dx * ca - dy * sa;
    float ry = dx * sa + dy * ca;

    float localX = rx / (transform_.scale_.x);
    float localY = ry / (transform_.scale_.y);

    localX += (baseSize_.x * 0.5f);
    localY += (baseSize_.y * 0.5f);

    return { localX, localY };
}

bool Object2D::IsInMousePoint(const XMFLOAT2& mpos) const
{
   /* if (fabsf(angle_) < 1e-5f) {
        float w = hitSize_.x;
        float h = hitSize_.y;
        float left = transform_.position_.x - pivot_.x * w;
        float top = transform_.position_.y - pivot_.y * h;
        if (mpos.x >= left && mpos.x <= left + w && mpos.y >= top && mpos.y <= top + h) return true;
        return false;
    }*/

    XMFLOAT2 local = ScreenToLocal(mpos);
    if (local.x >= 0 && local.x <= hitSize_.x && local.y >= 0 && local.y <= hitSize_.y) return true;
    return false;
}

bool Object2D::PointInPolygon(XMFLOAT2 point, const vector<XMFLOAT2>& corners) {
    // 4つの三角形に分けて、それぞれの符号を確認（外積ベース）
	const size_t corner = corners.size();
    for (int i = 0; i < corner; i++) {
        int j = (i + 1) % corner;
        float dx1 = corners[j].x - corners[i].x;
        float dy1 = corners[j].y - corners[i].y;
        float dx2 = point.x - corners[i].x;
        float dy2 = point.y - corners[i].y;
        VECTOR In1, In2;
        In1 = { dx1,dy1 };
        In2 = { dx2,dy2 };
        if (VCross(In1, In2).z < 0) return false;
    }
    return true;
}

bool Object2D::HitTest(const XMFLOAT2& point){
    if (hitShape_) {
        return hitShape_->IsHit(point, *this);
    }
    return false;
}
