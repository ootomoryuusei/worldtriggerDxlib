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

    // ��Ԏ擾

    /// <summary>
    /// �}�E�X���~���������Ă��邩
    /// </summary>
    /// <param name="btn"> left or right </param>
    /// <returns></returns>
    bool IsPressed(Button btn) const;
    /// <summary>
    /// �N���b�N�������ǂ���
    /// </summary>
    /// <param name="btn"> left or right </param>
    /// <returns></returns>
    bool IsClicked(Button btn) const;
    /// <summary>
    /// �_�u���N���b�N�������ǂ���
    /// </summary>
    /// <param name="btn"> left or right </param>
    /// <returns></returns>
    bool IsDoubleClicked(Button btn) const;

    //�}�E�X�ʒu�擾
    XMFLOAT2 GetMousePos() { return mousePos; }

    //�}�E�X�̕\���t���O�Z�b�g
    void SetMouseFlag(bool _flag) { mouseFlag = _flag; }

private:
    std::array<int, BUTTON_NUM> m_now{};
    std::array<int, BUTTON_NUM> m_prev{};
    std::array<int, BUTTON_NUM> m_pressStartTime{};
    std::array<int, BUTTON_NUM> m_lastClickTime{};
    std::array<bool, BUTTON_NUM> m_doubleClickFlag{};

    float m_time = 0.0;
    const float DOUBLE_CLICK_SPAN = 0.7; // �o�ߎ��ԂŃ_�u���N���b�N����

    int MouseX, MouseY; //�}�E�X���W

    XMFLOAT2 mousePos;

    bool mouseFlag;
};

