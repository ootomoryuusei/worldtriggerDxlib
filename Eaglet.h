#pragma once
#include "Trigger.h"
#include"TriggerFactory.h"
#include"AutoRegister.h"

class Eaglet :
    public Trigger
{
public:
    Eaglet(GameObject* parent);
    ~Eaglet();
    void Initialize() override;
    void Update() override;
    void Draw() override;
private:
    static AutoRegister<Eaglet, TriggerFactory> register_;
};

