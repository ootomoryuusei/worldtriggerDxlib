#pragma once
#include"Icon.h"
#include<vector>

using std::vector;

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

    auto GetInFrame() { return inFrame_; }
    bool GetCatchIcon() { return false; }

    void SetMyTrigger(MYTRIGGER _myTrigger) { myTrigger = _myTrigger; }
    MYTRIGGER GetMyTrigger() { return myTrigger; }
private:
    VECTOR initialPosition_;
    bool alreadySet_[MAX_SELECT_CHARACTER];
    int settingNum_;
    vector<bool> inFrame_;
    bool isCatchIcon_;

    MYTRIGGER myTrigger;
};

