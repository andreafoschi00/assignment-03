#ifndef __SERVOMOTOR__
#define __SERVOMOTOR__

class ServoMotor {
  public:
    virtual void on() = 0;
    virtual void setAngle(int angle) = 0;
    virtual void off() = 0;
};

#endif
