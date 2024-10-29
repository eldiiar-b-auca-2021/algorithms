
#ifndef UTIL_H
#define UTIL_H
#include <vector>
#include <string>
#include "city.h"
struct exit_exception : public std::exception {
    const char *what() const noexcept override {
        return "Exiting the program...";
    }
};

struct impossible_route_exception : public std::exception {
    const char *what() const noexcept override {
        return "There is no possible route between the cities with this maximum distance. Try upgrading your planes so they can fly further.";
    }
};

City findCityByName(std::vector<City>& cities, const std::string& originName){
    for (auto& city : cities) {
        if (city.getName() == originName) {
            return city;
        }
    }
    throw std::invalid_argument("City not found.");
}
#endif //UTIL_H
