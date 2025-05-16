#pragma once
#include "Engine/GameObject.h"
#include"CharacterIcon.h"
#include"Engine/CsvReader.h"
#include<vector>

#include"TriggerSetUI.h"
#include"TriggerSetUIFrames.h"
#include"TriggerSetButton.h";
#include"TriggerIcons.h"



using std::vector;
using std::string;

class SetIcons :
    public GameObject
{
public:
    SetIcons(GameObject* parent);
    ~SetIcons();
    void Initialize() override;
    void Update() override;
    void Draw() override;

    auto GetFrames() { return pTSUIFSs_; }
    auto GetIcons() { return pTIcons_; }
private:
    vector<CharacterIcon> pSelectCIcons_;
    vector<int> selectCharNum_;
    CsvReader* csv_;
    int FNSCNLine;
    int FN2DLine;
    string DLC; //ディレクトリ

    vector<TriggerSetButton*> pTSButtons_;
    vector<TriggerSetUIFrames*> pTSUIFSs_;
    vector<TriggerIcons*> pTIcons_;
};

