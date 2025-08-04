#include "../include/script_runner.h"
#include "../include/macro_manager.h"
#include "../include/mouse.h"
#include "../include/keyboard.h"
#include <string>
#include <sstream>
#include <vector>


#include "../include/script_runner.h"
#include "../include/macro_manager.h"
#include "../include/mouse.h"
#include "../include/keyboard.h"
#include <string>
#include <sstream>
#include <vector>

ScriptRunner::ScriptRunner(MacroManager& manager) : macroManager(manager) {}

void ScriptRunner::executeScript(const std::string& script) {
    std::istringstream scriptStream(script);
    std::string command;
    while (std::getline(scriptStream, command)) {
        parseCommand(command);
    }
}

void ScriptRunner::parseCommand(const std::string& command) {
    std::istringstream commandStream(command);
    std::string action;
    commandStream >> action;
    if (action == "moveMouse") {
        std::string sx, sy;
        commandStream >> sx >> sy;
        int x = std::stoi(sx);
        int y = std::stoi(sy);
        moveMouse(x, y);
    } else if (action == "clickMouse") {
        clickMouse();
    } else if (action == "pressKey") {
        std::string skey;
        commandStream >> skey;
        WORD key = static_cast<WORD>(std::stoi(skey));
        pressKey(key);
    } else if (action == "releaseKey") {
        std::string skey;
        commandStream >> skey;
        WORD key = static_cast<WORD>(std::stoi(skey));
        releaseKey(key);
    } else {
        macroManager.logAction("Unknown command: " + command);
    }
}