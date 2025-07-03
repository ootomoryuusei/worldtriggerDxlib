#pragma once
#include "Object3D.h"

class Trigger :
    public Object3D
{
public:
    Trigger(GameObject* parent);
    ~Trigger();
    void Initialize() override;
    void Update() override;
    void Draw() override;

    bool ArcInPoint(VECTOR _targer_pos,VECTOR _dir,float _fov);

private:
};

