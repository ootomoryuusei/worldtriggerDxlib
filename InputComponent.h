#pragma once
#include "Engine/GameObject.h"
#include"InputManager.h"

class InputComponent :
    public GameObject
{
public:
    InputComponent(GameObject* parent);
    virtual ~InputComponent(){}
    
    virtual void onInputEvent(InputEventType type) = 0;
private:

};

