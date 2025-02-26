##################################################################
##  This script will dynamically download the latest version of ##
##  CPM from GitHub and will include it in the project.         ##
##                                                              ##
##  Written by Simon Cahill (contact@simonc.eu)                 ##
##  Copyright (c) 2025 Simon Cahill and Contributors            ##
##################################################################

set(channelselect_CPM_DOWNLOAD_DIR "${CMAKE_CURRENT_BINARY_DIR}/cmake/cmake_includes")
file(MAKE_DIRECTORY "${channelselect_CPM_DOWNLOAD_DIR}")

# Download CPM
file(DOWNLOAD
    "https://github.com/cpm-cmake/CPM.cmake/releases/latest/download/CPM.cmake"
    "${channelselect_CPM_DOWNLOAD_DIR}/CPM.cmake"
)

# Include CPM
include("${channelselect_CPM_DOWNLOAD_DIR}/CPM.cmake")

CPMAddPackage(
    NAME nlohmann_json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG develop
)