#include "TripManager.h"
#include <QStringList>

void TripManager::addTrip(const Trip& trip) {
    trips.append(trip);
}

QString TripManager::generateReport() const {
    QMap<QString, int> visitCount;
    QMap<QString, int> passThroughCount;
    QSet<QString> allCities;
    int totalDistance = 0;

    for (const Trip& trip : trips) {
        allCities.insert(trip.fromCity);
        allCities.insert(trip.toCity);
        totalDistance += trip.distance;

        if (trip.stopAtToCity)
            visitCount[trip.toCity]++;
        else
            passThroughCount[trip.toCity]++;
    }

    QString mostVisited;
    int maxVisits = 0;
    for (auto it = visitCount.begin(); it != visitCount.end(); ++it) {
        if (it.value() > maxVisits) {
            mostVisited = it.key();
            maxVisits = it.value();
        }
    }

    QStringList passThroughCities;
    for (auto it = passThroughCount.begin(); it != passThroughCount.end(); ++it) {
        if (!visitCount.contains(it.key()))
            passThroughCities << it.key();
    }

    QStringList unvisitedCities;
    for (const QString& city : allCities) {
        if (!visitCount.contains(city))
            unvisitedCities << city;
    }

    QString report;
    report += "📊 年度出行报告\n";
    report += "------------------------\n";
    report += QString("总行程数：%1 次\n").arg(trips.size());
    report += QString("累计里程：%1 公里\n").arg(totalDistance);
    report += QString("去过最多的城市：%1（%2 次）\n").arg(mostVisited, QString::number(maxVisits));
    report += QString("经常路过但未停留的城市：%1\n").arg(passThroughCities.join(", "));
    report += "\n🧭 出行建议\n";
    report += "------------------------\n";
    if (!unvisitedCities.isEmpty()) {
        report += QString("建议探索以下未曾停留的城市：%1\n").arg(unvisitedCities.join(", "));
    } else {
        report += "你已经探索了所有城市！可考虑优化路径减少重复。\n";
    }

    return report;
}