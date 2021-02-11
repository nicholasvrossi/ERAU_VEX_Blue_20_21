#include <cstdint>
#include "main.h"
#include "AbstractMovement.hpp"


AbstractMovement* AbstractMovement::setReversedIf(bool reversed) {
    this->reversed = reversed;
    return this;
}
AbstractMovement* AbstractMovement::setDisabledIf(bool disabled) {
    this->disabled = disabled;
    return this;
}

AbstractMovement* AbstractMovement::set(pros::Motor motor, int64_t target) {
    if (reversed)
        motorTargets[motor] = -target;
    else
        motorTargets[motor] = target;

    return this;
}
AbstractMovement* AbstractMovement::set(pros::MotorSet motors, int64_t target) {
    for (pros::Motor motor: motors)
        set(motor, target);

    return this;
}


bool AbstractMovement::isDisabled() {
    return disabled;
}
bool AbstractMovement::isReversed() {
    return reversed;
}
