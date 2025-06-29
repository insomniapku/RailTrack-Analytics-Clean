#include "Trip.h"

Trip::Trip(City* fro, City* t, Time start, Time end)
    : from(fro), to(t), departure(start), arrival(end) {
    if (from) from->incrementVisit();
    if (to) to->incrementVisit();
}

City* Trip::getStart() const { return from; }

City* Trip::getEnd() const { return to; }

Time Trip::getStartTime() const { return departure; }

Time Trip::getEndTime() const { return arrival; }


