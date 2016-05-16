//
// Created by uilian on 5/15/16.
//

#ifndef FEEDERSCHEDULER_FEEDERSCHEDULERAPP_HPP
#define FEEDERSCHEDULER_FEEDERSCHEDULERAPP_HPP

#include <Poco/Util/ServerApplication.h>

class FeederSchedulerApp : public Poco::Util::ServerApplication
{
private:
    int main(const Poco::Util::Application::ArgVec& args) override;
};


#endif //FEEDERSCHEDULER_FEEDERSCHEDULERAPP_HPP
