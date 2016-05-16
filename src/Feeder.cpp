//
// Created by uilian on 5/15/16.
//

#include "Feeder.hpp"
#include <fstream>
#include <sstream>
#include <chrono>
#include <thread>
#include <Poco/Poco.h>
#include <Poco/Logger.h>

Feeder::Feeder(unsigned gpio)
 : gpio_{gpio}
{
    poco_assert(gpio > 0);
}

void Feeder::dispense()
{
    std::ostringstream oss;
    oss << "/sys/class/gpio/gpio" << gpio_ << "/value";

    std::ofstream ofs(oss.str());
    if (!ofs) {
        throw std::runtime_error("Could not open " + oss.str());
    }

    Poco::Logger::root().information("Food dispense started");
    ofs << "0";
    ofs.flush();
    std::this_thread::sleep_for(std::chrono::seconds(2));
    ofs << "1";
    ofs.flush();
    Poco::Logger::root().information("Food dispense finished");
}
