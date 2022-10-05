#ifndef __TASK__
#define __TASK__

class Task {

  private: 
    int myPeriod;
    int timeElapsed;
    bool active;
    bool periodic;
    bool completed;
    
  public:
    Task() {
      active = false;
    }

  // Periodic task
  virtual void init(int period){
    myPeriod = period;
    periodic = true;
    active = true;
    timeElapsed = 0;
  }

  // Aperiodic task
  virtual void init() {
    periodic = false;
    active = true;
    timeElapsed = 0;
    completed = false;
  }

  virtual void tick() = 0;

  bool updateAndCheckTime(int basePeriod) {
    timeElapsed += basePeriod;
    if(timeElapsed >= myPeriod){
      timeElapsed = 0;
      return true;
    } else {
      return false;
    }
  }

  bool isActive() {
    return active;
  }

  bool isPeriodic() {
    return periodic;
  }

  bool isCompleted() {
    return completed;
  }

  void setCompleted() {
    completed = true;
  }
  
  virtual void setActive(bool active) {
    timeElapsed = 0;
    this->active = active;
  }
};

#endif
