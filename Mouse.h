#pragma once
#include "Engine/GameObject.h"
#include <array>
#include "InputEvents.h"

using std::array;
using std::vector;

class Mouse : public GameObject
{
public:
    Mouse(GameObject* parent);
    ~Mouse();

    void Initialize() override;
    void Update() override;

    function<void(const ClickEvent&)> OnClick;
    function<void(const DoubleClickEvent&)> OnDoubleClick;
    function<void(const PressEvent&)> OnPress;
    function<void(const PressEvent&)> OnRelease;
    function<void(const DragEvent&)> OnDrag;
    function<void(const DragEvent&)> OnDragStart;
    function<void(const DragEvent&)> OnDragEnd;
    function<void(const WheelEvent&)> OnWheel;

    //マウスの表示フラグセット
    void SetMouseFlag(bool _flag) { mouseFlag = _flag; }
private:
    array<bool, MOUSE_MAX> m_now{}; //現在のマウス降下状態
    array<bool, MOUSE_MAX> m_prev{}; //1f前のマウス降下状態
    array<bool, MOUSE_MAX> m_dragging{}; //ドラッグ状態
    array<bool, MOUSE_MAX> m_doubleClicked{}; //ダブルクリック判定
    array<XMFLOAT2, MOUSE_MAX> m_dragStart{}; //ドラッグ開始位置

    const float DOUBLE_CLICK_SPAN = 0.7; // 経過時間でダブルクリック判定
    const int DRAG_THRESHOLD = 3; //ドラッグの閾値(pix)
    float lastClick[MOUSE_MAX]{};
    XMFLOAT2 m_pos; //マウス位置
    XMFLOAT2 m_prevPos; //1f前のマウス位置
    float m_time; //時間
    bool mouseFlag; //マウス表示フラグ
    void detect(int btn);
};

