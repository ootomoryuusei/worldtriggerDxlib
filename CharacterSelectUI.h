#pragma once
#include "Object3D.h"
class CharacterSelectUI :
    public Object3D
{
public:
    CharacterSelectUI(GameObject* parent);
    ~CharacterSelectUI();
    void Update() override;
    void Draw() override;

    SIZE_2D GetIconSize() { return graphSize_; }
    string GetFileName() { return fileName_; }
private:
    SIZE_2D graphSize_; //�A�C�R���̉摜�T�C�Y
    std::string fileName_;
};

