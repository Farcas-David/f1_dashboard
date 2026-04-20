#pragma once
#include "models.h"
#include <vector>
#include <string>
#include <sqlite3.h>

class Database {
public:
    Database(const std::string& path);
    ~Database();

    void createTables();
    void insertDrivers(const std::vector<Driver>& drivers);
    std::vector<Driver> getDrivers();

private:
    sqlite3* db;
};