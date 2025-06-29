#include "Time.h"
#include <cmath>

Time Time::simulatedNow = Time(2025, 5, 31);

Time::Time(int y, int m, int d, int h, int min)
    : year(y), month(m), day(d), hour(h), minute(min) {
    struct tm timeinfo = {};
    timeinfo.tm_year = y - 1900;
    timeinfo.tm_mon = m - 1;
    timeinfo.tm_mday = d;
    timeinfo.tm_hour = h;
    timeinfo.tm_min = min;
    rawTime = mktime(&timeinfo);
}

void Time::setSimulatedNow(int y, int m, int d, int h) {
    simulatedNow = Time(y, m, d, h);
}
Time Time::now() {
    return simulatedNow;
}

int Time::getDaysDifference(const Time& other) const {
    return std::abs(difftime(rawTime, other.rawTime) / (60 * 60 * 24));
}

bool Time::isRecent(int days) const {
    time_t nowTime = simulatedNow.rawTime;
    double diff = difftime(nowTime, rawTime);
    return (diff >= 0 && diff < (days * 86400));
}
