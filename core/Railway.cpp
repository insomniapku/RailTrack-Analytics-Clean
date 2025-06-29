#include "Railway.h"
#include <QMessageBox>
#include <sstream>
//#include<iomanip>
#include<iostream>
#include <QPalette>
#include <QPixmap>
#include <QPainter>

Railway::Railway(const std::string& name, City* start, City* end)
    : name(name), startCity(start), endCity(end) {}

std::string Railway::getName() const {
    return name;
}

bool Railway::includes(City* a, City* b) const {
    bool result = (a == startCity && b == endCity) || (a == endCity && b == startCity);
    if (result) {
        qDebug() << "✅ 找到铁路:" << QString::fromStdString(name)
            << "连接" << QString::fromStdString(a->getName()) << "-" << QString::fromStdString(b->getName());
    }
    return result;
}


std::vector<City*> Railway::getFullPath() const {
    return {startCity, endCity};
}

