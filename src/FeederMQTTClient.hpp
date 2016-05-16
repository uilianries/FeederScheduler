//
// Created by uilian on 5/15/16.
//

#ifndef FEEDERSCHEDULER_FEEDERMQTTCLIENT_HPP
#define FEEDERSCHEDULER_FEEDERMQTTCLIENT_HPP

#include <memory>
#include <Poco/Util/Timer.h>

#include <IoT/MQTT/MQTTClient.h>

#include "FeederTimerTask.hpp"

class FeederMQTTClient
{
public:
    explicit FeederMQTTClient(Poco::Util::TimerTask::Ptr& task);

    void onMessageArrived(const IoT::MQTT::MessageArrivedEvent& event);
private:
    Poco::Util::Timer timer_;
    Poco::Util::TimerTask::Ptr& task_;

    std::unique_ptr<IoT::MQTT::MQTTClient> client_;
};


#endif //FEEDERSCHEDULER_FEEDERMQTTCLIENT_HPP
