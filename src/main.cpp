#include <iostream>
#include "fetcher.h"
#include "parser.h"
#include "database.h"
#include "dashboard.h"

int main() {
    std::cout << "Fetching F1 data..." << std::endl;

    std::string response = httpGet("https://api.openf1.org/v1/drivers?session_key=latest");
    std::vector<Driver> drivers = parseDrivers(response);

    Database db("f1.db");
    db.createTables();
    db.insertDrivers(drivers);

    std::vector<Driver> fromDb = db.getDrivers();
    runDashboard(fromDb);

    return 0;
}