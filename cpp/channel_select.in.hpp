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

constexpr const char* APP_NAME = "@PROJECT_NAME@";
constexpr const char* APP_VERS = "@PROJECT_VERSION@";

constexpr const char* GPIO_CHIP = "/dev/@DEFAULT_GPIOCHIP@"; //!< This is the chip required for controlling the relay board
constexpr const char* FALLBACK_GPIO_CHIP = "/dev/@FALLBACK_GPIOCHIP@"; //!< This is the fallback chip required for controlling the relay board on a RaspberrFALLBACK
#endif // CHANNEL_SELECT_HPP