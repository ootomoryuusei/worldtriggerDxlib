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

    void SetInitialPosition(VECTOR _initialPosition) { initialPosition_ = _initialPosition; }
    int GetSettingNum() { return settingNum_; }
    string GetFileName() { return fileName_; }
    bool GetAlreadySet() { return alreadySet_; }
private:

    VECTOR initialPosition_;
    bool alreadySet_;
    int settingNum_;
};

