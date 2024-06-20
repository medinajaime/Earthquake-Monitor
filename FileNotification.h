//
// Created by Jaime on 6/20/2024.
//

#ifndef EARTHQUAKE_FILENOTIFICATION_H
#define EARTHQUAKE_FILENOTIFICATION_H

#include "EarthquakeNotification.h"
#include <fstream>

class FileNotification : public EarthquakeNotification {
public:
    void notify(const std::string& location, double magnitude, long time) const override {
        std::ofstream file("earthquakes.log", std::ios::app);
        if (file.is_open()) {
            file << "New Earthquake Detected!\n";
            file << "Location: " << location << "\n";
            file << "Magnitude: " << magnitude << "\n";
            file << "Time: " << time << "\n";
            file.close();
        }
    }
};


#endif //EARTHQUAKE_FILENOTIFICATION_H
