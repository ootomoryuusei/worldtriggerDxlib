#pragma once
#include"Icon.h"
#include<vector>
#include"IconFactory.h"
#include"AutoRegister.h"
#include "CharacterStatusFactory.h"

class CharacterData;
class TriggerSetUI;
class TriggerIcons;

using std::vector;

class CharacterIcon
    :public Icon
{
public:
    CharacterIcon(GameObject* parent);
    ~CharacterIcon();
    void Initialize() override;
    void Update() override;
    void Draw() override;

    const auto& GetpData()const { return pData_; }
private:
    bool createUI;

    TriggerSetUI* pT_SetUI_;
    TriggerIcons* pT_Icons_;

    CharacterData* pData_;

    static AutoRegister<Icon, IconFactory> register_;
};

