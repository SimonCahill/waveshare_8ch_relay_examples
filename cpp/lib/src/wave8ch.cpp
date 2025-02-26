/**
 * @file wave8ch.cpp
 * @author Simon Cahill (s.cahill@procyon-systems.de)
 * @brief Contains the implementation of the wave8ch library.
 * @version 0.1
 * @date 2025-02-26
 * 
 * @copyright Copyright (c) 2025 Procyon Systems
 */

//////////////////////////////////
//        System Includes       //
//////////////////////////////////
// stl
#include <array>
#include <cstdint>
#include <filesystem>
#include <string>
#include <unordered_map>
#include <vector>

// fmt
#include <fmt/format.h>

// gpiod
#include <gpiod.h>
#include <gpiod.hpp>

//////////////////////////////////
//        Local  Includes       //
//////////////////////////////////
#include "wave8ch/wave8ch.hpp"

namespace waveshare::relay_board_8ch {

    namespace fs = std::filesystem;

    using std::array;
    using std::unordered_map;
    using std::string;
    using std::vector;

    static inline bool getChannelState(const int32_t channel, const fs::path& gpioDevice = GPIO_CHIP) {
        try {
            auto gpioChip = gpiod::chip(gpioDevice);
            auto lineSettings = gpiod::line_settings{};
            auto line = gpioChip.prepare_request().add_line_settings(gpioChip.get_line_offset_from_name(fmt::format("GPIO{0:d}", channel)), lineSettings).do_request();
    
            const auto state = static_cast<bool>(line.get_value(line.offsets()[0]));
    
            return state;
        } catch (const std::invalid_argument&) {
            return getChannelState(channel, FALLBACK_GPIO_CHIP);
        }
    }

    static inline void setChannel(const int32_t channel, const bool newState, const fs::path& gpioDevice = GPIO_CHIP) {
        const auto gpioLineName = fmt::format("GPIO{0:d}", GPIO_PINS[channel]);
    
        try {
            auto gpioChip = gpiod::chip(gpioDevice);
            auto lineSettings = gpiod::line_settings{};
            lineSettings.set_direction(gpiod::line::direction::OUTPUT);
            auto line = gpioChip.prepare_request().add_line_settings(gpioChip.get_line_offset_from_name(gpioLineName), lineSettings).do_request();
            
            line.set_value(line.offsets()[0], newState == false ? gpiod::line::value::INACTIVE : gpiod::line::value::ACTIVE);
        } catch (const std::invalid_argument&) {
            setChannel(channel, newState, FALLBACK_GPIO_CHIP);
        }
    }

    /**
     * @brief Gets a map of all the channels and their current state.
     * 
     * @return unordered_map<Channel, bool> A map of the channels and their states.
     */
    unordered_map<Channel, bool> getChannelStates() {
        unordered_map<Channel, bool> channelStates{};

        for (const auto channel : GPIO_PINS) {
            channelStates[static_cast<Channel>(channel + 1)] = getChannelState(channel);
        }

        return channelStates;
    }

    /**
     * @brief Gets the state of a specific channel.
     * 
     * @param channel The channel to get the state of.
     * 
     * @return bool The state of the channel.
     */
    bool getChannelState(Channel channel) { return getChannelState(GPIO_PINS[static_cast<int32_t>(channel) - 1]); }

    /**
     * @brief Sets the state of a specific channel.
     * 
     * @param channel The channel to set the state of.
     * @param newState The new state of the channel.
     */
    void setChannelState(Channel channel, bool newState) { setChannel(GPIO_PINS[static_cast<int32_t>(channel) - 1], newState); }

} // namespace waveshare::relay_board_8ch