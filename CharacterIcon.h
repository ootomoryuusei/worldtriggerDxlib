#pragma once
#include"Icon.h"
#include"CharacterSetUIFrame.h"

class CharacterIcon
    :public Icon
{
public:
    CharacterIcon(GameObject* parent);
    ~CharacterIcon();
    void Update() override;
    void Draw() override;

    SIZE_2D GetIconSize() { return graphSize_; }
    void SetInitialPosition(VECTOR _initialPosition) { initialPosition_ = _initialPosition; }
    int GetSettingNum() { return settingNum_; }
    bool GetAlreadySet() { return alreadySet_; }
private:
    VECTOR initialPosition_;
    bool alreadySet_;
    int settingNum_;
};

