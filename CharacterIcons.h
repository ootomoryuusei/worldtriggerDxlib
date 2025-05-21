#pragma once
#include "Icon.h"
#include<vector>
#include"CharacterIcon.h"
#include"Engine/CsvReader.h"

class CharacterIcons :
    public Icon
{
public:
    CharacterIcons(GameObject* parent);
    ~CharacterIcons();
    void Update() override;
    void Draw() override;

    auto GetpCIcons() { return pCIcons_; }
private:
    vector<CharacterIcon*> pCIcons_;
    CsvReader* csv_;
    int FN2DLine;
    string DLC; //ディレクトリ
};

