#pragma once
#include "Object3D.h"
#include"CharacterData.h"

class Trigger :
    public Object3D
{
protected:
    string target_;
    TRIGGER trigger_;
public:
    Trigger(GameObject* parent);
    ~Trigger();
    void Initialize() override;
    void Update() override;
    void Draw() override;

    bool ArcInPoint(VECTOR _targer_pos,VECTOR _dir,float _fov);

    void SetTriggerData(TRIGGER _trigger) { trigger_ = _trigger; }
    TRIGGER GetTriggerData() { return trigger_; }

    void SetTarget(string _target) { target_ = _target; }
    const string& GetTarget()const { return target_; }
private:
};

