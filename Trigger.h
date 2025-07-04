#pragma once
#include "Object3D.h"
#include"CharacterData.h"

class Trigger :
    public Object3D
{
public:
    Trigger(GameObject* parent);
    ~Trigger();
    void Initialize() override;
    void Update() override;
    void Draw() override;

    bool ArcInPoint(VECTOR _targer_pos,VECTOR _dir,float _fov);

    void SetData(CharacterData* _data) { data_ = _data; }
    const auto& GetData() { return data_; }
private:
    CharacterData* data_;
};

