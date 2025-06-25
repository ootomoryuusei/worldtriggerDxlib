#pragma once
#include<functional>
#include<unordered_map>
#include<string>

using std::function;
using std::unordered_map;
using std::string;

template<class T>
class BaseFactory
{
public:
	using Creator = function<T*(GameObject*)>;

    void Register(const string& name, Creator creator) {
        creators_[name] = creator;
    }
    
    T* Create(const string& name, GameObject* parent) {
        auto it = creators_.find(name);
        if (it != creators_.end()) {
           /* return dynamic_cast<T*>(base);*/
            return it->second(parent);
        }
        return nullptr;
    }

    bool Has(const string& name) const {
        return creators_.find(name) != creators_.end();
    }
private:
    unordered_map<string, Creator> creators_;
};

