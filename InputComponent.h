#pragma once
#include "Engine/GameObject.h"
#include"InputManager.h"

class InputComponent :
    public GameObject
{
protected:
    const Keyboard* keyboard_;
    const Mouse* mouse_;

    virtual void OnClick(XMFLOAT2 mouse_pos){}
    virtual void OnDoubleClick(XMFLOAT2 mouse_pos){}
    virtual void OnDrag(XMFLOAT2 mouse_pos,XMFLOAT2 delta){}
public:
    InputComponent(GameObject* parent);
    virtual ~InputComponent(){}

    void Initialize() override;
    void Update() override;
private:

};

