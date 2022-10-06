#include "IrrigationManagementTask.h"

#include "Config.h"
#include "MsgService.h"
#include "ServoImpl.h"

IrrigationManagementTask::IrrigationManagementTask() {
  this->servo = new ServoImpl(PIN_SERVO);
  this->state = WAITING;
  this->irrigationTime = IRRIGATION_TIME;
  this->speed = 1;
  this->servo_tick = 1;
  this->position = 0;
  this->servo->on();

  isServoInit = false;
  tStop = millis();
  tServo = millis();
  attachServoTo180 = true;
  attachServoTo0 = false;
  isServoEnabled = false;
}

void IrrigationManagementTask::tick(){
  switch(state){
    case WAITING: {
      break;
    }
    case SETUP: {
      servoTimer();
      break;
    }
    case RUNNING: {
      servoStart();
      servoStop();
      break;
    }
    case SLEEPING: {
      irrigationSleep();
      break;
    }
  }
}

void IrrigationManagementTask::servoStart(){
  if(!isServoInit) {
    position = 0;
    isServoInit = true;
  }
  
  if(attachServoTo180){
    goTo180(); 
  } else {
    goTo0();
  }
}

void IrrigationManagementTask::goTo0(){
  if(position > 0){
    noInterrupts();
    position -= servo_tick;
    interrupts();
    servo->setAngle(position);
  } else if(position == 0) {
    attachServoTo180 = true;
    attachServoTo0 = false;  
  }
}

void IrrigationManagementTask::goTo180(){
  if(position < 180){
    noInterrupts();
    position += servo_tick;
    interrupts();
    servo->setAngle(position);
  } else if(position == 180) {
    attachServoTo180 = false;
    attachServoTo0 = true;  
  }
}



void IrrigationManagementTask::servoStop(){
  if((millis() - tStop) >= irrigationTime){
    this->state = SLEEPING;
    tStop = millis();
    tSleep = millis();
    Serial.println("Servo is going to sleep...");
  }
}

void IrrigationManagementTask::servoTimer() {
  Serial.println(this->speed);
  switch(this->speed){
    case 1:
      this->servo_tick = 1;
      break;
    case 2:
      this->servo_tick = 5;
      break;
    case 3:
      this->servo_tick = 10;
      break;
    case 4:
      this->servo_tick = 20;
      break;
    case 5:
      this->servo_tick = 30;
      break;
  }

    tServo = millis();
    state = RUNNING;
}

void IrrigationManagementTask::irrigationSleep(){
  if((millis() - tSleep) >= SERVO_SLEEP) {
    this->state = WAITING;
    Serial.println("Servo is ready.");
  }
}

void IrrigationManagementTask::reset(){
  tStop = millis();
  tServo = millis();
}
