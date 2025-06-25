#pragma once
#include "Trigger.h"
#include"TriggerFactory.h"
#include"AutoRegister.h"

class Kogetsu :
    public Trigger
{
public:
    Kogetsu(GameObject* parent);
    ~Kogetsu();
    void Initialize() override;
    void Update() override;
    void Draw() override;
private:
   static AutoRegister<Kogetsu, TriggerFactory> register_;
};

