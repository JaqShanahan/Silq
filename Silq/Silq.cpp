#include <iostream>
#include <string>
#include <cstdlib>
#include <direct.h>
#include <Windows.h>
#include <Lmcons.h>
#include <vector>
#include <map>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <conio.h> 

#define GetCurrentDir _getcwd

std::vector<std::string> split(const std::string& str, char delimiter) {
    std::stringstream ss(str);
    std::string part;
    std::vector<std::string> parts;
    while (std::getline(ss, part, delimiter)) {
        parts.push_back(part);
    }
    return parts;
}

std::string trim(const std::string& s) {
    size_t start = s.find_first_not_of(" \t\r\n");
    size_t end = s.find_last_not_of(" \t\r\n");
    return (start == std::string::npos) ? "" : s.substr(start, end - start + 1);
}

std::string shortenPath(const std::string& fullPath, int depth = 3) {
    std::vector<std::string> parts = split(fullPath, '\\');
    std::string result = "...";
    size_t start = (parts.size() > depth) ? parts.size() - depth : 0;
    for (size_t i = start; i < parts.size(); ++i) {
        result += "\\" + parts[i];
    }
    return result;
}

std::string getUsername() {
    char username[UNLEN + 1];
    DWORD len = UNLEN + 1;
    return GetUserNameA(username, &len) ? username : "Unknown";
}

std::string getHostname() {
    char hostname[MAX_COMPUTERNAME_LENGTH + 1];
    DWORD len = MAX_COMPUTERNAME_LENGTH + 1;
    return GetComputerNameA(hostname, &len) ? hostname : "Unknown";
}

void setColor(int textColor, int bgColor = 0) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, (WORD)((bgColor << 4) | textColor));
}

void runScript(const std::string& filename, std::vector<std::string>& history,
    std::map<std::string, std::string>& aliases);

std::string getCommandWithSuggestion(const std::vector<std::string>& history) {
    std::string input;
    char ch;

    while (true) {
        ch = _getch();
        if (ch == '\r') { // Enter
            std::cout << std::endl;
            break;
        }
        else if (ch == '\b') { // Backspace
            if (!input.empty()) {
                input.pop_back();
                std::cout << "\b \b";
            }
        }
        else if (ch == '\t') { // Tab (simplified tab complete with basic suggestions)
            for (auto it = history.rbegin(); it != history.rend(); ++it) {
                if (it->find(input) == 0 && *it != input) {
                    std::string rest = it->substr(input.size());
                    std::cout << rest;
                    input = *it;
                    break;
                }
            }
        }
        else {
            input += ch;
            std::cout << ch;
        }
    }

    return input;
}

int main() {
    _chdir("C:/Windows/System32");

    char buffer[FILENAME_MAX];
    if (!GetCurrentDir(buffer, FILENAME_MAX)) {
        std::cerr << "Error: Unable to get current working directory.\n";
        return 1;
    }

    std::string currentPath = buffer;
    std::string username = getUsername();
    std::string hostname = getHostname();
    std::vector<std::string> history;
    std::map<std::string, std::string> aliases = {
        {"ll", "dir /w"},
        {"..", "cd .."}
    };

    std::cout << "Custom Windows Terminal [Enhanced Mode] \n";
    std::cout << "(c) Jaq Shanahan. Because Microsoft Sucks.\n";

    while (true) {
        std::string shortPath = shortenPath(currentPath);

        setColor(10); std::cout << "\n" << username << "@" << hostname;
        setColor(15); std::cout << ": ";
        setColor(9); std::cout << shortPath;
        setColor(15); std::cout << "$ ";

        std::string command = getCommandWithSuggestion(history);
        command = trim(command);
        if (command.empty()) continue;

        history.push_back(command);

        // Alias replacement
        if (aliases.count(command)) {
            command = aliases[command];
        }

        // Exit
        if (command == "exit") {
            std::cout << "Exiting...\n";
            break;
        }

        // Help
        if (command == "help") {
            std::cout << "Built-in commands:\n";
            std::cout << "  cd <path>       Change directory\n";
            std::cout << "  cls / clear     Clear screen\n";
            std::cout << "  history         Show previous commands\n";
            std::cout << "  run <file.txt>  Run commands from file\n";
            std::cout << "  about           Displays about info\n";
            std::cout << "  exit            Quit the shell\n";
            continue;
        }

        // Clear
        if (command == "cls" || command == "clear") {
            system("cls");
            continue;
        }

        // About
        if (command == "about") {
            std::string about_string = "By Jaq Shanahan\nv1.0.0\n";
            for (int i = 0; i < about_string.length(); i++) {
                std::cout << about_string[i];
                Sleep(100); // Delay in milliseconds (adjust as needed)
            }
            continue;
        }

        // History
        if (command == "history") {
            for (size_t i = 0; i < history.size(); ++i)
                std::cout << i + 1 << ": " << history[i] << "\n";
            continue;
        }

        // Scripting
        if (command.substr(0, 4) == "run ") {
            std::string filename = trim(command.substr(4));
            runScript(filename, history, aliases);
            continue;
        }

        // Change dir
        if (command.substr(0, 3) == "cd ") {
            std::string newPath = trim(command.substr(3));
            std::replace(newPath.begin(), newPath.end(), '/', '\\');
            if (_chdir(newPath.c_str()) != 0) {
                std::cerr << "Error: Could not change directory to '" << newPath << "'\n";
            }
            else if (GetCurrentDir(buffer, FILENAME_MAX)) {
                currentPath = buffer;
            }
            continue;
        }

        // Run command with timer
        DWORD start = GetTickCount();
        int result = system(command.c_str());
        DWORD elapsed = GetTickCount() - start;

        std::cout << "Exit code: " << result << ", Time: " << elapsed << "ms\n";

        if (GetCurrentDir(buffer, FILENAME_MAX)) {
            currentPath = buffer;
        }
    }

    return 0;
}

// Script runner
void runScript(const std::string& filename, std::vector<std::string>& history,
    std::map<std::string, std::string>& aliases) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open script file '" << filename << "'\n";
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        line = trim(line);
        if (line.empty()) continue;

        std::cout << "[SCRIPT] $ " << line << "\n";
        history.push_back(line);

        if (aliases.count(line)) {
            line = aliases[line];
        }

        if (line.substr(0, 3) == "cd ") {
            std::string path = trim(line.substr(3));
            std::replace(path.begin(), path.end(), '/', '\\');
            _chdir(path.c_str());
        }
        else {
            system(line.c_str());
        }
    }
}
