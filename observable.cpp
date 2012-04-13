#include "observable.h"

void Observable::notify_observers(int value){
  vector<Observer*>::iterator observer;
  for(observer = observers.begin();observer != observers.end(); observer++){
    (*observer)->update(value);
  }
}

void Observable::add_observer(Observer& observer){
  Observer* o = &observer;
  observers.push_back(o);
}
