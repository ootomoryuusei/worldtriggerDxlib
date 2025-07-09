#pragma once
#include<unordered_map>
#include<string>

using std::unordered_map;
using std::string;

class Data
{
public:
	void Set(const string& key, const string& value) {
		data_[key] = value;
	}
	string GetString(const string& key) const { return data_.at(key); }
	int GetInt(const string& key)const { return stoi(data_.at(key)); }
	float GetFloat(const string& key)const { return stof(data_.at(key)); }
private:
	unordered_map<string, string> data_;
};

