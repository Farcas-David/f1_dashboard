#include "parser.h"
#include <nlohmann/json.hpp>
#include <iostream>

using json = nlohmann::json;

std::string safeString(const json& item, const std::string& key, const std::string& fallback = "") {
    if (item.contains(key)&&!item[key].is_null()) {
        return item[key].get<std::string>();
    }
    return fallback;
}

int safeInt(const json& item, const std::string& key, int fallback = 0) {
    if (item.contains(key)&&!item[key].is_null()) {
        return item[key].get<int>();
    }
    return fallback;
}

std::vector<Driver> parseDrivers(const std::string& jsonStr) {
    std::vector<Driver> drivers;

    try {
        json data = json::parse(jsonStr);

        for (const auto& item : data) {
            Driver d;
            d.number=safeInt(item, "driver_number");
            d.code=safeString(item, "name_acronym");
            d.firstName=safeString(item, "first_name");
            d.lastName=safeString(item, "last_name");
            d.team=safeString(item, "team_name");
            d.country=safeString(item, "country_code");
            drivers.push_back(d);
        }
    } catch (const json::exception& e) {
        std::cerr<<"JSON parse error: "<<e.what()<<std::endl;
    }

    return drivers;
}