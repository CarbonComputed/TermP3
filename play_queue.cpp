#include "play_queue.h"

PlayQueue::PlayQueue(){
  engine_ = createIrrKlangDevice();
  sound_ = NULL;
  current_ = NULL;
  if(!engine_){
    printf("Could not startup engine\n");
  }
}

PlayQueue::~PlayQueue(){
  engine_->drop();
}

Song* PlayQueue::get_current(){
  return current_;
}

bool PlayQueue::current_is_finished(){
  if(sound_ != NULL){
    return sound_->isFinished();
  }
  return false;
}

void PlayQueue::play(int index){
  engine_->stopAllSounds();
  sound_ = engine_->play2D(this->at(index).get_path().c_str(),false,false,true);
  current_ = &(this->at(index));
  index_ = index;
  notify_observers(REFRESH);
}

void PlayQueue::pause(){
  if(sound_->getIsPaused()){  
    sound_->setIsPaused(false);
  }
  else{
    sound_->setIsPaused(true);
  }
  notify_observers(REFRESH);
}

string PlayQueue::get_song_length(){
  stringstream str;
  if(sound_ != NULL){
    ik_u32 min = sound_->getPlayLength() / 60000;
    ik_u32 sec = (sound_->getPlayLength() % 60000) / 1000;
    str << min;
    str << ":";
    if(sec < 10){
      str << "0";
    }
    str << sec;
  }
  return str.str();
}

string PlayQueue::get_song_position(){
  stringstream str;
  if(sound_ != NULL){
    ik_u32 min = sound_->getPlayPosition() / 60000;
    ik_u32 sec = (sound_->getPlayPosition() % 60000) / 1000;
    str << min;
    str << ":";
    if(sec < 10){
      str << "0";
    }
    str << sec;
  }
  return str.str();
}

void PlayQueue::next(){
  if(index_ + 1 < size()){
    play(index_+1);
  }
}

void PlayQueue::prev(){
  if(index_ -1  >= 0){
    play(index_-1);
  }
}
