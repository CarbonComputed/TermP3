#include "play_queue.h"

Song PlayQueue::get_current() const{
  return this->current_;
}

void PlayQueue::set_current(const Song current){
  this->current_ = current;
}

void PlayQueue::play(){

}

void PlayQueue::pause(){
}

void PlayQueue::next(){
}

void PlayQueue::prev(){
}
