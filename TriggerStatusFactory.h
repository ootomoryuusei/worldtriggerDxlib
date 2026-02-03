#pragma once
#include "Data.h"
#include <string>

using std::string;

struct TriggerStatus {
    std::string name; //トリガー名
    float startPercent; //開始パーセント
    float percent; //パーセント
    float angle; //角度
    float rangeSize; //レンジサイズ
};

class TriggerStatusFactory {
public:
    static TriggerStatus CreateFromStatusData(const Data& data) {
        TriggerStatus status;
        status.name = data.GetString("WeaponName");
        status.startPercent = data.GetFloat("StartPercent");
        status.percent = data.GetFloat("Percent");
        status.angle = data.GetFloat("Angle");
        status.rangeSize = data.GetFloat("RangeSize");
        return status;
    }
};