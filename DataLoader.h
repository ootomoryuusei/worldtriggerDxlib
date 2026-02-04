#pragma once
#include"Engine/CsvReader.h"
#include"Data.h"
#include<string>
#include <vector>

using std::string;
using std::vector;

class DataLoader { 
public:
    static vector<Data> Load(CsvReader& reader) {
        vector<Data> result;

        if (reader.GetHeight() < 2) return result;

        vector<string> keys;
        for (size_t col = 0; col < reader.GetWidth(0); ++col) {
            keys.push_back(reader.GetString(col, 0));
        }

        for (size_t row = 1; row < reader.GetHeight(); ++row) {
            Data status;
            for (int col = 0; col < keys.size(); ++col) {
                status.Set(keys[col], reader.GetString(col, row));
            }
            result.push_back(status);
        }
        return result;
    }

    template<class T,class Factory>
    static T GetByName(const string& key, const string& name, const vector<Data>& list) {
        for (const auto& itr : list) {
            if (itr.GetString(key) == name) {
                return Factory::CreateFromStatusData(itr);
            }
        }
    }
    
    static int GetByIndex(const string& key,const string& name, const vector<Data>& list) {
        for (size_t i = 0; i < list.size();i++) {
            if (list[i].GetString(key) == name) {
                return static_cast<int>(i);
            };
        }
        return -1;
    }
};