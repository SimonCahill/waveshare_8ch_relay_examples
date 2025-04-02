# Waveshare 8-Channel Relay Examples in C#

This repository contains example code for controlling the Waveshare 8-Channel Relay module using C#. The goal of this project is to provide a simple and clear starting point for developers who want to integrate the relay module into their .NET applications.

## Goals

- Demonstrate how to interface with the Waveshare 8-Channel Relay module using C#.
- Provide reusable and well-documented code for relay control.
- Help developers understand the basics of GPIO communication in .NET.

## Features

- Turn individual relays on or off.
- Control multiple relays simultaneously.
- Example code for common use cases.

## Prerequisites

- A Waveshare 8-Channel Relay module.
- A device with GPIO support (e.g., Raspberry Pi).
- .NET 8.0 or later installed on your system.

## Getting Started

These steps must be performed on your raspberry Pi.

1. Clone this repository: (optional)
    ```bash
    git clone https://github.com/simoncahill/waveshare_8ch_relay_examples.git
    cd waveshare_8ch_relay_examples/cpp
    ```

2. Ensure you have the tools required for building C++ libraries, or download a precompiled version from GitHub.

3. Compile the library for your Raspberry Pi model:
    ```bash
    mkdir build && cd build
    cmake .. -Dchannelselect_BUILD_LIBRARY=ON -Dchannelselect_RASPI5=ON
    make
    ```

4. Install the library to your Raspberry Pi:
    ```bash
    sudo make install
    # or extract the library and copy it to your binary's install location
    ```

5. Download the NuGet package
    ```bash
    dotnet add package procsys.waveshare8ch
    ```

## Basic Usage

The example code demonstrates how to initialize the relay module and control individual relays. Below is a brief overview:

- **Initialize the Relay Module**: Use the provided `RelayController` class to set up communication with the relay module.
- **Control Relays**: Call methods like `TurnOnRelay(int relayNumber)` or `TurnOffRelay(int relayNumber)` to control specific relays.

### Example Code Snippet

```csharp
using ChannelSelect;

class Program {

    static void Main() {

        Console.WriteLine($"Channel states: { ChannelSelect.GetChannelStates() }");

    }

}
```

## Tips

- Ensure the GPIO pins are correctly configured and match the relay module's requirements.
- Run the application with appropriate permissions to access GPIO (e.g., `sudo` on Linux).
- Refer to the Waveshare 8-Channel Relay documentation for hardware setup details.

## Contributing

Contributions are welcome! Feel free to open issues or submit pull requests to improve the examples.

## License

This project is licensed under the MIT License. See the [LICENSE](../LICENSE) file for details.
