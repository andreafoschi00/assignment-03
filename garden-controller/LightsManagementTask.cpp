#include "LightsManagementTask.h"
#include "Config.h"
#include "MsgService.h"
#include "IrrigationManagementTask.h"

LightsManagementTask::LightsManagementTask(IrrigationManagementTask* irrMngTask, MsgServiceBT* btService) {
  this->led1 = new Led(PIN_LED1);
  this->led2 = new Led(PIN_LED2);
  this->led3 = new Led(PIN_LED3);
  this->led4 = new Led(PIN_LED4);

  this->irrMngTask = irrMngTask;
  this->btService = btService;
  this->state = AUTO_MODE;
}

void LightsManagementTask::tick(){
  switch(state){
    case AUTO_MODE: {
      if(MsgService.isMsgAvailable() && irrMngTask->state == IrrigationManagementTask::State::WAITING) {
        Msg* msg = MsgService.receiveMsg();
        String content = msg->getContent();

        int index = content.indexOf(',');
        int secondIndex = content.indexOf(',', index+1);
        int length = content.length();

        String temperature_toString = content.substring(0,index);
        int temperature = temperature_toString.toInt();
        String intensity_toString = content.substring(index+1,secondIndex);
        int intensity = intensity_toString.toInt();
        String state = content.substring(secondIndex+1, length);

        if (state == "alarm") {
          this->state = ALARM_MODE;
        } else if(intensity < 5) {
          this->led1->turnOn();
          this->led2->turnOn();
          this->led3->turnOnWithValue(intensity);
          this->led4->turnOnWithValue(intensity);

          if(intensity < 2) {
            this->irrMngTask->speed = temperature;
            this->irrMngTask->state = IrrigationManagementTask::State::SETUP;
          }
        } else {
          this->led1->turnOff();
          this->led2->turnOff();
          this->led3->turnOff();
          this->led4->turnOff();
        }

        delete msg;
      }

      if(btService->isMsgAvailable()){
        Msg* msg = btService->receiveMsg();
        String content = msg->getContent();

        if(content.equals("manual")) {
          this->state = MANUAL_MODE;
        }

        delete msg;
      }
      break;
    }
    
    case MANUAL_MODE: {
      if (btService->isMsgAvailable()) {
        Msg* msg = btService->receiveMsg();
        String content = msg->getContent();

        if (content.equals("auto")) {
          this->state = AUTO_MODE;
        } else if (content.equals("L1")) {
        if (this->led1->isActive()) {
          this->led1->turnOff();
        } else {
          this->led1->turnOn();
        }
        } else if (content.equals("L2")) {
          if (this->led2->isActive()) {
            this->led2->turnOff();
          } else {
            this->led2->turnOn();
          }
         } else if (content.startsWith("3")) {
          int intensity = toDigit(content[2]);
          this->led3->turnOnWithValue(intensity);
         } else if (content.startsWith("4")) {
          int intensity = toDigit(content[2]);
          this->led4->turnOnWithValue(intensity);
         } else if (content.equals("irrigation")) {
           // irrigation
           // this->irrigationTask->state = PAUSE;
         } else if (content.startsWith("s")) {
           // sn - n represents the value of the speed (1-8)
           int newSpeed = toDigit(content[1]);
           this->irrMngTask->speed = newSpeed;
         }

          delete msg;
        }
        break;
    }

    case ALARM_MODE: {
      if (btService->isMsgAvailable()) {
        Msg* msg = btService->receiveMsg();
        String msgContent = msg->getContent();

        if (msgContent.equals("alarm")) {
          // alarm
          this->state = AUTO_MODE;
        }

        delete msg;
      }
      break;
    }
  }
}
