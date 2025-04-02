/**
 * @file libtestmain.cpp
 * @author Simon Cahill (contact@simonc.eu)
 * @brief Contains the implementation of a basic test main function.
 * @version 0.1
 * @date 2025-03-31
 * 
 * @copyright Copyright (c) 2025 Simon Cahill and Contributors
 */

///////////////////////
//  SYSTEM INCLUDES  //
///////////////////////
// stl
#include <iostream>

// channel_select
#include <wave8ch/wave8ch.hpp>

int main() {

    const auto channelStates = waveshare::relay_board_8ch::getChannelStates();
    for (const auto& [channel, state] : channelStates) {
        std::cout << "Channel " << static_cast<int>(channel) << ": " << (state ? "ON" : "OFF") << std::endl
                  << "Toggling...." << std::endl;

        // Toggle the channel
        waveshare::relay_board_8ch::setChannelState(channel, !state);
    }

    return 0;
}