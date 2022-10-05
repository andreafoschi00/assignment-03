#include "Scheduler.h"
#include <TimerOne.h>

volatile bool timerFlag;

void timerHandler(void) {
  timerFlag = true;
}

void Scheduler::init(int period) {
  this->basePeriod = period;
  timerFlag = false;
  long lPeriod = 1000l* period;
  Timer1.initialize(lPeriod);
  Timer1.attachInterrupt(timerHandler);
  nTasks = 0;
}

bool Scheduler::addTask(Task* task) {
  if(nTasks < MAX_TASKS - 1) {
    taskList[nTasks] = task;
    nTasks++;
    return true;
  } else {
    return false;
  }
}

void Scheduler::schedule() {
  while (!timerFlag) { }
  timerFlag = false;

  for(int i=0; i<nTasks; i++) {
    if(taskList[i]->isActive()) {
      if(taskList[i]->isPeriodic()) {
        if(taskList[i]->updateAndCheckTime(basePeriod)) {
          taskList[i]->tick();
        }
      } else {
        taskList[i] -> tick();
        if(taskList[i]->isCompleted()) {
          taskList[i]->setActive(false);
        }
      }
    }
  }
}
