#include <iostream>
#include "fetcher.h"
#include "parser.h"

int main() {
    std::string response = httpGet("https://api.openf1.org/v1/drivers?session_key=latest");

    std::vector<Driver> drivers = parseDrivers(response);

    for (const auto& d : drivers) {
        std::cout<<d.number<<" | "<< d.code<<" | "
                 <<d.firstName<<" "<<d.lastName
                 <<" | "<<d.team<<std::endl;
    }

    return 0;
}