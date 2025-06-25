#pragma once
#include"BaseFactory.h"

template<class T,class Factory>
struct AutoRegister
{
    AutoRegister(const std::string& name) {
        Factory::Instance().Register(name, [](GameObject* parent)-> T*{
            return Instantiate<T>(parent);
            });
    }
};
