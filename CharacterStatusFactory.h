#pragma once
#include"Data.h"
#include<string>

using std::string;

struct CharacterStatus {
    std::string name; //ƒLƒƒƒ‰–¼
    int action; //s“®—Í
    int trion; //ƒgƒŠƒIƒ“
    int attack; //UŒ‚
    int defense; //–hŒä
    int avoidance; //‰ñ”ğ
    int support; //‰‡Œì
    int technique; //‹Zp
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