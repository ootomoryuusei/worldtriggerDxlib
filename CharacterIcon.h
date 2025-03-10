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
    bool GetAlreadySet(int _num) { return alreadySet_[_num]; }
private:
    VECTOR initialPosition_;
    bool alreadySet_[MAX_SELECT_CHARACTER];
    int settingNum_;
};

