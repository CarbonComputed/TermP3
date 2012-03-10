#ifndef PLAY_QUEUE_H
#define PLAY_QUEUE_H

#include "music_list.h"
#include "song.h"

class PlayQueue : MusicList{
 private:
   Song current_;

 public:
   Song get_current() const;
   void set_current(const Song);

};

#endif
