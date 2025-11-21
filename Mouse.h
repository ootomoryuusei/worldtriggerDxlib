#pragma once
#include "Engine/GameObject.h"
#include <array>
#include "InputEvents.h"

using std::vector;

class Mouse : public GameObject
{
public:
    Mouse(GameObject* parent);
    ~Mouse();

    void Initialize() override;
    void Update() override;
    void Update(vector<InputEvent>& events);
    // マウス状態

    /// <summary>
    /// 押下した瞬間
    /// </summary>
    /// <param name="btn"></param>
    void IsPressed(MouseButton btn, vector<InputEvent>& events);
    void IsClicked(MouseButton btn, vector<InputEvent>& events);
    void IsDoubleClicked(MouseButton btn, vector<InputEvent>& events);

    //マウス位置取得
    XMFLOAT2 GetMousePos() { return mousePos; }

    //マウスの表示フラグセット
    void SetMouseFlag(bool _flag) { mouseFlag = _flag; }

private:
    std::array<int, MOUSE_MAX> m_now{}; //現在のマウス降下状態
    std::array<int, MOUSE_MAX> m_prev{}; //1f前のマウス降下状態
    std::array<float, MOUSE_MAX> m_pressStartTime{}; 
    std::array<float, MOUSE_MAX> m_lastClickTime{}; 
    std::array<bool, MOUSE_MAX> m_dragging{};

    const float DOUBLE_CLICK_SPAN = 0.7; // 経過時間でダブルクリック判定
    const float DRAG_THRESOHLD = 4.0f; //ずれたらドラッグ開始(ピクセル)

    XMFLOAT2 mousePos;
    XMFLOAT2 dragStartPos;
    bool mouseFlag;

    float m_time;
};

