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
    //SetMouseDispFlag(mouseFlag); //マウスを表示させるフラグ関数
    //GetMousePoint(&MouseX, &MouseY);
    //mousePos = { (float)MouseX,(float)MouseY };

    //m_prev = m_now;

    //m_now[LEFT] = (GetMouseInput() & MOUSE_INPUT_LEFT) != 0;
    //m_now[RIGHT] = (GetMouseInput() & MOUSE_INPUT_RIGHT) != 0;

    //for (int i = 0; i < BUTTON_NUM; ++i) {
    //    // 押し始め
    //    if (m_now[i] && !m_prev[i]) {
    //        if (m_time - m_lastClickTime[i] <= DOUBLE_CLICK_SPAN) {
    //            m_doubleClickFlag[i] = true;
    //        }
    //        else {
    //            m_doubleClickFlag[i] = false;
    //        }

    //        m_lastClickTime[i] = m_time;
    //        m_pressStartTime[i] = m_time;
    //    }

    //    // ボタン離したときの処理を入れたい場合はここに
    //}
    //
    //m_time += Time::DeltaTime();
    
}

void Mouse::IsPressed(MouseButton btn, vector<InputEvent>& events)
{
    if (m_now[btn] && !m_prev[btn]) {
        m_pressStartTime[btn] = m_time;
        dragStartPos = mousePos;
        m_dragging[btn] = false;

        InputEvent e;
        e.device = InputDeviceType::MOUSE;
        e.m_Button = btn;
        e.position = mousePos;
        e.clickType = MouseClickType::PRESS;
        events.push_back(e);
    }
}

void Mouse::Update(vector<InputEvent>& events)
{
    m_prev = m_now;
    m_now[LEFT] = (GetMouseInput() & MOUSE_INPUT_LEFT) != 0;
    m_now[RIGHT] = (GetMouseInput() & MOUSE_INPUT_RIGHT) != 0;
    m_now[MIDDLE] = (GetMouseInput() & MOUSE_INPUT_MIDDLE) != 0;

    XMINT2 m_pos;
    GetMousePoint(&m_pos.x, &m_pos.y);
    mousePos = { (float)m_pos.x,(float)m_pos.y };

    const float dt = Time::DeltaTime();

    for (int i = 0; i < MOUSE_MAX; ++i) {
        if (m_now[i] && !m_prev[i]) {
            InputEvent e;
            e.device = InputDeviceType::MOUSE;
            e.position = mousePos;
            e.m_Button = (MouseButton)i;
            e.pressed = true;
            events.push_back(e);
        }
        if (!m_now[i] && m_prev[i]) {
            InputEvent e;
            e.device = InputDeviceType::MOUSE;
            e.position = mousePos;
            e.m_Button = (MouseButton)i;
            e.released = true;
            events.push_back(e);
        }


        // 離した瞬間
        if (!m_now[i] && m_prev[i]) {
            InputEvent e;
            e.device = InputDeviceType::MOUSE;
            e.m_Button = (MouseButton)i;
            e.position = mousePos;
            e.clickType = m_dragging[i] ? MouseClickType::DRAGEND : MouseClickType::RELEASE;
            events.push_back(e);
            // クリック判定
            if (!m_dragging[i]) {
                // ダブルクリック判定
                const float diff = m_time - m_lastClickTime[i];
                m_lastClickTime[i] = m_time;

                if (diff <= DOUBLE_CLICK_SPAN) {
                    InputEvent dc;
                    dc.device = InputDeviceType::MOUSE;
                    dc.m_Button = (MouseButton)i;
                    dc.position = mousePos;
                    dc.clickType = MouseClickType::DOBULECLICK;
                    events.push_back(dc);
                }
                else {
                    InputEvent c;
                    c.device = InputDeviceType::MOUSE;
                    c.m_Button = (MouseButton)i;
                    c.position = mousePos;
                    c.clickType = MouseClickType::CLICK;
                    events.push_back(c);
                }
            }
        }
    }
    m_time += dt;
}
