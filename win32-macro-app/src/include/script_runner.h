#ifndef SCRIPT_RUNNER_H
#define SCRIPT_RUNNER_H

class MacroManager; // Forward declaration
// Include string for std::string usage
#include <string>
class ScriptRunner {
public:
    ScriptRunner(MacroManager& manager);
    void executeScript(const std::string& script);
    void parseCommand(const std::string& command);
private:
    MacroManager& macroManager;
};

#endif // SCRIPT_RUNNER_H