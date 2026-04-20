#include "database.h"
#include <iostream>

Database::Database(const std::string& path) {
    int result=sqlite3_open(path.c_str(), &db);
    if (result!=SQLITE_OK) {
        std::cerr<<"Failed to open database: "<<sqlite3_errmsg(db)<<std::endl;
    }
}

Database::~Database() {
    sqlite3_close(db);
}

void Database::createTables() {
    const char* sql = R"(
        CREATE TABLE IF NOT EXISTS drivers (
            number    INTEGER PRIMARY KEY,
            code      TEXT,
            firstName TEXT,
            lastName  TEXT,
            team      TEXT,
            country   TEXT
        );
    )";

    char* errorMsg=nullptr;
    int result=sqlite3_exec(db, sql, nullptr, nullptr, &errorMsg);

    if (result!=SQLITE_OK) {
        std::cerr<<"Failed to create table: "<<errorMsg<<std::endl;
        sqlite3_free(errorMsg);
    }
}

void Database::insertDrivers(const std::vector<Driver>& drivers) {
    sqlite3_exec(db, "DELETE FROM drivers;", nullptr, nullptr, nullptr);
    for (const auto& d : drivers) {
        const char* sql = R"(
            INSERT INTO drivers (number, code, firstName, lastName, team, country)
            VALUES (?, ?, ?, ?, ?, ?);
        )";

        sqlite3_stmt* stmt;
        sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);

        sqlite3_bind_int (stmt, 1, d.number);
        sqlite3_bind_text(stmt, 2, d.code.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 3, d.firstName.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 4, d.lastName.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 5, d.team.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 6, d.country.c_str(), -1, SQLITE_STATIC);

        sqlite3_step(stmt);
        sqlite3_finalize(stmt);
    }
}

std::vector<Driver> Database::getDrivers() {
    std::vector<Driver> drivers;

    const char* sql = "SELECT number, code, firstName, lastName, team, country FROM drivers;";

    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        Driver d;
        d.number=sqlite3_column_int (stmt, 0);
        d.code=(const char*)sqlite3_column_text(stmt, 1);
        d.firstName=(const char*)sqlite3_column_text(stmt, 2);
        d.lastName=(const char*)sqlite3_column_text(stmt, 3);
        d.team=(const char*)sqlite3_column_text(stmt, 4);
        d.country=(const char*)sqlite3_column_text(stmt, 5);
        drivers.push_back(d);
    }

    sqlite3_finalize(stmt);
    return drivers;
}