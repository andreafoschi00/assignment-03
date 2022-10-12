#include <Arduino.h>

#include "Scheduler.h"
#include "Task.h"
#include "Config.h"
#include "MsgService.h"
#include "MsgServiceBT.h"
#include "LightsManagementTask.h"
#include "IrrigationManagementTask.h"

Scheduler scheduler;
MsgServiceBT *btMsgService;

void setup() {

  Serial.begin(115200);
  btMsgService = new MsgServiceBT(PIN_BT_RDX, PIN_BT_TDX);
  btMsgService -> init();
  
  scheduler.init(10);

  Task* irrigationTask = new IrrigationManagementTask();
  irrigationTask->init(50);
  irrigationTask->setActive(true);

  Task* lightsTask = new LightsManagementTask((IrrigationManagementTask *)irrigationTask, btMsgService);
  lightsTask->init(50);
  lightsTask->setActive(true);

  scheduler.addTask(irrigationTask);
  scheduler.addTask(lightsTask);

}

void loop() {
  scheduler.schedule();
}
