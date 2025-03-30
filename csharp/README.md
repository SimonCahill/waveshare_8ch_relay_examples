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

1. Clone this repository:
    ```bash
    git clone https://github.com/simoncahill/waveshare_8ch_relay_examples.git
    cd waveshare_8ch_relay_examples/csharp
    ```

2. Open the project in your favorite IDE (e.g., Visual Studio or Visual Studio Code).

3. Build the project:
    ```bash
    dotnet build
    ```

## Basic Usage

The example code demonstrates how to initialize the relay module and control individual relays. Below is a brief overview:

- **Initialize the Relay Module**: Use the provided `RelayController` class to set up communication with the relay module.
- **Control Relays**: Call methods like `TurnOnRelay(int relayNumber)` or `TurnOffRelay(int relayNumber)` to control specific relays.

### Example Code Snippet

```csharp
var relayController = new RelayController();
relayController.Initialize();

// Turn on relay 1
relayController.TurnOnRelay(1);

// Turn off relay 1
relayController.TurnOffRelay(1);

// Turn on all relays
relayController.TurnOnAllRelays();
```

## Tips

- Ensure the GPIO pins are correctly configured and match the relay module's requirements.
- Run the application with appropriate permissions to access GPIO (e.g., `sudo` on Linux).
- Refer to the Waveshare 8-Channel Relay documentation for hardware setup details.

## Contributing

Contributions are welcome! Feel free to open issues or submit pull requests to improve the examples.

## License

This project is licensed under the MIT License. See the [LICENSE](../LICENSE) file for details.
