//
// Created by Jaime on 6/20/2024.
//

#ifndef EARTHQUAKE_COMBINEDNOTIFICATION_H
#define EARTHQUAKE_COMBINEDNOTIFICATION_H

#include "ConsoleNotification.h"
#include "FileNotification.h"


#include "ConsoleNotification.h"
#include "FileNotification.h"

class CombinedNotification : public EarthquakeNotification {
private:
    ConsoleNotification consoleNotifier;
    FileNotification fileNotifier;

public:
    void notify(const std::string& location, double magnitude, long time) const override {
        consoleNotifier.notify(location, magnitude, time);
        fileNotifier.notify(location, magnitude, time);
    }
};
#endif //EARTHQUAKE_COMBINEDNOTIFICATION_H
