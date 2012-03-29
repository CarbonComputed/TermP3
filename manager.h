#ifndef MANAGER_H
#define MANAGER_H

#include <vector>

#include "observable.h"
#include "playlist.h"
#include "library.h"
#include "play_queue.h"
#include "defines.h"

class Manager : public Observable{
private:
  vector<Playlist> playlists_;
  Library library_;
  PlayQueue play_queue_;
public:
  int add_playlist(const string name);
  int delete_playlist(const string name);
  int delete_playlist(const int index);
  Library& get_library();
  PlayQueue& get_playqueue();
  Manager(const string user);

  

};



#endif
