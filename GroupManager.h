#pragma once
#include"Engine/GameObject.h"
#include"GroupBase.h"
#include<unordered_map>
#include<string>

using std::unordered_map;
using std::string;

class GroupManager : public GameObject {
public:
	GroupManager(GameObject* parent) : GameObject(parent,"GroupManager") {}

	template<class T>
	T* CreateGroup(const string& name) {
		if (groups_.count(name)) return nullptr;
		T* group = Instantiate<T>(this);
		groups_[name] = group;
		return group;
	}

	GroupBase* GetGroup(const string& name) {
		auto it = groups_.find(name);
		return it != groups_.end() ? it->second : nullptr;
	}

	template<class T>
	T* GetGroupAs(string& name) {
		return dynamic_cast<T*>(GetGroup(name));
	}
private:
	unordered_map<string,GroupBase*> groups_;
};
