#pragma once
#include "Object3D.h"
#include<vector>

using std::vector;
using std::string;

class Icon :
    public Object3D
{
protected:
    SIZE_F_2D graphSizeF_; //�A�C�R���̉摜�T�C�Y(float)
    SIZE_2D graphSize_; //�A�C�R���̉摜�T�C�Y
    string fileName_; //�t�@�C����
   /* VECTOR initialPosition_;
    bool alreadySet_;
    int settingNum_;*/
public:
    Icon(GameObject* parent);
    ~Icon();
    virtual void Update() override;
    virtual void Draw() override;

    void Load(const std::string& _fileName);

    string GetFileName() { return fileName_; }
    SIZE_F_2D GetGraphSizeF_2D() { return graphSizeF_; }
    SIZE_2D GetGraphSize_2D() { return graphSize_; }
    /*void SetInitialPosition(VECTOR _initialPosition) { initialPosition_ = _initialPosition; }
    int GetSettingNum() { return settingNum_; }*/
   
private:
};
