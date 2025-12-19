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
    float w = baseSize_.x * scale_.x;
    float h = baseSize_.y * scale_.y;
    float cx = position_.x; 
    float cy = position_.y;

    float dx = screenPos.x - cx;
    float dy = screenPos.y - cy;

    float ca = cosf(-angle_);
    float sa = sinf(-angle_);
    float rx = dx * ca - dy * sa;
    float ry = dx * sa + dy * ca;

    float localX = rx / (scale_.x);
    float localY = ry / (scale_.y);

    localX += (baseSize_.x * 0.5f);
    localY += (baseSize_.y * 0.5f);

    return { localX, localY };
}

bool Object2D::IsInMousePoint(const XMFLOAT2& mpos) const
{
    if (fabsf(angle_) < 1e-5f) {
        float w = baseSize_.x * scale_.x;
        float h = baseSize_.y * scale_.y;
        float left = position_.x - pivot_.x * w;
        float top = position_.y - pivot_.y * h;
        if (mpos.x >= left && mpos.x <= left + w && mpos.y >= top && mpos.y <= top + h) return true;
        return false;
    }

    XMFLOAT2 local = ScreenToLocal(mpos);
    if (local.x >= 0 && local.x <= baseSize_.x && local.y >= 0 && local.y <= baseSize_.y) return true;
    return false;
}

bool Object2D::PointInQuad(XMFLOAT2 point, const array<XMFLOAT2, 4>& corners) {
    // 4つの三角形に分けて、それぞれの符号を確認（外積ベース）
    for (int i = 0; i < 4; i++) {
        int j = (i + 1) % 4;
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