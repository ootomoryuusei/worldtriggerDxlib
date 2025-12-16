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
    m_prevPos = m_pos; //prevに位置をセット
    m_prev = m_now; //prevに状態をセット
    //マウスのインプット状態
    m_now[RIGHT] = (GetMouseInput() & MOUSE_INPUT_RIGHT) != 0;
    m_now[LEFT] = (GetMouseInput() & MOUSE_INPUT_LEFT) != 0;
    m_now[MIDDLE] = (GetMouseInput() & MOUSE_INPUT_MIDDLE) != 0;

    SetMouseDispFlag(mouseFlag); //マウスを表示させるフラグ関数
    int m_posX, m_posY;
    GetMousePoint(&m_posX, &m_posY);
    m_pos = { (float)m_posX,(float)m_posY };

    for (int i = 0;i < (int)MOUSE_MAX;i++) {
        detect(i);
    }

    m_time += Time::DeltaTime();
	SetPosition(m_pos.x,m_pos.y,0.0f);
}

void Mouse::detect(int btn)
{
    //マウスクリック、ダブルクリック
    if (m_now[btn] && !m_prev[btn]) { //押した瞬間
        if (OnPress) OnPress({ (MouseButton)btn,m_pos });

        float diff = m_time - lastClick[btn];
        lastClick[btn] = m_time;

        m_doubleClicked[btn] = (diff <= DOUBLE_CLICK_SPAN);
        if (m_doubleClicked[btn] && OnDoubleClick) {
            OnDoubleClick({ (MouseButton)btn,m_pos });
        }
        m_dragging[btn] = false;
        m_dragStart[btn] = m_pos;
    }

    if (!m_now[btn] && m_prev[btn]) { //離した瞬間
        if (OnRelease) OnRelease({ (MouseButton)btn,m_pos });

        if (m_dragging[btn] && OnDragEnd) {
            DragEvent d_event;
            d_event.button = (MouseButton)btn;
            d_event.start = m_dragStart[btn];
            d_event.current = m_pos;
            d_event.delta = m_pos - m_prevPos;
            OnDragEnd(d_event);
        }

        if (!m_doubleClicked[btn] && !m_dragging[btn] && OnClick) { 
            OnClick({ (MouseButton)btn,m_pos });
        }
    }

    if (m_now[btn] && m_prev[btn]) { //押し続け
        XMFLOAT2 diff = m_pos - m_dragStart[btn];
        XMFLOAT2 delta = m_pos - m_prevPos;

        if (!m_dragging[btn] && (abs(diff.x) > DRAG_THRESHOLD || abs(diff.y > DRAG_THRESHOLD))) {
            m_dragging[btn] = true;
            if (OnDragStart) OnDragStart({ (MouseButton)btn,m_dragStart[btn],m_pos,delta });
        }

        if (m_dragging[btn] && OnDrag) {
            
            OnDrag({ (MouseButton)btn,m_dragStart[btn],m_pos,delta });
        }
    }
}

