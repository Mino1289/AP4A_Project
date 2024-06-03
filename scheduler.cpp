#include "scheduler.hpp"

Scheduler::Scheduler() {
    this->interval = 0;
    this->sensorsFloat = vector<Sensor<float>>();
    this->sensorsInt = vector<Sensor<int>>();
    this->sensorsBool = vector<Sensor<bool>>();
}

Scheduler::Scheduler(const unsigned& interval, const vector<Sensor<float>>& sensorsF, const vector<Sensor<int>>& sensorsI, const vector<Sensor<bool>>& sensorsB) {
    this->interval = interval;
    this->sensorsFloat = sensorsF;
    this->sensorsInt = sensorsI;
    this->sensorsBool = sensorsB;
}

Scheduler::Scheduler(const Scheduler& scheduler) {
    this->interval = scheduler.interval;
    this->sensorsFloat = scheduler.sensorsFloat;
    this->sensorsInt = scheduler.sensorsInt;
    this->sensorsBool = scheduler.sensorsBool;
}

Scheduler::~Scheduler() {}

/**
 * @brief Récupère les valeurs des capteurs de type float
 * 
 * @return vector<float> 
 */
vector<float> Scheduler::getFloatVals() {
    vector<float> vals = vector<float>();
    for (auto& sensor : this->sensorsFloat) {
        vals.push_back(sensor.getVal());
    }
    return vals;
}

/**
 * @brief Récupère les valeurs des capteurs de type int
 * 
 * @return vector<int> 
 */
vector<int> Scheduler::getIntVals() {
    vector<int> vals = vector<int>();
    for (auto& sensor : this->sensorsInt) {
        vals.push_back(sensor.getVal());
    }
    return vals;
}

/**
 * @brief Réupère les valeurs des capteurs de type booléen
 * 
 * @return vector<bool> 
 */
vector<bool> Scheduler::getBoolVals() {
    vector<bool> vals = vector<bool>();
    for (auto& sensor : this->sensorsBool) {
        vals.push_back(sensor.getVal());
    }
    return vals;
}

/**
 * @brief Réupère les noms de tous les capteurs
 * 
 * @return vector<std::string> 
 */
vector<std::string> Scheduler::getNames() {
    vector<std::string> names = vector<std::string>();
    for (auto& sensor : this->sensorsFloat) {
        names.push_back(sensor.getName());
    }
    for (auto& sensor : this->sensorsInt) {
        names.push_back(sensor.getName());
    }
    for (auto& sensor : this->sensorsBool) {
        names.push_back(sensor.getName());
    }
    return names;
}