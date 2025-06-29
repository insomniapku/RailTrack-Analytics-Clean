#include "StatisticsInitializer.h"

void StatisticsInitializer::initialize(Statistics& stats) {
    Time::setSimulatedNow(2025, 5, 29);

    // 构造城市
    City* beijing = new City("北京", 500, 300, CityRank::METROPOLIS, "中国首都，历史文化名城");
    City* shanghai = new City("上海", 800, 400, CityRank::METROPOLIS, "国际化大都市，经济中心");
    City* xuzhou = new City("徐州", 550, 350, CityRank::MIDDLE, "五省通衢，兵家必争之地");
    City* hometown = new City("信阳", 520, 370, CityRank::HOMETOWN, "山水茶都，豫风楚韵");
    City* workplace = new City("武汉", 580, 400, CityRank::WORKPLACE, "九省通衢，大学之城");

    // 添加城市到统计器
    stats.addCity(beijing);
    stats.addCity(shanghai);
    stats.addCity(xuzhou);
    stats.addCity(hometown);
    stats.addCity(workplace);

    // 创建铁路
    Railway* jinghu = new Railway("京沪铁路", beijing, shanghai);
    jinghu->addViaCity(xuzhou);
    stats.addRailway(*jinghu);

    // 添加行程
    Trip trip1(hometown, workplace, Time(2025, 5, 1), Time(2025, 5, 1, 12), jinghu);
    Trip trip2(workplace, shanghai, Time(2025, 5, 2), Time(2025, 5, 2, 15), jinghu);

    stats.addTrip(trip1);
    stats.addTrip(trip2);

    // 设置工作/家乡
    stats.setHometown(hometown);
    stats.setWorkplace(workplace);
}
