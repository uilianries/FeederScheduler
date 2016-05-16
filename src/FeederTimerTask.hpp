//
// Created by uilian on 5/15/16.
//

#ifndef FEEDERSCHEDULER_FEEDERTIMERTASK_HPP
#define FEEDERSCHEDULER_FEEDERTIMERTASK_HPP

#include <Poco/Util/TimerTask.h>

class FeederTimerTask : public Poco::Util::TimerTask
{
public:
    explicit FeederTimerTask(unsigned gpio);

    void run() override;

private:
    unsigned gpio_;
};


#endif //FEEDERSCHEDULER_FEEDERTIMERTASK_HPP
