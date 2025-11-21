#pragma once
#include "Engine/GameObject.h"
#include <array>
#include "InputEvents.h"

using std::vector;

class Keyboard : public GameObject
{
public:
    enum Key {
        UP,
        DOWN,
        LEFT,
        RIGHT,
        SPACE,
        KEY_NUM
    };

    Keyboard(GameObject* parent);
    ~Keyboard();

    void Initialize() override;
    void Update() override;
    void Update(vector<InputEvent>& events);

    //// 状態取得
    //bool IsPressed(Key key) const;      // 押している
    //bool IsTriggered(Key key) const;    // 押した瞬間
    //bool IsReleased(Key key) const;     // 離した瞬間
    //bool IsLongPressed(Key key) const;  // 長押し
    //bool IsDoublePressed(Key key) const; // 連打（ダブルプレス）

private:
    std::array<bool, KEY_NUM> m_now{};
    std::array<bool, KEY_NUM> m_prev{};

    std::array<float, KEY_NUM> m_pressStartTime{};    // 押下開始時刻
    std::array<float, KEY_NUM> m_lastPressTime{};     // 直前押下時刻
    std::array<bool, KEY_NUM> m_doublePressFlag{};    // 連打フラグ

    const float DOUBLE_PRESS_SPAN = 0.3f; // 連打判定時間
    const float LONG_PRESS_TIME = 0.5f;   // 長押し判定時間

    float m_time = 0.0f;
};

