#pragma once
#include "Object3D.h"
#include<vector>

using std::vector;
using std::string;

class Icon :
    public Object3D
{
protected:
    SIZE_F_2D graphSizeF_; //アイコンの画像サイズ(float)
    SIZE_2D graphSize_; //アイコンの画像サイズ
    string fileName_; //ファイル名
    bool canVisible_; //iconを表示するかしないか
    int num_;
    int createNum_;
public:
    Icon(GameObject* parent);
    ~Icon();
    virtual void Update() override;
    virtual void Draw() override;

    void Load(const std::string& _fileName);

    string GetFileName() { return fileName_; }
    SIZE_F_2D GetGraphSizeF_2D() { return graphSizeF_; }
    SIZE_2D GetGraphSize_2D() { return graphSize_; }

    void SetCanVisible(bool _canVisible) { canVisible_ = _canVisible; }
    bool GetCanVisible() { return canVisible_; }
    void SetNum(int _num) { num_ = _num; }
    int GetNum() { return num_; }
    void SetCreateNum(int _createNum) { createNum_ = _createNum; }
    int GetCreateNum() { return createNum_; }
private:
};
