#pragma once
#include "Object3D.h"
class TriggerIcon :
    public Object3D
{
public:
    TriggerIcon(GameObject* parent);
    ~TriggerIcon();
    void Initialize() override;
    void Update() override;
    void Draw() override;

    void SetFileName(std::string _fileName) { fileName_ = _fileName; }
private:
    SIZE_2D graphSize_; //�A�C�R���̉摜�T�C�Y
    std::string fileName_;
};

