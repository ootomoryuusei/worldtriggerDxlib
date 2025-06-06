#pragma once
#include "Object3D.h"
class Asteroid :
    public Object3D
{
public:
    Asteroid(GameObject* parent);
    ~Asteroid();
    void Initialize() override;
    void Update() override;
    void Draw() override;
private:
};

