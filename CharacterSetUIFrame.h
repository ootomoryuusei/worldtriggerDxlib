#pragma once
#include "Object3D.h"
#include<vector>

using std::vector;

class CharacterSetUIFrame :
    public Object3D
{
public:
    CharacterSetUIFrame(GameObject* parent);
    ~CharacterSetUIFrame();
    void Update() override;
    void Draw() override;

    vector<XMFLOAT2> GetFramePosition() { return FramePosition_; }
    XMFLOAT2 GetSIFGraphSize() { return { (float)graphSize_.x,(float)graphSize_.y }; }
private:
    SIZE_2D graphSize_; //アイコンの画像サイズ
    vector<XMFLOAT2> FramePosition_;
};

