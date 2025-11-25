#pragma once
#include "Engine/GameObject.h" // your existing GameObject base
#include <DirectXMath.h>
#include <string>
#include <functional>

using namespace DirectX;

class UIRaycaster; // forward

class Object2D : public GameObject
{
public:
    // Basic construction: parent can be null
    Object2D(GameObject* parent, const std::string& name = "Object2D");
    virtual ~Object2D();

    // lifecycle
    virtual void Initialize() override; // registers to UIRaycaster
    virtual void Update() override;
    virtual void Draw() override;
    virtual void Release() override; // unregisters

    // sprite / visual properties (kept similar to your Icon)
    void LoadSprite(const std::string& filePath);
    void SetPosition(float x, float y) { graphPos_.x = x; graphPos_.y = y; }
    XMFLOAT2 GetPosition() const { return graphPos_; }
    void SetSize(float w, float h) { graphSizeF_.x = w; graphSizeF_.y = h; graphSize_.x = (int)w; graphSize_.y = (int)h; }
    XMFLOAT2 GetSize() const { return graphSizeF_; }
    void SetScale(float sx, float sy) { scale_ = { sx, sy }; }
    void SetAngle(float radians) { angle_ = radians; }

    // hit test: returns true if screen-space mouse point is inside the drawn quad
    // takes rotation and scale into account (pivot = center by default, pivot can be set)
    virtual bool IsInMousePoint(const XMFLOAT2& mpos) const;

    // event virtuals: override in subclasses to react to input
    virtual void OnPress(const XMFLOAT2& pos) {}
    virtual void OnRelease(const XMFLOAT2& pos) {}
    virtual void OnClick(const XMFLOAT2& pos) {}
    virtual void OnDoubleClick(const XMFLOAT2& pos) {}
    virtual void OnDragStart(const XMFLOAT2& startPos) {}
    virtual void OnDrag(const XMFLOAT2& currentPos, const XMFLOAT2& delta) {}
    virtual void OnDragEnd(const XMFLOAT2& endPos) {}
    virtual void OnHoverEnter() {}
    virtual void OnHoverExit() {}

    std::function<void(const XMFLOAT2&)> onPress;
    std::function<void(const XMFLOAT2&)> onRelease;
    std::function<void(const XMFLOAT2&)> onClick;
    std::function<void(const XMFLOAT2&)> onDoubleClick;
    std::function<void(const XMFLOAT2&)> onDragStart;
    std::function<void(const XMFLOAT2&, const XMFLOAT2&)> onDrag;
    std::function<void(const XMFLOAT2&)> onDragEnd;
    std::function<void()> onHoverEnter;
    std::function<void()> onHoverExit;

    void SetSelecting(bool s) { selecting_ = s; }
    bool GetSelecting() const { return selecting_; }

protected:
    XMFLOAT2 graphSizeF_ = { 64.0f, 64.0f };
    struct Int2 { int x, y; } graphSize_ = { 64, 64 };
    XMFLOAT2 graphPos_ = { 0.0f, 0.0f }; 
    std::string fileName_;
    std::string object2DName_;

    bool selecting_ = false;
    int createNum_ = 0;
    XMFLOAT2 scale_ = { 1.0f, 1.0f };
    XMFLOAT2 pivot_ = { 0.5f, 0.5f }; 
    float angle_ = 0.0f;

    bool hovered_ = false;
    bool pressed_ = false;
    XMFLOAT2 pressStartPos_ = { 0,0 };
    XMFLOAT2 lastMousePos_ = { 0,0 };

    static UIRaycaster* s_uiRaycaster;

    void RegisterToRaycaster();
    void UnregisterFromRaycaster();

    XMFLOAT2 ScreenToLocal(const XMFLOAT2& screenPos) const;
};