//
// Created by uilian on 5/15/16.
//

#include "FeederSchedulerApp.hpp"

#include <string>

#include <Poco/AutoPtr.h>
#include <Poco/PatternFormatter.h>
#include <Poco/FormattingChannel.h>

#include "FeederMQTTClient.hpp"
#include "FeederTimerTask.hpp"

int FeederSchedulerApp::main(const Poco::Util::Application::ArgVec& args)
{
    Poco::AutoPtr<Poco::PatternFormatter> patternFormatter(new Poco::PatternFormatter);
    patternFormatter->setProperty("pattern", "%L %Y-%m-%d %H:%M:%S %s: %t");
    Poco::AutoPtr<Poco::FormattingChannel> formarttingChannel(new Poco::FormattingChannel(patternFormatter, logger().getChannel()));

    Poco::Logger::root().setChannel(formarttingChannel);

    poco_assert(!args.empty());
    unsigned gpio = static_cast<unsigned>(std::stoul(args.front()));

    Poco::AutoPtr<Poco::Util::TimerTask> feederTimerTaskPtr(new FeederTimerTask(gpio));

    FeederMQTTClient feederMQTTClient(feederTimerTaskPtr);

    waitForTerminationRequest();

    return Poco::Util::Application::EXIT_OK;
}