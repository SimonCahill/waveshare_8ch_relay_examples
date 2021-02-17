# waveshare_8ch_relay_examples
This repository contains example code useful when using the WaveShare 8-channel relay module for the RaspberryPi.
The example code provided by WaveShare is mixed up and doesn't work correctly.

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
