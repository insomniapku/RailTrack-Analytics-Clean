#include "Statistics.h"
#include <iostream>
#include <map>
#include <set>
#include <algorithm>
#include <chrono>
#include <random>
#include <unordered_map>
#include <queue>

void Statistics::addTrip(const Trip& trip) {
    trips.push_back(trip);
}

void Statistics::addCity(City* city) {
    allCities.push_back(city);
}

void Statistics::clearall(){
    trips.clear();
}

void Statistics::addRailway(const Railway& railway) {
    railways.push_back(railway);
}

void Statistics::setHometown(City* city) {
    hometown = city;
}

void Statistics::setWorkplace(City* city) {
    workplace = city;
}

std::vector<Trip> Statistics::getRecentTrips(int days) const {
    std::vector<Trip> recent;
    for (const auto& trip : trips) {
        if (trip.getStartTime().isRecent(days)) {
            recent.push_back(trip);
        }
    }
    return recent;
}

void Statistics::getTopCities(const std::vector<Trip>& trips,
    std::vector<std::pair<City*, int>>& startCounts,
    std::vector<std::pair<City*, int>>& endCounts) const {
    std::map<City*, int> startMap, endMap;
    for (const auto& trip : trips) {
        startMap[trip.getStart()]++;
        endMap[trip.getEnd()]++;
    }
    for (auto& p : startMap) startCounts.push_back(p);
    for (auto& p : endMap) endCounts.push_back(p);
    std::sort(startCounts.begin(), startCounts.end(), [](auto& a, auto& b) { return a.second > b.second; });
    std::sort(endCounts.begin(), endCounts.end(), [](auto& a, auto& b) { return a.second > b.second; });
}

std::vector<City*> Statistics::getUnvisitedViaCities() const {
    // 步骤1: 获取所有访问过的城市
    std::set<City*> visited;
    for (const auto& trip : trips) {
        visited.insert(trip.getStart());
        visited.insert(trip.getEnd());
    }

    // 步骤2: 获取所有经由城市
    std::set<City*> via;
    for (const auto& rail : railways) {
        via.insert(rail.getFullPath()[0]);
        via.insert(rail.getFullPath()[1]);
    }

    // 步骤3: 找出未访问的经由城市
    std::vector<City*> unvisited;
    for (auto c : via) {
        if (!visited.count(c)) unvisited.push_back(c);
    }

    // 步骤4: 如果未访问城市超过5个，随机选择5个
    if (unvisited.size() > 5) {
        // 创建随机数生成器
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::shuffle(unvisited.begin(), unvisited.end(), std::default_random_engine(seed));

        // 保留前5个元素
        unvisited.resize(5);
    }

    return unvisited;
}

std::vector<Railway*> Statistics::findRailwayPathBFS(const Trip& trip) {
    City* start = trip.getStart();
    City* goal = trip.getEnd();

    // 每个城市从哪条铁路来
    std::unordered_map<City*, std::pair<City*, Railway*>> parent;
    std::queue<City*> q;
    std::set<City*> visited;

    q.push(start);
    visited.insert(start);

    while (!q.empty()) {
        City* current = q.front();
        q.pop();

        for (const Railway& railway : railways) {
            std::vector<City*> path = railway.getFullPath();
            for (size_t i = 0; i + 1 < path.size(); ++i) {
                City* u = path[i];
                City* v = path[i + 1];

                // 建图是无向图，两个方向都考虑
                if (u == current && !visited.count(v)) {
                    visited.insert(v);
                    parent[v] = { u, const_cast<Railway*>(&railway) };
                    q.push(v);
                } else if (v == current && !visited.count(u)) {
                    visited.insert(u);
                    parent[u] = { v, const_cast<Railway*>(&railway) };
                    q.push(u);
                }
            }
        }
    }

    // 回溯路径
    std::vector<Railway*> result;
    if (!parent.count(goal)) {
        return result; // 无路径
    }

    City* curr = goal;
    while (curr != start) {
        auto [prev, rail] = parent[curr];
        result.push_back(rail);
        curr = prev;
    }

    std::reverse(result.begin(), result.end());
    return result;
}
/*std::string Statistics::evaluateUserType()const  {
    auto recentTrips = getRecentTrips(30); // 近一个月行程
    int totalTrips = recentTrips.size();

    if (totalTrips == 0) return "无行程记录 (No trips)";

    // 1. 统计小城市数量和大都市数量
    int smallCityCount = 0;
    int metropolisCount = 0;
    int totalCities = totalTrips * 2; // 每个行程有起点和终点

    for (const auto& trip : recentTrips) {
        if (trip.getStart() && trip.getStart()->getRank() == CityRank::SMALL) {
            smallCityCount++;
        }
        if (trip.getEnd() && trip.getEnd()->getRank() == CityRank::SMALL) {
            smallCityCount++;
        }
        if (trip.getStart() && trip.getStart()->getRank() == CityRank::METROPOLIS) {
            metropolisCount++;
        }
        if (trip.getEnd() && trip.getEnd()->getRank() == CityRank::METROPOLIS) {
            metropolisCount++;
        }
    }

    // 2. 统计回家次数 - 修复空指针问题
    int homeTrips = 0;
    if (workplace && hometown) {
        for (const auto& trip : recentTrips) {
            City* start = trip.getStart();
            City* end = trip.getEnd();

            if (start && end) {
                bool fromWorkToHome = (start == workplace && end == hometown);
                bool fromHomeToWork = (start == hometown && end == workplace);

                if (fromWorkToHome || fromHomeToWork) {
                    homeTrips++;
                }
            }
        }
    }

    //输出调试信息
    std::cout << "\n===== 调试信息 =====\n";
    std::cout << "总行程数: " << totalTrips << "\n";
    std::cout << "小城市数量: " << smallCityCount << "\n";
    std::cout << "大都市数量: " << metropolisCount << "\n";
    std::cout << "回家次数: " << homeTrips << "\n";
    if (workplace) std::cout << "工作城市: " << workplace->getName()
                  << " (" << static_cast<int>(workplace->getRank()) << ")\n";
    if (hometown) std::cout << "家乡: " << hometown->getName()
                  << " (" << static_cast<int>(hometown->getRank()) << ")\n";

    // 3. 完善用户画像算法
    // 条件1: 旷野闲游者
    if (smallCityCount >= 5 && static_cast<double>(smallCityCount) / totalCities > 0.5) {
        return "旷野闲游者 (Wilderness Wanderer)";
    }

    // 条件2: 小城奋斗者
    if (workplace &&
        (workplace->getRank() == CityRank::SMALL || workplace->getRank() == CityRank::MIDDLE) &&
        totalTrips <= 4) {
        return "小城奋斗者 (Small-town Striver)";
    }

    // 条件3: 都市内卷人
    if (workplace && workplace->getRank() == CityRank::METROPOLIS) {
        if (totalTrips <= 4 || static_cast<double>(metropolisCount) / totalCities > 0.5) {
            return "都市内卷人 (Metropolitan Insider)";
        }
    }

    // 条件4: 顾家蓝领人 - 修复等级比较逻辑
    if (workplace && hometown) {
        bool workHigherThanHome = static_cast<int>(workplace->getRank()) > static_cast<int>(hometown->getRank());

        if (workHigherThanHome && homeTrips >= 2) {
            return "顾家蓝领人 (Family-oriented Worker)";
        }
    }

    // 如果以上都不符合，根据行程数量分类
    if (totalTrips <= 2) {
        return "安居自得者 (Homebody)——具体的分类请继续探索吧！ (Undefined)";
    }
    else if (totalTrips >= 3 && totalTrips <= 8) {
        return "出差工作者 (Business Traveler)——具体的分类请继续探索吧！ (Undefined)";
    }
    else if (totalTrips >= 9) {
        return "古希腊掌管火车的神 (Train God)——具体的分类请继续探索吧！ (Undefined)";
    }
}
void Statistics::runAnalysis() {
    auto recent = getRecentTrips(30);
    std::vector<std::pair<City*, int>> start, end;
    getTopCities(recent, start, end);

    std::cout << "===== 年度出行分析报告 =====\n";

    std::cout << "\n最近常见始发城市:\n";
    for (int i = 0; i < std::min<int>(start.size(), 5); ++i)
        std::cout << i+1 << ". " << start[i].first->getName() << "（" << start[i].second << "次）\n";

    std::cout << "\n最近常见终点城市:\n";
    for (int i = 0; i < std::min<int>(end.size(), 5); ++i)
        std::cout << i+1 << ". " << end[i].first->getName() << "（" << end[i].second << "次）\n";

    auto unvisited = getUnvisitedViaCities();
    std::cout << "\n推荐探索未访问城市：";
    if (unvisited.empty()) std::cout << "无";
    else {
        for (auto c : unvisited) std::cout << c->getName() << " ";
    }

    std::cout << "\n\n用户画像类型：" << evaluateUserType() << "\n";
}*/
std::string Statistics::evaluateUserType() const {
    auto recentTrips = getRecentTrips(30); // 近一个月行程
    int totalTrips = recentTrips.size();
    if (totalTrips == 0) return "无行程记录 (No trips)";

    // 1. 统计回家次数
    int homeTrips = 0;
    if (workplace && hometown) {
        for (const auto& trip : recentTrips) {
            City* start = trip.getStart();
            City* end = trip.getEnd();
            if (start && end) {
                bool fromWorkToHome = (start == workplace && end == hometown);
                bool fromHomeToWork = (start == hometown && end == workplace);
                if (fromWorkToHome || fromHomeToWork) {
                    homeTrips++;
                }
            }
        }
    }

    // 2. 用户类型判断逻辑

    // 条件1：经常往返工作地与家乡
    if (homeTrips >= 2) {
        return "两地通勤者 (Dual-City Commuter)";
    }

    // 条件2：出行频繁（>= 10 次）
    if (totalTrips >= 10) {
        return "高铁达人 (Railway Expert)";
    }

    // 条件3：工作城市为大都市，出行不多
    if (workplace && workplace->getRank() == CityRank::METROPOLIS && totalTrips <= 4) {
        return "都市静居者 (Urban Settler)";
    }

    // 条件4：工作城市为中小城市，出行不频繁
    if (workplace &&
        (workplace->getRank() == CityRank::SMALL || workplace->getRank() == CityRank::MIDDLE) &&
        totalTrips <= 4) {
        return "小城定居人 (Local Homebody)";
    }

    // 条件5：出行中等偏多（5~9次），但无明显规律
    if (totalTrips >= 5 && totalTrips <= 9) {
        return "浮动探索者 (Drifting Explorer)";
    }

    // 条件6：只出过1~2次门
    if (totalTrips <= 2) {
        return "宅家守望者 (Stay-at-Home Watcher)";
    }

    // 默认分类
    return "出行旅者 (General Traveler)";
}
void Statistics::runAnalysis() {
    auto recent = getRecentTrips(30);
    std::vector<std::pair<City*, int>> start, end;
    getTopCities(recent, start, end); // 获取常见出发与到达城市

    std::cout << "\n======= 年度出行分析报告 =======\n";

    // 1. 总体出行统计
    int totalTrips = recent.size();
    std::set<City*> uniqueCities;
    for (const auto& trip : recent) {
        if (trip.getStart()) uniqueCities.insert(trip.getStart());
        if (trip.getEnd()) uniqueCities.insert(trip.getEnd());
    }

    std::cout << "\n过去30天总出行次数：" << totalTrips << " 次\n";
    std::cout << "共涉及城市数量：" << uniqueCities.size() << " 座\n";

    // 2. 常见出发城市（前3）
    std::cout << "\n常见出发城市 TOP3：\n";
    if (start.empty()) {
        std::cout << "暂无出发城市数据。\n";
    } else {
        for (int i = 0; i < std::min<int>(start.size(), 3); ++i) {
            std::cout << i + 1 << ". " << start[i].first->getName()
            << "（" << start[i].second << " 次出发）\n";
        }
    }

    // 3. 常见到达城市（前3）
    std::cout << "\n常见到达城市 TOP3：\n";
    if (end.empty()) {
        std::cout << "暂无到达城市数据。\n";
    } else {
        for (int i = 0; i < std::min<int>(end.size(), 3); ++i) {
            std::cout << i + 1 << ". " << end[i].first->getName()
            << "（" << end[i].second << " 次到达）\n";
        }
    }

    // 4. 推荐未探索城市
    auto unvisited = getUnvisitedViaCities();
    std::cout << "\n推荐探索的未到访城市：";
    if (unvisited.empty()) {
        std::cout << "（暂无建议，已经很全面啦！）\n";
    } else {
        for (auto city : unvisited) {
            std::cout << city->getName() << " ";
        }
        std::cout << "\n";
    }

    // 5. 用户画像类型
    std::cout << "\n综合分析用户画像类型：\n→ " << evaluateUserType() << "\n";

    std::cout << "======= 分析结束，感谢使用 =======\n";
}

City* Statistics::getCityByName(const std::string& name) {
    for (City* city : allCities) {
        if (city->getName() == name) {
            return city;
        }
    }
    return nullptr;
}

void Statistics::printAllCities() const {
    for (City* city : allCities) {
        std::cout << city->getName() << std::endl;
    }
}

const std::vector<Trip>& Statistics::getAllTrips() const {
    return trips; // 假设成员变量是：std::vector<Trip> trips;
}
const std::vector<Railway>& Statistics::getAllRailways() const {
    return railways;
}

