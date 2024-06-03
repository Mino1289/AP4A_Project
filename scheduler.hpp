#ifndef __SCHEDULER_HPP__
#define __SCHEDULER_HPP__

#include <iostream>
#include <vector>
#include <unistd.h>

#include "sensor.hpp"

using namespace std;

class Scheduler {
    private:
        // en secondes
        unsigned interval;
        vector<Sensor<float>> sensorsFloat;
        vector<Sensor<int>> sensorsInt;
        vector<Sensor<bool>> sensorsBool;

    public:
        Scheduler();
        Scheduler(const unsigned&, const vector<Sensor<float>>&, const vector<Sensor<int>>&, const vector<Sensor<bool>>&);
        Scheduler(const Scheduler&);
        virtual ~Scheduler();

        unsigned getInterval() const { return this->interval; }

        vector<float> getFloatVals();
        vector<int> getIntVals();
        vector<bool> getBoolVals();
        
        vector<std::string> getNames();
};


#endif // __SCHEDULER_HPP__