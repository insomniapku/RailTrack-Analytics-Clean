#ifndef TRIP_H
#define TRIP_H

#include "City.h"
#include "Time.h"
#include "Railway.h"

class Trip {
private:
    City* from;       // ✅ 起点城市
    City* to;         // ✅ 终点城市
    Time departure;   // ✅ 出发时间
    Time arrival;     // ✅ 到达时间

public:
    // 构造函数
    Trip(City* fro, City* t, Time start, Time end);


    // 基本信息获取
    City* getStart() const;
    City* getEnd() const;
    Time getStartTime() const;
    Time getEndTime() const;
    Railway* getRailway() const;

    // 可选：打印行程信息（用于调试或分析报告）
    void printInfo() const;
};

#endif // TRIP_H
