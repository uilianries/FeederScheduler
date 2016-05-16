//
// Created by uilian on 5/15/16.
//

#include <Poco/Logger.h>

#include "FeederTimerTask.hpp"
#include "Feeder.hpp"

FeederTimerTask::FeederTimerTask(unsigned gpio)
: gpio_{gpio}
, onFeed_{nullptr}
{}

void FeederTimerTask::delegateOnFeed(FeederTimerTask::onFeed callback)
{
    onFeed_ = callback;
}

void FeederTimerTask::run()
{
    Poco::Logger::root().information("Dispense Food on aquarium");

    Feeder feeder(gpio_);
    try {
        feeder.dispense();
        if (onFeed_) {
            onFeed_();
        }
    } catch (const std::runtime_error& error) {
        Poco::Logger::root().error(error.what());
    }
}