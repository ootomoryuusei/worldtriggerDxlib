#pragma once
#include "Icon.h"
#include<vector>

using std::vector;

class TriggerSetUIFrame :
    public Icon
{
public:
    TriggerSetUIFrame(GameObject* parent);
    ~TriggerSetUIFrame();
    void Update() override;
    void Draw() override;

    /*vector<XMFLOAT2> GetSIFPosition() { return SIUFPosition_; }
    XMFLOAT2 GetSIFGraphSize() { return { (float)graphSize_.x,(float)graphSize_.y }; }*/
private:
    //SIZE_2D graphSize_; //�A�C�R���̉摜�T�C�Y
    //vector<XMFLOAT2> SIUFPosition_;
};

