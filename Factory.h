#pragma once
#include<functional>
#include<unordered_map>
#include<string>
#include "Engine/GameObject.h"

using std::function;
using std::unordered_map;
using std::string;

class Factory
{
public:
	using Creator = function<GameObject* (GameObject* parent)>;

	static Factory& Instance() {
		static Factory instance;
		return instance;
	}

    void Register(const std::string& name, Creator creator) {
        creators_[name] = creator;
    }
    
    GameObject* Create(const std::string& name, GameObject* parent) {
        auto it = creators_.find(name);
        if (it != creators_.end()) {
            return (it->second)(parent);
        }
        return nullptr;
    }
private:
    unordered_map<string, Creator> creators_;
};

