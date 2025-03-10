#pragma once
#include"Icon.h"
class TriggerIcon :
    public Icon
{
public:
    TriggerIcon(GameObject* parent);
    ~TriggerIcon();
    void Update() override;
    void Draw() override;

    void Load(const std::string& _fileName);

    SIZE_2D GetIconSize() { return graphSize_; }
    void SetInitialPosition(VECTOR _initialPosition) { initialPosition_ = _initialPosition; }
    int GetSettingNum() { return settingNum_; }
    string GetFileName() { return fileName_; }
    bool GetAlreadySet() { return alreadySet_; }
private:
    SIZE_2D graphSize_; //アイコンの画像サイズ
    std::string fileName_;
    VECTOR initialPosition_;
    bool alreadySet_;
    int settingNum_;
};

