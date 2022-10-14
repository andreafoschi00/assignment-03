#ifndef __LIGHTS_MANAGEMENT_TASK__
#define __LIGHTS_MANAGEMENT_TASK__

#include "MsgServiceBT.h"
#include "Led.h"
#include "Task.h"
#include "IrrigationManagementTask.h"

// This task manage the ON/OFF of LEDs 1,2 and luminosity of LEDs 3,4

class LightsManagementTask: public Task {
  public:
    LightsManagementTask(IrrigationManagementTask* task, MsgServiceBT* btService);
    void tick();

    private:
      enum{AUTO_MODE, MANUAL_MODE, ALARM_MODE} state;
     
      Led* led1;
      Led* led2;
      Led* led3;
      Led* led4;

      IrrigationManagementTask* irrMngTask;
      MsgServiceBT* btService;
};

#endif
