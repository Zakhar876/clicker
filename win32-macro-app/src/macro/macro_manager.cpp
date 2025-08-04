
#include "../include/macro_manager.h"
#include <iostream>
#include <fstream>

void MacroManager::loadScript(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open script file: " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        scripts.push_back(line);
    }
    file.close();
}

void MacroManager::runScript(const std::string& scriptName) {
    for (const auto& script : scripts) {
        // Here you would interpret and execute the script commands
        logAction("Executing: " + script);
    }
}

void MacroManager::logAction(const std::string& action) {
    std::cout << action << std::endl;
}