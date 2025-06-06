#pragma once
#include "Object3D.h"
class Eaglet :
    public Object3D
{
public:
    Eaglet(GameObject* parent);
    ~Eaglet();
    void Initialize() override;
    void Update() override;
    void Draw() override;
private:
};

