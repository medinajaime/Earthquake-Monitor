#include "crow.h"
#include "EarthquakeNotification.h"
#include "CombinedNotification.h" // Include CombinedNotification header
#include "EarthquakeFetcher.h"
#include "EarthquakeMonitor.h"
#include <atomic>

std::atomic<bool> running(false);

int main() {
    crow::SimpleApp app;
    std::string apiKey = "CWA-103C5D0F-4366-4991-AAC8-4975188142C4";
    EarthquakeFetcher fetcher(apiKey);
    CombinedNotification combinedNotifier; // Create CombinedNotification instance
    EarthquakeMonitor monitor(fetcher, combinedNotifier); // Use CombinedNotification in EarthquakeMonitor

    CROW_ROUTE(app, "/start-monitoring").methods("POST"_method)([&]() {
        if (!running) {
            running = true;
            monitor.start();
            return crow::response(200, "Monitoring started");
        }
        return crow::response(200, "Already monitoring");
    });

    CROW_ROUTE(app, "/stop-monitoring").methods("POST"_method)([&]() {
        if (running) {
            running = false;
            monitor.stop();
            return crow::response(200, "Monitoring stopped");
        }
        return crow::response(200, "Not monitoring");
    });

    CROW_ROUTE(app, "/earthquakes").methods("GET"_method)([]() {
        std::ifstream file("earthquakes.log");
        std::string log((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        return crow::response(200, log);
    });

    app.port(8080).multithreaded().run();
    return 0;
}
