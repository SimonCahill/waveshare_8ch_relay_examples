/********************************************
            Channel Select in C++
 *                                          *
 *      Copyright © Simon Cahill and        *
 *               contributors               *
 ********************************************/

#ifndef GPIOD_API
#define GPIOD_API
#endif

//////////////////////////////////
//        System Includes       //
//////////////////////////////////
// STL
#include <algorithm>
#include <array>
#include <iostream>
#include <fstream>
#include <map>
#include <optional>
#include <regex>
#include <string>

// libc
#include <getopt.h>
#include <stdint.h>
#include <sys/stat.h>
#include <unistd.h>

// fmt
#include <fmt/format.h>

// gpiod
#include <gpiod.h>
#include <gpiod.hpp>

//////////////////////////////////
//        Local  Includes       //
//////////////////////////////////
#include "channel_select.hpp"

//////////////////////////////////
//            Usings            //
//////////////////////////////////
using std::array;
using std::cerr;
using std::cout;
using std::endl;
using std::map;
using std::optional;
using std::regex;
using std::regex_search;
using std::string;
using std::string_view;
using std::tolower;
using std::transform;

enum class StateModifier { ENABLE, DISABLE, READ };

static bool                                     g_readAll{false};
static map<int32_t, optional<StateModifier>>    g_channelOptions{};
static StateModifier                            g_stateModifier{StateModifier::READ};

//////////////////////////////////
//       STATIC CONSTEXPR       //
//////////////////////////////////

/**
 * @brief A simple array representing a map to the channels on the relay board, corresponding to
 * the GPIO pins.
 * 
 * E.g.: CHANNELS[0] = channel 1 = GPIO5
 */
static constexpr array<uint32_t, 8> CHANNELS {
    5, 6, 13, 16, 19, 20, 21, 26
};

//////////////////////////////////
//     FUNCTION PROTOTYPES      //
//////////////////////////////////
using optsm_t = optional<StateModifier>;

optsm_t     stateModifierFromString(const string& optArg); //!< Converts an optarg value to a boolean
int32_t     parseArgs(int32_t argc, char** argv); //!< Parses arguments passed to the application

bool        getChannelState(const int32_t channelId); //!< Gets the state of a given channel
void        listChannels(); //!< Lists all channels available with their state.
void        setChannel(const int32_t channelId, const StateModifier newState); //!< Sets the state of a given channel

void        printHelp(); //!< Prints the help text for the application
void        printVersion(); //!< Prints the version information for the application

int32_t main(int32_t argc, char** argv) {
    if (const auto retVal = parseArgs(argc, argv); retVal > 0) {
        return retVal - 1; // Return an error code or null, depending on the arguments
    }

    if (g_readAll) {
        listChannels();
        return 0;
    }

    for (const auto& [channel, state] : g_channelOptions) {
        if (state) {
            switch (*state) {
                case StateModifier::DISABLE:
                    setChannel(channel, *state);
                    break;
                case StateModifier::ENABLE:
                    setChannel(channel, *state);
                    break;
                default:
                    fmt::println("Channel {0:d} (GPIO pin {1:d}) set to {2:s}", channel + 1, CHANNELS[channel], getChannelState(CHANNELS[channel]) ? "OFF" : "ON");
                    break;
            }
        } else if (g_stateModifier == StateModifier::READ) {
            fmt::println("Channel {0:d} (GPIO pin {1:d}) set to {2:s}", channel + 1, CHANNELS[channel], getChannelState(CHANNELS[channel]) ? "OFF" : "ON");
            continue;
        } else {
            setChannel(channel, g_stateModifier);
        }
    }

    return 0;
}

/**
 * @brief Parses the arguments/options passed to this application using getopt.
 * 
 * @param argc The amount of arguments passed
 * @param argv An array containing the arguments/options
 * 
 * @return int32_t 0 if application shall continue, otherwise app return code + 1.
 */
int32_t parseArgs(int32_t argc, char** argv) {
    constexpr option APP_OPTIONS[] = {
        { "help",       no_argument,    nullptr,    'h' },
        { "version",    no_argument,    nullptr,    'v' },

        // channels
        { "channel1",   no_argument,    nullptr,    '1' },
        { "channel2",   no_argument,    nullptr,    '2' },
        { "channel3",   no_argument,    nullptr,    '3' },
        { "channel4",   no_argument,    nullptr,    '4' },
        { "channel5",   no_argument,    nullptr,    '5' },
        { "channel6",   no_argument,    nullptr,    '6' },
        { "channel7",   no_argument,    nullptr,    '7' },
        { "channel8",   no_argument,    nullptr,    '8' },
        { "all",        no_argument,    nullptr,    'a' },

        // modifiers
        { "enable",     no_argument,    nullptr,    'e' },
        { "disable",    no_argument,    nullptr,    'd' },
        { "read-state", no_argument,    nullptr,    'r' },

        // other operations
        { "list-all",   no_argument,    nullptr,    'L' }
    };
    constexpr const char* APP_SHORTOPTS = R"(hv12345678edrLa)";

    int32_t optChar = -1;

    while ((optChar = getopt_long(argc, argv, APP_SHORTOPTS, APP_OPTIONS, nullptr)) != -1) {
        if (optChar >= 49 && optChar <= 56) {
            // Handle channel inputs
            g_channelOptions.try_emplace(optChar - 49, std::nullopt);
        } else {
            switch (optChar) {
                case 'h':
                    printHelp();
                    return 1;
                case 'v':
                    printVersion();
                    return 1;
                case 'e':
                    g_stateModifier = StateModifier::ENABLE;
                    break;
                case 'd':
                    g_stateModifier = StateModifier::DISABLE;
                    break;
                case 'r':
                    g_stateModifier = StateModifier::READ;
                    break;
                case 'L':
                    g_readAll = true;
                    break;
                case 'a':
                    for (int32_t i = 0; i < 8; i++) {
                        g_channelOptions.try_emplace(i, std::nullopt);
                    }
                    break;
            }
        }
    }

    return 0;
}

bool getChannelState(const int32_t channel) {
    auto gpioChip = gpiod::chip(string{GPIO_CHIP});
    auto lineSettings = gpiod::line_settings{};
    auto line = gpioChip.prepare_request().add_line_settings(gpioChip.get_line_offset_from_name(fmt::format("GPIO{0:d}", channel)), lineSettings).do_request();

    return static_cast<bool>(line.get_value(line.offsets()[0]));
}

optsm_t stateModifierFromString(const string& optArg) {
    constexpr const char* ENABLE_OPT = "e";
    constexpr const char* DISABLE_OPT = "d";
    constexpr const char* READ_OPT = "r";

    if (optArg.length() == 0) { return std::nullopt; }

    if (optArg == ENABLE_OPT) {
        return StateModifier::ENABLE;
    } else if (optArg == DISABLE_OPT) {
        return StateModifier::DISABLE;
    } else if (optArg == READ_OPT) {
        return StateModifier::READ;
    }
    
    return std::nullopt;
}

void listChannels() {
    size_t channelCounter = 1;

    for (const auto channel : CHANNELS) {
        fmt::println("Channel {0:d} (GPIO pin {1:d}) set to {2:s}", channelCounter++, channel, getChannelState(channel) ? "OFF" : "ON");
    }
}

void printHelp() {
    fmt::print(R"(
{0:s} v{1:s} - A simple application for controlling GPIO pins on modern Linux OSs on RasPi

Usage:
    {0:s} -h
    {0:s} -e -123       # enable channels 1, 2, and 3
    {0:s} -d -528       # disable channels 5, 2, and 8 and read the state of channel 7
    {0:s} -L            # read the states of all channels

Troubleshooting:
    Permission denied? Is your user in the gpio group? # usermod -aG gpio <myuser>
    Library not found? Try installing lgpiod

Options:
    Channel selection:
     --channel1,    -1  Channel 1
     --channel2,    -2  Look, it's the same up until -8
     ...
     --channel8,    -8  I'm sure it's self-explanatory at this point
     --all,         -a  All channels

    Channel options:
     --enable,      -e  Enable channel(s)
     --disable,     -d  Disable channel(s)
     --read,        -r  Read the channel state

    General options:
     --list-all,    -L  List all channels and their current state

     --help,        -h  Displays this text and exits
     --version,     -v  Displays the version information and exits
)", APP_NAME, APP_VERS);

}

void printVersion() {
    fmt::print(R"({0:s} v{1:s} - A simple application for controlling GPIO pins on modern Linux OSs on RasPi)", APP_NAME, APP_VERS);
}

void setChannel(const int32_t channel, const StateModifier newState) {
    const auto gpioLineName = fmt::format("GPIO{0:d}", CHANNELS[channel]);

    auto gpioChip = gpiod::chip(string{GPIO_CHIP});
    auto lineSettings = gpiod::line_settings{};
    lineSettings.set_direction(gpiod::line::direction::OUTPUT);
    auto line = gpioChip.prepare_request().add_line_settings(gpioChip.get_line_offset_from_name(gpioLineName), lineSettings).do_request();

    fmt::println("Attempting to set GPIO{0:d} {1:s}", CHANNELS[channel], newState == StateModifier::DISABLE ? "ON" : "OFF");
    line.set_value(line.offsets()[0], newState == StateModifier::DISABLE ? gpiod::line::value::INACTIVE : gpiod::line::value::ACTIVE);
}
