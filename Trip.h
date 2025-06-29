#ifndef TRIP_H
#define TRIP_H

#include <QString>

struct Trip {
    QString fromCity;
    QString toCity;
    int distance;
    bool stopAtToCity;

    Trip(QString from, QString to, int dist, bool stop = true)
        : fromCity(from), toCity(to), distance(dist), stopAtToCity(stop) {}
};

#endif // TRIP_H