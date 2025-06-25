#pragma once
#include "Trigger.h"
#include"TriggerFactory.h"
#include"AutoRegister.h"

class Shield :
    public Trigger
{
public:
    Shield(GameObject* parent);
    ~Shield();
    void Initialize() override;
    void Update() override;
    void Draw() override;
private:
    static AutoRegister<Shield, TriggerFactory> register_;
};

