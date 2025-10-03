#include "Keyboard.h"
#include <DxLib.h>
#include "Time.h" // DeltaTime() �p

Keyboard::Keyboard(GameObject* parent) : GameObject(parent,"�L�[�{�[�h")
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

    // ���ݏ�ԍX�V
    m_now[UP] = CheckHitKey(KEY_INPUT_UP) != 0;
    m_now[DOWN] = CheckHitKey(KEY_INPUT_DOWN) != 0;
    m_now[LEFT] = CheckHitKey(KEY_INPUT_LEFT) != 0;
    m_now[RIGHT] = CheckHitKey(KEY_INPUT_RIGHT) != 0;
    m_now[SPACE] = CheckHitKey(KEY_INPUT_SPACE) != 0;

    // �e�L�[�̎��ԊǗ�
    for (int i = 0; i < KEY_NUM; ++i) {
        // �����n��
        if (m_now[i] && !m_prev[i]) {
            // �A�Ŕ���
            if (m_time - m_lastPressTime[i] <= DOUBLE_PRESS_SPAN) {
                m_doublePressFlag[i] = true;
            }
            else {
                m_doublePressFlag[i] = false;
            }

            m_lastPressTime[i] = m_time;
            m_pressStartTime[i] = m_time;
        }

        // �������u�Ԃɒ������t���O�̓��Z�b�g�\
        if (!m_now[i] && m_prev[i]) {
            // ��������A�ł̌㏈�����K�v�Ȃ炱���ōs��
        }
    }

    m_time += Time::DeltaTime();
}

// �����Ă���
bool Keyboard::IsPressed(Key key) const
{
    return m_now[key];
}

// �������u��
bool Keyboard::IsTriggered(Key key) const
{
    return m_now[key] && !m_prev[key];
}

// �������u��
bool Keyboard::IsReleased(Key key) const
{
    return !m_now[key] && m_prev[key];
}

// ����������
bool Keyboard::IsLongPressed(Key key) const
{
    return m_now[key] && (m_time - m_pressStartTime[key] >= LONG_PRESS_TIME);
}

// �A�Łi�_�u���v���X�j����
bool Keyboard::IsDoublePressed(Key key) const
{
    return IsTriggered(key) && m_doublePressFlag[key];
}
