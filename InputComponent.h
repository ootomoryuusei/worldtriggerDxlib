#pragma once
#include "Engine/GameObject.h"
#include"InputManager.h"

class InputComponent :
    public GameObject
{
protected:
    virtual void OnLeftClick(XMFLOAT2 mouse_pos){}
    virtual void OnRightClick(XMFLOAT2 mouse_pos){}
    /*virtual void OnDrag(XMFLOAT2 mouse_pos,XMFLOAT2 delta){}*/
    virtual void OnSpacePressed(){}

    virtual bool IsHit(XMFLOAT2 position) const { return false; }

public:
    InputComponent(GameObject* parent);
    virtual ~InputComponent(){}

    virtual void HandleInput(const InputEvent& event) {
        if (event.device == InputDeviceType::MOUSE) {
            if (event.pressed && IsHit(event.position)) {
                if (event.mouseButton == MouseButton::LEFT) {
                    OnLeftClick(event.position);
                }
                else if (event.mouseButton == MouseButton::RIGHT) {
                    OnRightClick(event.position);
                }
            }
        }
        else if(event.device == InputDeviceType::KEYBOARD) {
            if (event.keyCode == Keyboard::SPACE && event.pressed) {
                OnSpacePressed();
            }
        }
    }
private:

};

