#include "Keyboard.h"
#include <DxLib.h>
#include "Time.h" // DeltaTime() 用

Keyboard::Keyboard(GameObject* parent) : GameObject(parent,"キーボード")
{
}

Keyboard::~Keyboard()
{
}

void Keyboard::Initialize()
{
}

void Keyboard::Update()
{
    m_prev = m_now;

    // 現在状態更新
    m_now[UP] = CheckHitKey(KEY_INPUT_UP) != 0;
    m_now[DOWN] = CheckHitKey(KEY_INPUT_DOWN) != 0;
    m_now[LEFT] = CheckHitKey(KEY_INPUT_LEFT) != 0;
    m_now[RIGHT] = CheckHitKey(KEY_INPUT_RIGHT) != 0;
    m_now[SPACE] = CheckHitKey(KEY_INPUT_SPACE) != 0;

    // 各キーの時間管理
    for (int i = 0; i < KEY_NUM; ++i) {
        // 押し始め
        if (m_now[i] && !m_prev[i]) {
            // 連打判定
            if (m_time - m_lastPressTime[i] <= DOUBLE_PRESS_SPAN) {
                m_doublePressFlag[i] = true;
            }
            else {
                m_doublePressFlag[i] = false;
            }

            m_lastPressTime[i] = m_time;
            m_pressStartTime[i] = m_time;
        }

        // 離した瞬間に長押しフラグはリセット可能
        if (!m_now[i] && m_prev[i]) {
            // 長押しや連打の後処理が必要ならここで行う
        }
    }

    m_time += Time::DeltaTime();
}

void Keyboard::Update(vector<InputEvent>& events)
{
    m_prev = m_now;
    m_time += Time::DeltaTime();

    if (CheckHitKey(KEY_INPUT_UP))   m_now[UP] = true; else m_now[UP] = false;
    if (CheckHitKey(KEY_INPUT_DOWN)) m_now[DOWN] = true; else m_now[DOWN] = false;
    if (CheckHitKey(KEY_INPUT_LEFT)) m_now[LEFT] = true; else m_now[LEFT] = false;
    if (CheckHitKey(KEY_INPUT_RIGHT))m_now[RIGHT] = true; else m_now[RIGHT] = false;
    if (CheckHitKey(KEY_INPUT_SPACE))m_now[SPACE] = true; else m_now[SPACE] = false;

    for (int i = 0; i < KEY_NUM; ++i) {
        if (m_now[i] && !m_prev[i]) {
            InputEvent e;
            e.device = InputDeviceType::KEYBOARD;
            e.keyCode = i;
            e.pressed = true;
            events.push_back(e);
        }
        if (!m_now[i] && m_prev[i]) {
            InputEvent e;
            e.device = InputDeviceType::KEYBOARD;
            e.keyCode = i;
            e.released = true;
            events.push_back(e);
        }
    }
}

//// 押している
//bool Keyboard::IsPressed(Key key) const
//{
//    return m_now[key];
//}
//
//// 押した瞬間
//bool Keyboard::IsTriggered(Key key) const
//{
//    return m_now[key] && !m_prev[key];
//}
//
//// 離した瞬間
//bool Keyboard::IsReleased(Key key) const
//{
//    return !m_now[key] && m_prev[key];
//}
//
//// 長押し判定
//bool Keyboard::IsLongPressed(Key key) const
//{
//    return m_now[key] && (m_time - m_pressStartTime[key] >= LONG_PRESS_TIME);
//}
//
//// 連打（ダブルプレス）判定
//bool Keyboard::IsDoublePressed(Key key) const
//{
//    return IsTriggered(key) && m_doublePressFlag[key];
//}
