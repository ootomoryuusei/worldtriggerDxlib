#pragma once
#include "Engine/GameObject.h" 
#include"GameInfo.h"
#include"InputManager.h"
#include"BaseHitShape.h"
#include <DirectXMath.h>
#include <string>
#include<array>
#include <functional>

class Raycaster2D;

using namespace DirectX;
using std::string;
using std::array;

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

    string GetFileName() { return fileName_; }

    void SetSelecting(bool _selecting) { selecting_ = _selecting; }
    bool GetSelecting() { return selecting_; }

    void SetCreateNum(int _createNum) { createNum_ = _createNum; }
    int GetCreateNum() { return createNum_; }

    void SetIconName(string _iconName) { iconName_ = _iconName; }
    string GetIconName() { return iconName_; }

    void SetFontHandle(int _fontHandle) { fontHandle_ = _fontHandle; }

    bool IsInMousePoint(const XMFLOAT2& mpos) const;

    bool PointInPolygon(XMFLOAT2 point, const vector<XMFLOAT2>& corners);

    bool HitTest(const XMFLOAT2& point);
protected:
    int hModel_; //モデルハンドル
    XMFLOAT2 position_; //座標
    XMFLOAT2 scale_; //スケール
    string fileName_; //ファイル名
    string iconName_; //アイコン名
    bool selecting_; //セレクトされているかどうか
    int createNum_; //作成番号
    int fontHandle_; //フォントハンドル
    XMFLOAT2 pivot_; //回転軸
    float angle_; //回転
	BaseHitShape* hitShape_ = nullptr; //当たり判定形状

    bool hovered_ = false;
    bool pressed_ = false;
    XMFLOAT2 pressStartPos_ = { 0,0 };
    XMFLOAT2 lastMousePos_ = { 0,0 };

	Raycaster2D* raycaster2D_ = nullptr; //2Dレイキャスター

    void RegisterToRaycaster();
    void UnregisterFromRaycaster();

    XMFLOAT2 ScreenToLocal(const XMFLOAT2& screenPos) const;
};