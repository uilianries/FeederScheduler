//
// Created by uilian on 5/15/16.
//

#ifndef FEEDERSCHEDULER_FEEDERTIMERTASK_HPP
#define FEEDERSCHEDULER_FEEDERTIMERTASK_HPP

#include <Poco/Util/TimerTask.h>
#include <functional>
#include "IoT/MQTT/MQTTClient.h"

class FeederTimerTask : public Poco::Util::TimerTask
{
public:
    using onFeed = std::function<void()>;

    explicit FeederTimerTask(unsigned gpio);

    void run() override;

    void delegateOnFeed(onFeed callback);

private:
    unsigned gpio_;
    onFeed onFeed_;
};


#endif //FEEDERSCHEDULER_FEEDERTIMERTASK_HPP
