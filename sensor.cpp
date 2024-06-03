#include "sensor.hpp"

/**
 * @brief Récupère la valeur du capteur (génère une valeur si besoin)
 * 
 * @tparam T 
 * @return T& 
 */
template <typename T>
T& Sensor<T>::getVal() {
    genVal();
    return this->val;
}

/**
 * @brief Génère une valeur pour le capteur
 * 
 * @tparam T 
 */
template <typename T>
void Sensor<T>::genVal() {
    this->val = (rand()%100) / (T) 17; // Random value for test
}

/**
 * @brief Génère une valeur pour le capteur de type booléen
 * 
 * @tparam T 
 */
template <>
void Sensor<bool>::genVal() {
    this->val = (rand()%2);
}


