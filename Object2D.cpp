#include "Object2D.h"
#include "UIRaycaster.h"
#include "Time.h"
#include <DxLib.h>
#include <algorithm>
#include <cmath>

// static
UIRaycaster* Object2D::s_uiRaycaster = nullptr;

Object2D::Object2D(GameObject* parent, const std::string& name)
    : GameObject(parent, name), object2DName_(name)
{
}

Object2D::~Object2D()
{
}

void Object2D::Initialize()
{
    GameObject::SetInitialized();
    // register to global UIRaycaster (create if missing)
    RegisterToRaycaster();
}

void Object2D::RegisterToRaycaster()
{
    if (!s_uiRaycaster) {
        return;
    }

    auto& list = s_uiRaycaster->elements_;
    if (std::find(list.begin(), list.end(), this) == list.end()) list.push_back(this);
}

void Object2D::UnregisterFromRaycaster()
{
    if (!s_uiRaycaster) return;
    auto& list = s_uiRaycaster->elements_;
    auto it = std::find(list.begin(), list.end(), this);
    if (it != list.end()) list.erase(it);
}

void Object2D::Release()
{
    UnregisterFromRaycaster();
    GameObject::Release();
}

void Object2D::Update()
{
}

void Object2D::Draw()
{
    if (fileName_.empty()) return;

    int handle = LoadGraph(fileName_.c_str());
    if (handle == -1) return;

    float w = graphSizeF_.x * scale_.x;
    float h = graphSizeF_.y * scale_.y;
    float drawX = graphPos_.x - pivot_.x * w;
    float drawY = graphPos_.y - pivot_.y * h;

    DrawRotaGraph2F((int)drawX, (int)drawY, pivot_.x, pivot_.y, 1.0f, angle_, handle, TRUE);
}

void Object2D::LoadSprite(const std::string& filePath)
{
    fileName_ = filePath;
}

XMFLOAT2 Object2D::ScreenToLocal(const XMFLOAT2& screenPos) const
{
    float w = graphSizeF_.x * scale_.x;
    float h = graphSizeF_.y * scale_.y;
    float cx = graphPos_.x; 
    float cy = graphPos_.y;

    float dx = screenPos.x - cx;
    float dy = screenPos.y - cy;

    float ca = cosf(-angle_);
    float sa = sinf(-angle_);
    float rx = dx * ca - dy * sa;
    float ry = dx * sa + dy * ca;

    float localX = rx / (scale_.x);
    float localY = ry / (scale_.y);

    localX += (graphSizeF_.x * 0.5f);
    localY += (graphSizeF_.y * 0.5f);

    return { localX, localY };
}

bool Object2D::IsInMousePoint(const XMFLOAT2& mpos) const
{
    if (fabsf(angle_) < 1e-5f) {
        float w = graphSizeF_.x * scale_.x;
        float h = graphSizeF_.y * scale_.y;
        float left = graphPos_.x - pivot_.x * w;
        float top = graphPos_.y - pivot_.y * h;
        if (mpos.x >= left && mpos.x <= left + w && mpos.y >= top && mpos.y <= top + h) return true;
        return false;
    }

    XMFLOAT2 local = ScreenToLocal(mpos);
    if (local.x >= 0 && local.x <= graphSizeF_.x && local.y >= 0 && local.y <= graphSizeF_.y) return true;
    return false;
}