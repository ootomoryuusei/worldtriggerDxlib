#pragma once
#include "Engine/GameObject.h"
#include <array>
#include "InputEvents.h"

using std::array;
using std::vector;

class Keyboard : public GameObject
{
public:
    Keyboard(GameObject* parent);
    ~Keyboard();

    void Initialize() override;
    void Update() override;

    function<void(const KeyEvent&)> OnKeyDown;
    function<void(const KeyEvent&)> OnKeyUp;
    function<void(const KeyEvent&)> OnKeyRepeat;
private:
    array<bool, 256> k_now{};
    array<bool, 256> k_prev{};

    const float DOUBLE_PRESS_SPAN = 0.3f; // ˜A‘Å”»’èŽžŠÔ
    const float LONG_PRESS_TIME = 0.5f;   // ’·‰Ÿ‚µ”»’èŽžŠÔ
};

