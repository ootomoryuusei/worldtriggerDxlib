#pragma once
#include "Engine/GameObject.h"
#include <array>

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

    // ��Ԏ擾
    bool IsPressed(Key key) const;      // �����Ă���
    bool IsTriggered(Key key) const;    // �������u��
    bool IsReleased(Key key) const;     // �������u��
    bool IsLongPressed(Key key) const;  // ������
    bool IsDoublePressed(Key key) const; // �A�Łi�_�u���v���X�j

private:
    std::array<bool, KEY_NUM> m_now{};
    std::array<bool, KEY_NUM> m_prev{};

    std::array<float, KEY_NUM> m_pressStartTime{};    // �����J�n����
    std::array<float, KEY_NUM> m_lastPressTime{};     // ���O��������
    std::array<bool, KEY_NUM> m_doublePressFlag{};    // �A�Ńt���O

    const float DOUBLE_PRESS_SPAN = 0.3f; // �A�Ŕ��莞��
    const float LONG_PRESS_TIME = 0.5f;   // ���������莞��

    float m_time = 0.0f;
};

