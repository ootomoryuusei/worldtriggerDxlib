#include "Mouse.h"
#include <DxLib.h>

Mouse::Mouse(GameObject* parent) : GameObject(parent)
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
    SetMouseDispFlag(mouseFlag); //�}�E�X��\��������t���O�֐�
    GetMousePoint(&MouseX, &MouseY);
    mousePos = { (float)MouseX,(float)MouseY };

    m_prev = m_now;

    m_now[LEFT] = (GetMouseInput() & MOUSE_INPUT_LEFT) != 0;
    m_now[RIGHT] = (GetMouseInput() & MOUSE_INPUT_RIGHT) != 0;

    for (int i = 0; i < BUTTON_NUM; ++i) {
        // �����n��
        if (m_now[i] && !m_prev[i]) {
            if (m_frame - m_lastClickFrame[i] <= DOUBLE_CLICK_SPAN) {
                m_doubleClickFlag[i] = true;
            }
            else {
                m_doubleClickFlag[i] = false;
            }

            m_lastClickFrame[i] = m_frame;
            m_pressStartFrame[i] = m_frame;
        }

        // �{�^���������Ƃ��̏�������ꂽ���ꍇ�͂�����
    }

    ++m_frame;
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