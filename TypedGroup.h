#pragma once
#include<unordered_set>
#include<algorithm>
#include"GroupBase.h"

using std::unordered_set;

template<class T>
class TypedGroup : public GroupBase {
public:
	using ObjectList = unordered_set<T*>;

	void Add(T* obj) {
		if (members_.insert(obj).second) {
			obj->AddGroup(this);
		}
	}

	void Remove(T* obj) override {
		T* casted = dynamic_cast<T*>(obj);
		if (casted && members_.erease(casted)) {
			obj->RemoveGroup(this);
		}
	}

	const ObjectList& GetObjects() const {
		return members_;
	}
protected:
	ObjectList members_;
};
