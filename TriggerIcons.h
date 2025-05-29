#pragma once
#include "Icon.h"
#include<vector>
#include<array>
#include"TriggerIcon.h"
#include"CharacterIcon.h"

class CsvReader;

//class TriggerIcon;
//class CharacterIcon;
//class CharacterSetUIFrame;
//class TriggerSetUIFrame;

using std::vector;
using std::array;

class TriggerIcons :
    public Icon
{
public:
    TriggerIcons(GameObject* parent);
    ~TriggerIcons();
    void Initialize() override;
    void Update() override;
    void Draw() override;

    auto GetpTIcons() { return pALLTIcons_; }

    void SetTriggers(CharacterIcon* pCharacterIcon, MAIN_SUB type);

    void SetpCharacterIcon_(CharacterIcon* _pChracterIcon) { pCharacterIcon_ = _pChracterIcon; }
private:
    CsvReader* csv_;
    array<vector<TriggerIcon*>, MAX> pTIcons_;
    array<vector<TriggerIcon*>,MAX> pCanSet_;
    vector<TriggerIcon*> pSubTIcons_;
    vector<TriggerIcon*> pALLTIcons_;
    CharacterIcon* pCharacterIcon_;
    bool firstSet;

    void DefaultSetTriggers(CharacterIcon* pCharacterIcon, MAIN_SUB type);
    void CreateCanSet(CharacterIcon* pCharacterIcon,MAIN_SUB type);
};

