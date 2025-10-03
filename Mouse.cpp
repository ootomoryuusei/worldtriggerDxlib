#include "Mouse.h"
#include <DxLib.h>

Mouse::Mouse(GameObject* parent) : GameObject(parent,"マウス")
{
    mouseFlag = true;
}

Mouse::~Mouse()
{
}

void Mouse::Initialize()
{
   
}

void Mouse::Update()
{
    SetMouseDispFlag(mouseFlag); //マウスを表示させるフラグ関数
    GetMousePoint(&MouseX, &MouseY);
    mousePos = { (float)MouseX,(float)MouseY };

    m_prev = m_now;

    m_now[LEFT] = (GetMouseInput() & MOUSE_INPUT_LEFT) != 0;
    m_now[RIGHT] = (GetMouseInput() & MOUSE_INPUT_RIGHT) != 0;

    for (int i = 0; i < BUTTON_NUM; ++i) {
        // 押し始め
        if (m_now[i] && !m_prev[i]) {
            if (m_time - m_lastClickTime[i] <= DOUBLE_CLICK_SPAN) {
                m_doubleClickFlag[i] = true;
            }
            else {
                m_doubleClickFlag[i] = false;
            }

            m_lastClickTime[i] = m_time;
            m_pressStartTime[i] = m_time;
        }

        // ボタン離したときの処理を入れたい場合はここに
    }
    
    m_time += Time::DeltaTime();
}

bool Mouse::IsPressed(Button btn) const
{
    return m_now[btn];
}

bool Mouse::IsClicked(Button btn) const
{
    return m_now[btn] && !m_prev[btn];
}

bool Mouse::IsDoubleClicked(Button btn) const
{
    return IsClicked(btn) && m_doubleClickFlag[btn];
}