#ifndef __SENSOR_HPP__
#define __SENSOR_HPP__

#include <cstdlib>
#include <string>


template <typename T> class Sensor {
    private:
        T val;
        std::string name;
        void genVal();
    public:
        Sensor() : val(0), name(nullptr) {}
        Sensor(const T& value, const std::string name_) : val(value), name(name_) {}
        Sensor(const Sensor& sensor) : val(sensor.val), name(sensor.name) {}
        
        virtual ~Sensor() {}

        std::string getName() const { return this->name; }
        T& getVal();
        // Random values for test ?, called by getVal()
      
};

template class Sensor<float>;
template class Sensor<int>;
template class Sensor<bool>;

#endif // __SENSOR_HPP__ 