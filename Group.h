#pragma once
#include"Engine/GameObject.h"
#include<list>
#include<string>
#include<vector>

using std::vector;
using std::list;
using std::string;

template<class T>
class Group : public GameObject {
public:
	Group(GameObject* parent,const string& name = "") : GameObject(parent,name){}

	void Add(T* obj) {
		members_.push_back(obj);
	}

	const vector<T*>& GetAll() const {
		return members_;
	}
private:
	vector<T*> members_;
};
