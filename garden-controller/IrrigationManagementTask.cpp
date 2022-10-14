#include "IrrigationManagementTask.h"

#include "Config.h"
#include "MsgService.h"
#include "ServoImpl.h"

IrrigationManagementTask::IrrigationManagementTask() {
  this->servo = new ServoImpl(PIN_SERVO);
  this->state = WAITING;
  this->speed = 1;
  this->servo_tick = 1;
  this->servo->on();
  this->position = 0;
  this->servo->setAngle(position);
  delay(15);
  this->servo->off();
  this->forward = true;
}

void IrrigationManagementTask::tick(){
  switch(state){
    case WAITING: {
      // LightsManagementTask will change the state in SETUP when it's time to start irrigation
      break;
    }
    case SETUP: {
      servoSetup();
      break;
    }
    case RUNNING: {
      moveServo();
      break;
    }
    case SLEEPING: {
      irrigationSleep();
      break;
    }
  }
}

void IrrigationManagementTask::moveServo(){
  irrigationProgress = millis();
  // Check if it's still time to irrigate
  if((irrigationProgress - tStart) <= IRRIGATION_TIME) {
    if(forward) {
      while(position < 180) {
        position += servo_tick;
        servo->setAngle(position);
        delay(15); // --> Wait for servo to reach selected angle
      }
      forward = false;
    } else {
      while(position > 0) {
        position -= servo_tick;
        servo->setAngle(position);
        delay(15); // --> Wait for servo to reach selected angle
      }
      forward = true;
    }
  } else {
    servo->off();
    tStop = millis();
    state = SLEEPING;
  }
}

void IrrigationManagementTask::servoSetup() {
  // Change speed of the servo (given by the service using serial)
  switch(this->speed){
    case 1:
      this->servo_tick = 1; // --> Speed 1
      break;
    case 2:
      this->servo_tick = 3; // --> Speed 2
      break;
    case 3:
      this->servo_tick = 5; // --> Speed 3
      break;
    case 4:
      this->servo_tick = 7; // --> Speed 4
      break;
    case 5:
      this->servo_tick = 10; // --> Speed 5
      break;
  }
    servo-> on();
    forward = true;
    tStart = millis();
    state = RUNNING;
}

void IrrigationManagementTask::irrigationSleep(){
  sleepProgress = millis();
  // Check if is still time to sleep
  if((sleepProgress - tStop) >= SERVO_SLEEP) {
    this->state = WAITING;
  }
}
