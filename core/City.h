#ifndef CITY_H
#define CITY_H

#include <string>
#include <utility>

enum class CityRank {
    SMALL, MIDDLE, METROPOLIS, HOMETOWN, WORKPLACE
};

class City {
private:
    std::string name;
    int visitCount;
    std::string recoText;
    std::pair<int, int> position;
    CityRank rank;
    bool lighted;           // 是否被点亮（单次行程中经过）

public:
    City(const std::string& n, int x, int y, CityRank r, const std::string& reco = "");
    void incrementVisit();
    std::string getName() const;
    int getVisitCount() const;
    std::string getRecoText() const;
    CityRank getRank() const;
    std::pair<int, int> getPosition() const;
    void lightUp();
    void resetLight();
    bool isLighted();
    void setRecoText(const std::string& text) ;
    void printInfo() const ;
};

#endif // CITY_H
