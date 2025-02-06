#pragma once
#include"Object3D.h"
class TriggerIcon :
    public Object3D
{
public:
    TriggerIcon(GameObject* parent);
    ~TriggerIcon();
    void Update() override;
    void Draw() override;

    void Load(const std::string& _fileName);

    SIZE_2D GerGraphSize() { return graphSize_; }
    void SetInitialPosition(VECTOR _initialPosition) { initialPosition_ = _initialPosition; }
    int GetSettingNum() { return settingNum_; }
private:
    SIZE_2D graphSize_; //アイコンの画像サイズ
    std::string fileName_;
    VECTOR initialPosition_;
    bool alreadySet_;
    int settingNum_;
};

