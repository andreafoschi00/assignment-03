#ifndef __IRRIGATION_MANAGEMENT_TASK__
#define __IRRIGATION_MANAGEMENT_TASK__

#include "ServoMotor.h"
#include "Task.h"
#include "Utils.h"

class IrrigationManagementTask: public Task {
  public:
    IrrigationManagementTask();
    void tick();
    void reset();

    enum State { WAITING, SETUP, RUNNING, SLEEPING } state;

    int speed;

  private:

    void servoStart();
    void goTo180();
    void goTo0();
    void servoStop();
    void servoTimer();
    void irrigationSleep();
    
    ServoMotor* servo;

    int position;
    int servo_tick;

    long irrigationTime;
    long tStop;
    long tServo;
    long tSleep;

    bool isServoInit;
    bool attachServoTo180;
    bool isServoEnabled;
    bool attachServoTo0;
};

#endif
