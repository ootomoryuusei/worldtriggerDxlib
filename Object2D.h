#pragma once
#include "Engine/GameObject.h" 
#include <DirectXMath.h>
#include <string>
#include <functional>

using namespace DirectX;
using std::string;

class UIRaycaster;

struct SIZE_2D {
    int x, y, halfX, halfY;
    void set(int _x, int _y) {
        x = _x, y = _y;
    }
    int halfX() const { return x / 2; }
    int halfY() const { return y / 2; }
};

struct SIZE_F_2D {
    float x, y;
    void set(float _x, float _y) {
        x = _x; y = _y;
    }
    float halfX() const { return x / 2; }
    float halfY() const { return y / 2; }
};


class Object2D : public GameObject
{
public:
    Object2D(GameObject* parent, const std::string& name = "Object2D");
    virtual ~Object2D();

    virtual void Initialize() override; 
    virtual void Update() override;
    virtual void Draw() override;
    virtual void Release() override;

    void LoadSprite(const string& filePath);
    void SetScale(float sx, float sy) { scale_ = { sx, sy }; }

    virtual bool IsInMousePoint(const XMFLOAT2& mpos) const;

   /* virtual void OnPress(const XMFLOAT2& pos) {}
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
    std::function<void()> onHoverExit;*/

    void SetSelecting(bool s) { selecting_ = s; }
    bool GetSelecting() const { return selecting_; }

protected:
    int hModel_; //モデルハンドル
    SIZE_F_2D graphSizeF_; //アイコンの画像サイズ(float)
    SIZE_2D graphSize_; //アイコンの画像サイズ(int)
    XMFLOAT2 graphPos_; //アイコン座標
    string fileName_; //ファイル名
    string iconName_; //アイコン名
    bool selecting_; //セレクトされているかどうか
    int createNum_; //作成番号
    VECTOR scale_; //スケール
    int fontHandle_; //フォントハンドル
    XMFLOAT2 pivot_; //回転軸
    float angle_; //回転

    bool hovered_ = false;
    bool pressed_ = false;
    XMFLOAT2 pressStartPos_ = { 0,0 };
    XMFLOAT2 lastMousePos_ = { 0,0 };

    static UIRaycaster* s_uiRaycaster;

    void RegisterToRaycaster();
    void UnregisterFromRaycaster();

    XMFLOAT2 ScreenToLocal(const XMFLOAT2& screenPos) const;
};