#include "Object2D.h"
#include "Raycaster2D.h"
#include "Time.h"
#include <DxLib.h>
#include <algorithm>
#include <cmath>

Object2D::Object2D(GameObject* parent, const std::string& name)
    : GameObject(parent, name)
{
}

Object2D::~Object2D()
{
}

void Object2D::Initialize()
{
    GameObject::SetInitialized();
	RegisterToRaycaster(); // Raycaster2D  ìoò^
}

void Object2D::RegisterToRaycaster()
{
	raycaster2D_ = GetParent()->FindGameObject<InputManager>()->GetRaycastManager()->GetRaycaster2D();
	if (!raycaster2D_) return; // Raycaster2DÇ™ë∂ç›ÇµÇ»Ç¢èÍçáÇÕìoò^ÇµÇ»Ç¢

    auto& list = raycaster2D_->elements_;
    if (std::find(list.begin(), list.end(), this) == list.end()) list.push_back(this);
}

void Object2D::UnregisterFromRaycaster()
{
	if (!raycaster2D_) return; // Raycaster2DÇ™ë∂ç›ÇµÇ»Ç¢èÍçáÇÕìoò^âèúÇµÇ»Ç¢
    auto& list = raycaster2D_->elements_;
    auto it = std::find(list.begin(), list.end(), this);
    if (it != list.end()) list.erase(it);
}

void Object2D::Release()
{
	UnregisterFromRaycaster(); // Raycaster2D  ìoò^âèú
    GameObject::Release();
}

void Object2D::Update()
{
	if (hModel_ < 0)return;
    position_ = { transform_.position_.x,transform_.position_.y };
    scale_ = { transform_.rotate_.x,transform_.rotate_.y };

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
    assert(hModel_ >= 0); //ÉAÉTÅ[ÉVÉáÉì
    GetGraphSize(hModel_, &graphSize_.x, &graphSize_.y);
    graphSizeF_.set(graphSize_.x,graphSize_.y);
}

XMFLOAT2 Object2D::ScreenToLocal(const XMFLOAT2& screenPos) const
{
    float w = graphSizeF_.x * scale_.x;
    float h = graphSizeF_.y * scale_.y;
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

    localX += (graphSizeF_.x * 0.5f);
    localY += (graphSizeF_.y * 0.5f);

    return { localX, localY };
}

bool Object2D::IsInMousePoint(const XMFLOAT2& mpos) const
{
    if (fabsf(angle_) < 1e-5f) {
        float w = graphSizeF_.x * scale_.x;
        float h = graphSizeF_.y * scale_.y;
        float left = position_.x - pivot_.x * w;
        float top = position_.y - pivot_.y * h;
        if (mpos.x >= left && mpos.x <= left + w && mpos.y >= top && mpos.y <= top + h) return true;
        return false;
    }

    XMFLOAT2 local = ScreenToLocal(mpos);
    if (local.x >= 0 && local.x <= graphSizeF_.x && local.y >= 0 && local.y <= graphSizeF_.y) return true;
    return false;
}