//
// Created by uilian on 5/15/16.
//

#include "FeederMQTTClient.hpp"

#include <chrono>

#include <Poco/Delegate.h>
#include <Poco/JSON/Object.h>
#include <Poco/JSON/Parser.h>
#include <Poco/LocalDateTime.h>
#include <Poco/Format.h>
#include <Poco/NumberFormatter.h>
#include <Poco/Logger.h>
#include <IoT/MQTT/MQTTConnectOptions.h>
#include <IoT/MQTT/MQTTClientFactory.h>


FeederMQTTClient::FeederMQTTClient(Poco::AutoPtr<FeederTimerTask>& task)
: task_{task}
{
    IoT::MQTT::MQTTConnectOptions options;
    options.password = "feederscheduler";
    options.username = "feeder_scheduler";

    IoT::MQTT::MQTTClientFactory::FactoryArguments arguments;
    arguments.options = std::move(options);
    arguments.serverUri = "m11.cloudmqtt.com:15347";
    arguments.clientId = "FeederSchedulerClient";

    task_->delegateOnFeed(std::bind(&FeederMQTTClient::onFeedCompleted, this));

    client_ = IoT::MQTT::MQTTClientFactory::CreateMQTTClient<IoT::MQTT::MQTTClientFactory::ClientType::Paho>(arguments);

    Poco::Logger::root().information("Subscribe on broker");

    client_->subscribe("smartaquarium/actuator/feeder/config", IoT::MQTT::QoS::AT_LEAST_ONCE);

    Poco::Logger::root().information("Delegate arrived message");

    client_->messageArrived += Poco::delegate(this, &FeederMQTTClient::onMessageArrived);
}

void FeederMQTTClient::onMessageArrived(const IoT::MQTT::MessageArrivedEvent& event)
{
    Poco::JSON::Parser jsonParser;

    auto parsedResult = jsonParser.parse(event.message.payload);
    auto extractedObj = parsedResult.extract<Poco::JSON::Object::Ptr>();

    auto interval = extractedObj->get("interval").convert<unsigned>();
    auto time_trigger = extractedObj->get("hour").convert<unsigned>();

    Poco::Logger::root().information("Received message from broker - Payload: " + event.message.payload);

    auto parsedInterval = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::hours(interval)).count();

    const Poco::LocalDateTime now;
    auto dispense_day = now.day();

    Poco::LocalDateTime localDateTime(now.year(), now.month(), dispense_day, time_trigger);

    if (!dispense_history_.empty()) {
        const auto &last_dispense = *dispense_history_.rbegin();
        if (last_dispense.day() == now.day() && time_trigger <= static_cast<unsigned>(now.hour())) {
            localDateTime += Poco::Timespan(0, interval, 0, 0, 0);
        }
    }

    std::string formattedString;
    Poco::format(formattedString, "Food dispense scheduled to: %d/%s/%s - %s:%s:%s",
                 localDateTime.year(), Poco::NumberFormatter::format0(localDateTime.month(), 2),
                 Poco::NumberFormatter::format0(localDateTime.day(), 2),
                 Poco::NumberFormatter::format0(localDateTime.hour(), 2),
                 Poco::NumberFormatter::format0(localDateTime.minute(), 2),
                 Poco::NumberFormatter::format0(localDateTime.second(), 2));
    Poco::Logger::root().information(formattedString);

    timer_.cancel(true);
    timer_.schedule(task_, localDateTime.timestamp(), parsedInterval);
}

void FeederMQTTClient::onFeedCompleted()
{
    dispense_history_.emplace();

    Poco::Logger::root().information("Send feeder feedback to broker");
    client_->publish("smartaquarium/actuator/feeder/level", "0", IoT::MQTT::QoS::AT_LEAST_ONCE);
}