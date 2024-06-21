//
// Created by Jaime on 6/20/2024.
//

#ifndef EARTHQUAKE_CONSOLENOTIFICATION_H
#define EARTHQUAKE_CONSOLENOTIFICATION_H

#include "EarthquakeNotification.h"
#include <iostream>

class ConsoleNotification : public EarthquakeNotification {
public:
    void notify(const std::string& location, double magnitude, const std::string& time) const override {
        std::cout << "New Earthquake Detected!\n";
        std::cout << "Location: " << location << "\n";
        std::cout << "Magnitude: " << magnitude << "\n";
        std::cout << "Time: " << time << "\n";
    }
};

#endif //EARTHQUAKE_CONSOLENOTIFICATION_H
