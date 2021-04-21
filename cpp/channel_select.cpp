/********************************************
            Channel Select in C++
 *                                          *
 *      Copyright © Simon Cahill and        *
 *               contributors               *
 ********************************************/

//////////////////////////////////
//        System Includes       //
//////////////////////////////////
#include <algorithm>
#include <iostream>
#include <fstream>
#include <regex>
#include <string>

#include <stdint.h>
#include <sys/stat.h>
#include <unistd.h>

//////////////////////////////////
//            Usings            //
//////////////////////////////////
using std::cerr;
using std::cout;
using std::endl;
using std::regex;
using std::regex_search;
using std::string;
using std::tolower;
using std::transform;

//////////////////////////////////
//        Global Variables      //
//////////////////////////////////
static uint32_t g_channel = 0;
static bool g_state = false;

static const uint32_t CHANNELS[8] {
    5, 6, 13, 16, 19, 20, 21, 26
};

template<typename... Args>
string formatString(const string& format, Args... args)  {
    auto stringSize = snprintf(NULL, 0, format.c_str(), args...) + 1; // +1 for \0
    std::unique_ptr<char[]> buffer(new char[stringSize]);

    snprintf(buffer.get(), stringSize, format.c_str(), args...);

    return string(buffer.get(), buffer.get() + stringSize - 1); // std::string handles termination for us.
}

//////////////////////////////////
//      Function Prototypes     //
//////////////////////////////////
bool directoryExists(string dirPath);
bool parseArgs(int32_t argC, char** argV);

void enableGpio();
void setGpio();
void showHelp();

int main(int32_t argC, char** argV) {

    if (argC <= 2) {
        showHelp();
        return -1;
    }

    if (!parseArgs(argC, argV)) return -1;

    return 0;
}

bool directoryExists(string dirPath) {
    struct stat _stat;
    if (stat(dirPath.c_str(), &_stat) == 0 && S_ISDIR(_stat.st_mode)) {
        return true;
    }
    return false;
}

bool parseArgs(int32_t argC, char** argV) {
    const static regex CHANNEL_PATTERN(R"((ch)?[0-8])");
    const static regex STATE_PATTERN(R"(on|off|true|false)");

    for (int32_t i = 0; i < argC; i++) {
        string arg = argV[i];

        // Convert arg to lower
        transform(arg.begin(), arg.end(), arg.begin(), [&](const auto c) { return tolower(c); });

        if (regex_search(arg, CHANNEL_PATTERN)) {
            g_channel = std::stoi(arg.substr(arg.size() - 1, 1));
        } else if (regex_search(arg, STATE_PATTERN)) {
            g_state = (arg == "on" || arg == "true");
        } else {
            showHelp();
            return false;
        }
    }

    return true;
}

void enableGpio() {
    static const string GPIO_DIR_PATH = "/sys/class/gpio/gpio";

    const auto gpioPath = formatString("%s%d", GPIO_DIR_PATH.c_str(), g_channel);

    if (directoryExists(gpioPath)) return;

    // Make sure Linux exports the pin
    {
        std::ofstream fileStream("/sys/class/gpio/export", std::ios::trunc);
        fileStream << g_channel << endl;
    }

    // Set the GPIO direction
    {
        std::ofstream fileStream(formatString("%s/direction", gpioPath.c_str()), std::ios::trunc);
        fileStream << "out" << endl;
    }
}

void setGpio() {
    static const string GPIO_DIR_PATH = "/sys/class/gpio/gpio";

    const auto gpioPath = formatString("%s%d/value", GPIO_DIR_PATH.c_str(), g_channel);

    std::ofstream fileStream(gpioPath, std::ios::trunc);
    fileStream << static_cast<int32_t>(g_state) << endl;
}

void showHelp() {
    cout << R"(
Usage:
    channel_select [ch]0-8 on/off/true/false
    channel_select --help
    )" << endl;
}
