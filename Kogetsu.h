#pragma once
#include "Object3D.h"
class Kogetsu :
    public Object3D
{
public:
    Kogetsu(GameObject* parent);
    ~Kogetsu();
    void Initialize() override;
    void Update() override;
    void Draw() override;
private:
};

