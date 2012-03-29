#include "manager.h"

Manager::Manager(const string user): library_(user){
}

int Manager::add_playlist(const string name){
  vector<Playlist>::iterator pl;
  for(pl = playlists_.begin(); pl != playlists_.end(); pl++){
    if(pl->get_name() == name){
        return E_ADD;   
    }
  }
  playlists_.push_back(Playlist(name));
  return SUCCESS;
}

int Manager::delete_playlist(const string name){
  vector<Playlist>::iterator pl;
  for(pl = playlists_.begin();pl != playlists_.end(); pl++){
    if(pl->get_name() == name){
      playlists_.erase(pl);
      return SUCCESS;
    }
  }
  return E_DELETE;
}

int Manager::delete_playlist(const int index){
  if(index < 0 || index >= playlists_.size()){ 
    return E_DELETE; 
  }
  playlists_.erase(playlists_.begin() + index);
  return SUCCESS;
}

Library& Manager::get_library(){
  return library_;
}

PlayQueue& Manager::get_playqueue(){
  return play_queue_;
}


