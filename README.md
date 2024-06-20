

# Earthquake Monitoring System

This project is an earthquake monitoring system designed to fetch, process, and notify users about earthquake events, focusing on the Taiwan region. It integrates with the Taiwan Central Weather Administration (CWA) API to retrieve real-time earthquake data and provides notifications through console output and log files. Additionally, it includes a web interface using the Crow library to control and monitor earthquake data remotely.

## Features

- Fetch earthquake data from the CWA API and filter for events in Taiwan.
- Notify users about detected earthquakes through console output and log files (`earthquakes.log`).
- Web interface for monitoring earthquake data and controlling monitoring functionality remotely.
- Modular design with object-oriented programming (OOP) principles for extensibility and maintainability.

## Project Structure

The project is structured as follows:

- **`main.cpp`**: Main program file that sets up the Crow server, routes HTTP requests, and integrates components.
- **`CombinedNotification.h`**: Header file for the `CombinedNotification` class, which combines console and file notifications.
- **`ConsoleNotification.h`**: Header file for the `ConsoleNotification` class, which handles console notifications.
- **`FileNotification.h`**: Header file for the `FileNotification` class, which handles file-based notifications.
- **`EarthquakeFetcher.h`**: Header file for the `EarthquakeFetcher` class, which fetches earthquake data from the CWA API.
- **`EarthquakeMonitor.h`**: Header file for the `EarthquakeMonitor` class, which monitors earthquake events and notifies using notifications.
- **`crow.h`**: Crow library header for handling web requests and setting up the web interface.

## Setup Instructions

1. Clone the repository to your local machine.
2. Make sure you have the required dependencies installed (Crow library, C++ compiler, etc.).
3. Update the API key in `main.cpp` with your CWA API key.
4. Build the project using CMake or your preferred build system.
5. Run the executable generated after building the project.

## Usage

- Start the monitoring system by sending a POST request to `/start-monitoring`.
- Stop the monitoring system by sending a POST request to `/stop-monitoring`.
- Access earthquake logs by sending a GET request to `/earthquakes`.

## Contributing

Contributions to improve and extend the functionality of this project are welcome. Fork the repository, make your changes, and submit a pull request.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

