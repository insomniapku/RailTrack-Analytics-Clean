#ifndef RAILWAY_H
#define RAILWAY_H

#include <vector>
#include <string>
#include "City.h"

class Railway {
private:
    std::string name;
    City* startCity;
    City* endCity;

public:
    Railway(const std::string& name, City* start, City* end);
    bool includes(City* a, City* b) const;
    std::vector<City*> getFullPath() const;
    std::string getName() const;
};

#endif // RAILWAY_H


