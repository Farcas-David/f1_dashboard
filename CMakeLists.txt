cmake_minimum_required(VERSION 3.20)
project(f1_dashboard)

set(CMAKE_CXX_STANDARD 17)

find_package(CURL REQUIRED)
find_package(nlohmann_json REQUIRED)
find_package(unofficial-sqlite3 REQUIRED)
find_package(ftxui REQUIRED)

add_executable(f1_dashboard
        src/main.cpp
        src/fetcher.cpp
        src/fetcher.h
        src/models.h
        src/parser.cpp
        src/parser.h
)

target_link_libraries(f1_dashboard
        PRIVATE
        CURL::libcurl
        nlohmann_json::nlohmann_json
        unofficial::sqlite3::sqlite3
        ftxui::screen
        ftxui::dom
        ftxui::component
)