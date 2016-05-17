//
// Created by uilian on 5/15/16.
//

#ifndef FEEDERSCHEDULER_FEEDERMQTTCLIENT_HPP
#define FEEDERSCHEDULER_FEEDERMQTTCLIENT_HPP

#include <memory>
#include <Poco/Util/Timer.h>

#include <IoT/MQTT/MQTTClient.h>

#include "FeederTimerTask.hpp"
#include <set>
#include <Poco/DateTime.h>
#include <Poco/LocalDateTime.h>

class FeederMQTTClient
{
public:
    explicit FeederMQTTClient(Poco::AutoPtr<FeederTimerTask>& task);

    void onMessageArrived(const IoT::MQTT::MessageArrivedEvent& event);
private:
    Poco::Util::Timer timer_;
    Poco::AutoPtr<FeederTimerTask>& task_;

    std::unique_ptr<IoT::MQTT::MQTTClient> client_;

    void onFeedCompleted();

    std::set<Poco::LocalDateTime> dispense_history_;
};


#endif //FEEDERSCHEDULER_FEEDERMQTTCLIENT_HPP
