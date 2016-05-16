//
// Created by uilian on 5/15/16.
//

#include <Poco/Logger.h>

#include "FeederTimerTask.hpp"
#include "Feeder.hpp"

FeederTimerTask::FeederTimerTask(unsigned gpio)
: gpio_{gpio}
{}

void FeederTimerTask::run()
{
    Poco::Logger::root().information("Dispense Food on aquarium");

    Feeder feeder(gpio_);
    try {
        feeder.dispense();
    } catch (const std::runtime_error& error) {
        Poco::Logger::root().error(error.what());
    }
}