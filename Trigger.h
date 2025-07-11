#pragma once
#include "Object3D.h"
#include"CharacterData.h"

class TriggerData;

class Trigger :
    public Object3D
{
protected:
    TriggerData* pData_;
public:
    Trigger(GameObject* parent);
    ~Trigger();
    void Initialize() override;
    void Update() override;
    void Draw() override;

    bool ArcInPoint(VECTOR _targer_pos,VECTOR _dir,float _fov);

    const auto& GetptrData() const { return pData_; }
private:
};

