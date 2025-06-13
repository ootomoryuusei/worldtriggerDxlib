#pragma once
#include "Object3D.h"
class Triggers :
    public Object3D
{
public:
    Triggers(GameObject* parent);
    ~Triggers();
    void Initialize() override;
    void Update() override;
    void Draw() override;
private:

};

