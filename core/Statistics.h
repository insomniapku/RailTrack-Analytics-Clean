#ifndef STATISTICS_H
#define STATISTICS_H

#include <vector>
#include "Trip.h"
#include "City.h"
#include "Railway.h"

class Statistics {
private:
    std::vector<Trip> trips;
    std::vector<City*> allCities;
    std::vector<Railway> railways;
    City* hometown = nullptr;
    City* workplace = nullptr;

public:
    void addTrip(const Trip& trip);
    void addCity(City* city);
    void addRailway(const Railway& railway);
    void setHometown(City* city);
    void setWorkplace(City* city);

    std::vector<Trip> getRecentTrips(int days) const;
    void getTopCities(const std::vector<Trip>& trips,
                      std::vector<std::pair<City*, int>>& startCounts,
                      std::vector<std::pair<City*, int>>& endCounts) const;
    std::vector<City*> getUnvisitedViaCities() const;
    std::string evaluateUserType() const;
    void runAnalysis();  // 打印报告
    City* getCityByName(const std::string& name);
    Railway* getRailwayByName(const std::string& name);
    const std::vector<Railway>& getAllRailways() const;
    void addTri(const Trip&);
    void printAllCities() const;
    void clearall();
    const std::vector<Trip>& getAllTrips() const;
    std::vector<Railway*> findRailwayPathBFS(const Trip& trip);
};


#endif // STATISTICS_H
