#ifndef _ABSTRACT_MOVEMENT_HPP_
#define _ABSTRACT_MOVEMENT_HPP_

#include <map>
#include <vector>
#include <cstdint>
#include "main.h"


namespace pros {
typedef std::vector<pros::Motor> MotorSet;
}

class AbstractMovement {
  protected:
    // std::map does not allow object keys without a comparator, hence this class
    struct Comp {
        bool operator() (const pros::Motor& lhs, const pros::Motor& rhs) const {
            return true;
        }
    };


    std::map<pros::Motor, int64_t, Comp> motorTargets;
    bool reversed = false;
    bool disabled = false;

  public:
    virtual void run() = 0;
    AbstractMovement* set(pros::Motor motor, int64_t target);
    AbstractMovement* set(pros::MotorSet motors, int64_t target);

    virtual AbstractMovement* setReversedIf(bool reversed);
    virtual AbstractMovement* setDisabledIf(bool disabled);

    bool isDisabled();
    bool isReversed();
};

#endif // _ABSTRACT_MOVEMENT_HPP_
