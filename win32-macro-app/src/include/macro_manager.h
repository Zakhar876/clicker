#ifndef MACRO_MANAGER_H
#define MACRO_MANAGER_H

#include <string>
#include <vector>

class MacroManager {
public:
    void loadScript(const std::string& filePath);
    void runScript(const std::string& scriptName);
    void logAction(const std::string& action);

private:
    std::vector<std::string> scripts;
};

#endif // MACRO_MANAGER_H