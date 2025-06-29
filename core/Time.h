#ifndef TIME_H
#define TIME_H

#include <ctime>
class Time {
private:
    int year, month, day, hour, minute;
    time_t rawTime;
    static Time simulatedNow;

public:
    Time(int y, int m, int d, int h = 0, int min = 0);
    static void setSimulatedNow(int y, int m, int d);
    int getDaysDifference(const Time& other) const;
    bool isRecent(int days) const;
    time_t getRaw() const { return rawTime; }
    static void setSimulatedNow(int y, int m, int d, int h = 0);
    static Time now();
};

#endif // TIME_H
