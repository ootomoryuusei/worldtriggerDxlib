#pragma once
#include"Icon.h"
#include<vector>
#include"IconFactory.h"
#include"AutoRegister.h"

class TriggerSetUI;
class TriggerIcons;

using std::vector;

class CharacterIcon
    :public Icon
{
public:
    CharacterIcon(GameObject* parent);
    ~CharacterIcon();
    void Update() override;
    void Draw() override;

    void SetInitialPosition(VECTOR _initialPosition) { initialPosition_ = _initialPosition; }
    int GetSettingNum() { return settingNum_; }
    bool GetAlreadySet(int _num) { return alreadySet_[_num]; }

    auto GetInFrame() { return inFrame_; }
    bool GetCatchIcon() { return false; }
private:
    VECTOR initialPosition_;
    bool alreadySet_[MAX_SELECT_CHARACTER];
    int settingNum_;
    vector<bool> inFrame_;
    bool isCatchIcon_;

    bool createUI;

    TriggerSetUI* pT_SetUI_;
    TriggerIcons* pT_Icons_;

    static AutoRegister<Icon, IconFactory> register_;
};

