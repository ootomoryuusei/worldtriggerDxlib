#pragma once
#include "Engine/GameObject.h"
#include <array>

class Mouse : public GameObject
{
public:
    enum Button {
        LEFT = 0,
        RIGHT = 1,
        BUTTON_NUM = 2
    };
    Mouse(GameObject* parent);
    ~Mouse();

    void Initialize() override;
    void Update() override;

    // 状態取得

    /// <summary>
    /// マウスを降下し続けているか
    /// </summary>
    /// <param name="btn"> left or right </param>
    /// <returns></returns>
    bool IsPressed(Button btn) const;
    /// <summary>
    /// クリックしたかどうか
    /// </summary>
    /// <param name="btn"> left or right </param>
    /// <returns></returns>
    bool IsClicked(Button btn) const;
    /// <summary>
    /// ダブルクリックしたかどうか
    /// </summary>
    /// <param name="btn"> left or right </param>
    /// <returns></returns>
    bool IsDoubleClicked(Button btn) const;

    //マウス位置取得
    XMFLOAT2 GetMousePos() { return mousePos; }

    //マウスの表示フラグセット
    void SetMouseFlag(bool _flag) { mouseFlag = _flag; }

private:
    std::array<int, BUTTON_NUM> m_now{};
    std::array<int, BUTTON_NUM> m_prev{};
    std::array<int, BUTTON_NUM> m_pressStartFrame{};
    std::array<int, BUTTON_NUM> m_lastClickFrame{};
    std::array<bool, BUTTON_NUM> m_doubleClickFlag{};

    int m_frame = 0;
    const int DOUBLE_CLICK_SPAN = 20; // フレーム数でダブルクリック判定

    int MouseX, MouseY; //マウス座標

    XMFLOAT2 mousePos;

    bool mouseFlag;
};

