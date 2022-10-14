#ifndef __IRRIGATION_MANAGEMENT_TASK__
#define __IRRIGATION_MANAGEMENT_TASK__

#include "ServoMotor.h"
#include "Task.h"
#include "Utils.h"

// This task manage the irrigation system, controlled by the servo motor.

class IrrigationManagementTask: public Task {
  public:
    IrrigationManagementTask();
    void tick();

    enum State { WAITING, SETUP, RUNNING, SLEEPING } state;

    int speed;

  private:

    void moveServo();
    void servoSetup();
    void irrigationSleep();
    
    ServoMotor* servo;

    int position;
    int servo_tick;

    unsigned long irrigationProgress;
    unsigned long sleepProgress;
    unsigned long tStart;
    unsigned long tStop;

    bool forward;
};

#endif
