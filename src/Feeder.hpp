//
// Created by uilian on 5/15/16.
//

#ifndef FEEDERSCHEDULER_FEEDER_HPP
#define FEEDERSCHEDULER_FEEDER_HPP

class Feeder {

public:
    explicit Feeder(unsigned gpio);

    void dispense();

private:
    unsigned gpio_;
};


#endif //FEEDERSCHEDULER_FEEDER_HPP
