#ifndef _PID_Movement_HPP_
#define _PID_Movement_HPP_


#include <cstdint>
#include "main.h"
#include "AbstractMovement.hpp"


struct PIDConstants {
    double Kp = 0.01;
	double Ki = 0.000001;
	double Kd = 0.001;
	uint64_t integralActiveRange = 15;
};

class PIDMovement: public AbstractMovement {
  private:
    class PIDVariables {
      public:
        int64_t lastError;
        int64_t integral;
        int64_t derivative;

        PIDVariables(int64_t lastError);
    };

    PIDConstants consts;

  public:
    void run();

    PIDMovement* setConsts(PIDConstants pidConsts);
};

#endif // _PID_Movement_HPP_
