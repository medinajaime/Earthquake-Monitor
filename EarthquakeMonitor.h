//
// Created by Jaime on 6/20/2024.
//

#ifndef EARTHQUAKE_EARTHQUAKEMONITOR_H
#define EARTHQUAKE_EARTHQUAKEMONITOR_H

#include "EarthquakeNotification.h"
#include "EarthquakeFetcher.h"
#include <atomic>
#include <thread>
#include <chrono>
#include <nlohmann/json.hpp>
#include <iostream>
#include <iomanip>
#include <sstream>

class EarthquakeMonitor {
public:
    EarthquakeMonitor(EarthquakeFetcher& fetcher, const EarthquakeNotification& notifier)
            : fetcher(fetcher), notifier(notifier), running(false) {}

    void start() {
        if (!running) {
            running = true;
            monitorThread = std::thread(&EarthquakeMonitor::monitor, this);
            monitorThread.detach();
        }
    }

    void stop() {
        if (running) {
            running = false;
            if (monitorThread.joinable()) {
                monitorThread.join();
            }
        }
    }

private:
    void monitor() {
        std::string previousData;

        while (running) {
            try {
                std::string currentData = fetcher.fetch();

                if (currentData.find('<') != std::string::npos) {
                    throw std::runtime_error("Received HTML instead of JSON. Check your API key and endpoint URL.");
                }

                if (!currentData.empty() && currentData != previousData) {
                    auto jsonData = nlohmann::json::parse(currentData);
                    auto earthquakes = jsonData["records"]["Earthquake"];

                    for (const auto& quake : earthquakes) {
                        std::string location = quake["EarthquakeInfo"]["Epicenter"]["Location"].get<std::string>();
                        double magnitude = quake["EarthquakeInfo"]["EarthquakeMagnitude"]["MagnitudeValue"].get<double>();
                        std::string timeStr = quake["EarthquakeInfo"]["OriginTime"].get<std::string>();

                        // Convert time string to timestamp
                        std::tm tm = {};
                        std::istringstream ss(timeStr);
                        ss >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S");
                        long time = std::mktime(&tm);

                        //if (location.find("Taiwan") != std::string::npos) {
                            notifier.notify(location, magnitude, time);
                        //}
                    }

                    previousData = currentData;
                }

                std::cout << "Monitoring earthquakes..." << std::endl;
                std::this_thread::sleep_for(std::chrono::minutes(1));
            } catch (const std::exception& e) {
                std::cerr << "Error: " << e.what() << std::endl;
            }
        }
    }

    EarthquakeFetcher& fetcher;
    const EarthquakeNotification& notifier;
    std::atomic<bool> running;
    std::thread monitorThread;
};

#endif //EARTHQUAKE_EARTHQUAKEMONITOR_H
