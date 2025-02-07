#pragma once
#include "Object3D.h"
#include<vector>

class TriggerIcon;
class CsvReader;
class CharacterIcon;

class TriggerIcons :
    public Object3D
{
public:
    TriggerIcons(GameObject* parent);
    ~TriggerIcons();
    void Update() override;
    void Draw() override;

private:
    std::vector<TriggerIcon*> pTIcons_;
    std::vector<CharacterIcon*> pCIcons_;
    CsvReader* csv_;
    int FN2DLine;
    MYTRIGGER trigger;
    string DLC; //ディレクトリ
};

