#ifndef OBSERVABLE_H
#define OBSERVABLE_H

#include <vector>

#include "observer.h"

using namespace std;

class Observable{
 private:
  vector<Observer*> observers;

 public:
  virtual void notify_observers(int value);
  virtual void add_observer(Observer& observer);

};

#endif
