#include <functional>
#include <vector>
#include <cmath>
#include <cstdint>
#include "main.h"
#include "../../G_inc/headers/InvKinematics.hpp"
#include "../../G_inc/headers/AbstractMovement.hpp"


void InvKinematics::addAndRunCommand(std::function<void()> funct) {
    //commands.push_back(funct);
    //commands.back()(); // this is not an error - don't mess with it
    funct();
}


//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//<<<                     >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//<<< InvKinematics::move >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//<<<                     >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
InvKinematics* InvKinematics::move(AbstractMovement* command) {
    addAndRunCommand([&command]() {
        if (command->isDisabled()) {
            command->run();
        }
    });

    return this;
}


//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//<<<                      >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//<<< InvKinematics::delay >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//<<<                      >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
InvKinematics* InvKinematics::delay(int64_t millis) {
    addAndRunCommand([millis]() {
        pros::delay(millis);
    });

    return this;
}


//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//<<<                     >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//<<< InvKinematics::hold >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//<<<                     >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
InvKinematics* InvKinematics::hold(pros::Motor motor, int velocity) {
    addAndRunCommand([motor, velocity, this]() {
        motor.move(velocity);
    });

    return this;
}
InvKinematics* InvKinematics::hold(pros::MotorSet motors, int velocity) {
    addAndRunCommand([motors, velocity, this]() {
        for (pros::Motor motor: motors)
            hold(motor, velocity);
    });

    return this;
}


//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//<<<                     >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//<<< InvKinematics::stop >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//<<<                     >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
InvKinematics* InvKinematics::stop(pros::Motor motor) {
    addAndRunCommand([motor, this]() {
        hold(motor, 0);
    });

    return this;
}
InvKinematics* InvKinematics::stop(pros::MotorSet motors) {
    addAndRunCommand([motors, this]() {
        for (pros::Motor motor: motors)
            stop(motor);
    });

    return this;
}


//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//<<<                      >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//<<< InvKinematics::pulse >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//<<<                      >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
InvKinematics* InvKinematics::pulse(pros::Motor motor, int velocity, int duration) {
    addAndRunCommand([motor, velocity, duration, this]() {
        hold(motor, velocity);
        delay(duration);
        hold(motor, 0);
    });

    return this;
}
InvKinematics* InvKinematics::pulse(pros::MotorSet motors, int velocity, int duration) {
    addAndRunCommand([motors, velocity, duration, this]() {
        for (pros::Motor motor: motors)
            pulse(motor, velocity, duration);
    });

    return this;
}


//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//<<<                     >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//<<< InvKinematics::tare >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//<<<                     >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
InvKinematics* InvKinematics::tare(pros::Motor motor) {
    addAndRunCommand([motor, this]() {
        motor.tare_position();
    });

    return this;
}
InvKinematics* InvKinematics::tare(pros::MotorSet motors) {
    addAndRunCommand([motors, this]() {
        for (pros::Motor motor: motors)
            tare(motor);
    });

    return this;
}
