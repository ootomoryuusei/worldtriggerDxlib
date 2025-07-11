#pragma once
#include "Data.h"
#include <string>

using std::string;

struct TriggerStatus {
    std::string name;
    float startPercent;
    float percent;
    float angle;
    float rangeSize;
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