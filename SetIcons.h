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
private:
    vector<CharacterIcon> pSelectCIcons_;
    vector<int> selectCharNum_;
    CsvReader* csv_;
    int FNSCNLine;
    int FN2DLine;
    string DLC; //ディレクトリ
};

