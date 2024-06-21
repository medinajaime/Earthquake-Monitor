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
#include <ctime>
#include <mutex>


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
        std::string previousLocationAPI1;
        double previousMagnitudeAPI1 = 0.0;
        std::string previousTimeAPI1;

        std::string previousLocationAPI2;
        double previousMagnitudeAPI2 = 0.0;
        std::string previousTimeAPI2;

        bool isUsingAPI1 = true;

        while (running) {
            try {
                std::string currentData = fetcher.fetch();

                if (currentData.find('<') != std::string::npos) {
                    throw std::runtime_error("Received HTML instead of JSON. Check your API key and endpoint URL.");
                }

                if (!currentData.empty()) {
                    auto jsonData = nlohmann::json::parse(currentData);
                    auto earthquakes = jsonData["records"]["Earthquake"];

                    if (!earthquakes.empty()) {
                        auto latestQuake = earthquakes[0];
                        std::string location = latestQuake["EarthquakeInfo"]["Epicenter"]["Location"].get<std::string>();
                        double magnitude = latestQuake["EarthquakeInfo"]["EarthquakeMagnitude"]["MagnitudeValue"].get<double>();
                        std::string timeStr = latestQuake["EarthquakeInfo"]["OriginTime"].get<std::string>();

                        std::tm tm = {};
                        std::istringstream ss(timeStr);
                        ss >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S");
                        if (ss.fail()) {
                            throw std::runtime_error("Failed to parse time string.");
                        }
                        std::time_t time = std::mktime(&tm);

                        std::ostringstream timeConverter;
                        timeConverter << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
                        std::string readableTime = timeConverter.str();

                        if (isUsingAPI1) {
                            if (location != previousLocationAPI1 || magnitude != previousMagnitudeAPI1 || readableTime != previousTimeAPI1) {
                                notifier.notify(location, magnitude, readableTime);
                                previousLocationAPI1 = location;
                                previousMagnitudeAPI1 = magnitude;
                                previousTimeAPI1 = readableTime;
                            }
                        } else {
                            if (location != previousLocationAPI2 || magnitude != previousMagnitudeAPI2 || readableTime != previousTimeAPI2) {
                                notifier.notify(location, magnitude, readableTime);
                                previousLocationAPI2 = location;
                                previousMagnitudeAPI2 = magnitude;
                                previousTimeAPI2 = readableTime;
                            }
                        }

                        isUsingAPI1 = !isUsingAPI1;
                    }
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

#endif // EARTHQUAKE_EARTHQUAKEMONITOR_H
