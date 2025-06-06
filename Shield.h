#pragma once
#include "Object3D.h"
class Shield :
    public Object3D
{
public:
    Shield(GameObject* parent);
    ~Shield();
    void Initialize() override;
    void Update() override;
    void Draw() override;
private:
};

