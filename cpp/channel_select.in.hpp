/**
 * @file channel_select.hpp
 * @author Simon Cahill (simon@simonc.eu)
 * @brief Contains useful variables and constants for the application; generated at Makefile generation time.
 * @version 0.1
 * @date 2024-02-26
 * 
 * @copyright Copyright (c) 2024 Simon Cahill
 */

#ifndef CHANNEL_SELECT_HPP
#define CHANNEL_SELECT_HPP

#include <array>

#ifndef channelselect_EXPORT_LIB
constexpr const char* APP_NAME = "@PROJECT_NAME@";
constexpr const char* APP_VERS = "@PROJECT_VERSION@";
#endif // !channelselect_EXPORT_LIB

constexpr const char* GPIO_CHIP = "/dev/@DEFAULT_GPIOCHIP@"; //!< This is the chip required for controlling the relay board
constexpr const char* FALLBACK_GPIO_CHIP = "/dev/@FALLBACK_GPIOCHIP@"; //!< This is the fallback chip required for controlling the relay board on a RaspberrFALLBACK

using std::array;

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
#endif // CHANNEL_SELECT_HPP