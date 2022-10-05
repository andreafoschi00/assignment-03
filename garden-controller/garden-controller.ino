#include <Arduino.h>

#include "Scheduler.h"
#include "Task.h"

Scheduler scheduler;

void setup() {
  scheduler.init(10);
}

void loop() {
  scheduler.schedule();
}
