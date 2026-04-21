#include "dashboard.h"
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/component/component.hpp>

using namespace ftxui;

void runDashboard(const std::vector<Driver>& drivers) {
    auto screen = ScreenInteractive::Fullscreen();

    auto makeRow = [](std::string num, std::string code, std::string name, std::string team, std::string country) {
        return hbox({
            text(num)     | size(WIDTH, EQUAL, 6),
            text(code)    | size(WIDTH, EQUAL, 6),
            text(name)    | size(WIDTH, EQUAL, 25),
            text(team)    | size(WIDTH, EQUAL, 30),
            text(country) | size(WIDTH, EQUAL, 6),
        });
    };

    auto header = makeRow("NUM", "COD", "NAME", "TEAM", "NAT") | bold;

    Elements rows;
    rows.push_back(header);
    rows.push_back(separator());
    for (const auto& d : drivers) {
        rows.push_back(makeRow(
            std::to_string(d.number),
            d.code,
            d.firstName + " " + d.lastName,
            d.team,
            d.country
        ));
    }

    auto quitBtn = Button("Quit", screen.ExitLoopClosure());

    auto renderer = Renderer(quitBtn, [&] {
        return vbox({
            text("F1 Live Dashboard") | bold | hcenter,
            separator(),
            vbox(rows) | border,
            separator(),
            quitBtn->Render() | hcenter,
        }) | border;
    });

    screen.Loop(renderer);
}