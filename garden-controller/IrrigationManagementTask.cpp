#include "IrrigationManagementTask.h"

#include "Config.h"
#include "MsgService.h"
#include "ServoImpl.h"

IrrigationManagementTask::IrrigationManagementTask() {
  this->servo = new ServoImpl(PIN_SERVO);
  this->state = WAITING;
  this->irrigationTime = IRRIGATION_TIME;
  this->speed = 1;
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
    case RUNNING: {
      servoStart();
      servoStop();
      servoTimer();
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
  if(position > 0 && isServoEnabled){
    isServoEnabled = false;
    noInterrupts();
    position -= SERVO_TICK;
    interrupts();
    servo->setAngle(position);
  } else if(position == 0) {
    attachServoTo180 = true;
    attachServoTo0 = false;  
  }
}

void IrrigationManagementTask::goTo180(){
  if(position < 180 && isServoEnabled){
    isServoEnabled = false;
    noInterrupts();
    position += SERVO_TICK;
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
  int servoSpeed = 0;
  switch(this->speed){
    case 1:
      servoSpeed = 150;
      break;
    case 2:
      servoSpeed = 120;
      break;
    case 3:
      servoSpeed = 90;
      break;
    case 4:
      servoSpeed = 60;
      break;
    case 5:
      servoSpeed = 30;
      break;
  }

  if((millis() - tServo) >= servoSpeed){
    tServo = millis();
    isServoEnabled = true;
  }
}

void IrrigationManagementTask::irrigationSleep(){
  if((millis() - tSleep) >= SERVO_SLEEP) {
    this->state = WAITING;
  }
}

void IrrigationManagementTask::reset(){
  tStop = millis();
  tServo = millis();
}
