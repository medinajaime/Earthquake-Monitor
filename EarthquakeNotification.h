//
// Created by Jaime on 6/20/2024.
//

#ifndef EARTHQUAKE_EARTHQUAKENOTIFICATION_H
#define EARTHQUAKE_EARTHQUAKENOTIFICATION_H

#include <string>

class EarthquakeNotification {
public:
    virtual void notify(const std::string& location, double magnitude, const std::string& time) const = 0;
    virtual ~EarthquakeNotification() = default;
};

#endif //EARTHQUAKE_EARTHQUAKENOTIFICATION_H
