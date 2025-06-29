#include "City.h"

City::City(const std::string& n, int x, int y, CityRank r, const std::string& reco)
    : name(n), position({x, y}), rank(r), recoText(reco), visitCount(0) {}

void City::incrementVisit() { visitCount++; }

std::string City::getName() const { return name; }

int City::getVisitCount() const { return visitCount; }

std::string City::getRecoText() const { return recoText; }

CityRank City::getRank() const { return rank; }

std::pair<int, int> City::getPosition() const { return position; }
