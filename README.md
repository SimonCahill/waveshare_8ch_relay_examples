# waveshare_8ch_relay_examples
This repository contains example code useful when using the WaveShare 8-channel relay module for the RaspberryPi.
The example code provided by WaveShare is mixed up and doesn't work correctly.

# C++ Application

Included with this repository is a C++ application, which is now the recommended use of this repository!  
The C++ application uses libgpiod, which is bundled in this repository. Regardless of whether or not libgpiod is found on your system,  
the Makefile generator will always download the correct version of the library and link against it.

## Building the Application

Unlike in previous versions, the application has been refactored to use CMake as its Makefile generator and build system, instead of using raw compiler commands.  
Building the application is very easy nonetheless.

```sh
# Ensure you're in the `cpp` directory!

# Create build directory
mkdir -p build && cd build

# It doesn't really matter which platform you're on; because of the fallback logic, this should work on both RPi5 and older models

cmake .. [-Dchannelselect_RASPI5] # Add the value in brackets if you're planning on running on RPi5.

make -j$(($(nproc)-1)) # Build with nproc - 1
```

## Usage

Using the app is fairly simple, and it provides a simple help text to get you started.  
Some examples are included below:

```
waveshare_channel_select v1.1.0 - A simple application for controlling GPIO pins on modern Linux OSs on RasPi

Usage:
    waveshare_channel_select -h
    waveshare_channel_select -e -123       # enable channels 1, 2, and 3
    waveshare_channel_select -d -528       # disable channels 5, 2, and 8 and read the state of channel 7
    waveshare_channel_select -L            # read the states of all channels

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
```

# Bash Script

Contained within this repository is a Bash script, which handles setting the GPIO pins, respective to the selected channel.
There are a total of eight relays on the board, which are designated as "channels".

The script takes two arguments:

 - The channel number (1-8)
 - The state (0/1, on/off, true/false)
 - --help

The channel may be prefixed with "ch" or "CH", or may simply be passed to the script.
The order in which the arguments are passed does not affect the execution of the script.

If the --help|-h arg is passed, the script will print the help text and exit.

## Example usage

```bash
# Enable channel 1
./channel_select ch1 on

# Enable channel 3
./channel_select on 3

# Disable channel 8
./channel_select false CH8

# Print help menu
./channel_select --help
```