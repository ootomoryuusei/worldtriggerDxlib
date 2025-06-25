#pragma once
#include "Trigger.h"
#include"TriggerFactory.h"
#include"AutoRegister.h"

class Asteroid :
    public Trigger
{
public:
    Asteroid(GameObject* parent);
    ~Asteroid();
    void Initialize() override;
    void Update() override;
    void Draw() override;
private:
    static AutoRegister<Asteroid, TriggerFactory> register_;
};

