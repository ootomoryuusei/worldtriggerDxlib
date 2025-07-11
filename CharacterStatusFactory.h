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
        status.name = data.GetString("�L������");
        status.action = data.GetInt("�s����");
        status.trion = data.GetInt("�g���I��");
        status.attack = data.GetInt("�U��");
        status.defense = data.GetInt("�h��");
        status.avoidance = data.GetInt("���");
        status.support = data.GetInt("����");
        status.technique = data.GetInt("�Z�p");
        return status;
    }
};