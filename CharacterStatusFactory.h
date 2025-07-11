#pragma once
#include"Data.h"
#include<string>

using std::string;

struct CharacterStatus {
    std::string name;
    int action;
    int trion;
    int attack;
    int defense;
    int avoidance;
    int support;
    int technique;
};

class CharacterStatusFactory {
public:
    static CharacterStatus CreateFromStatusData(const Data& data) {
        CharacterStatus status;
        status.name = data.GetString("ƒLƒƒƒ‰–¼");
        status.action = data.GetInt("s“®—Í");
        status.trion = data.GetInt("ƒgƒŠƒIƒ“");
        status.attack = data.GetInt("UŒ‚");
        status.defense = data.GetInt("–hŒä");
        status.avoidance = data.GetInt("‰ñ”ğ");
        status.support = data.GetInt("‰‡Œì");
        status.technique = data.GetInt("‹Zp");
        return status;
    }
};