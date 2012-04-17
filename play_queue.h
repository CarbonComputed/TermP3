#ifndef PLAY_QUEUE_H
#define PLAY_QUEUE_H

#include <stdio.h>
#include <sstream>
#include "irrKlang-1.3.0/include/irrKlang.h"

#include "music_list.h"
#include "song.h"
#include "defines.h"
#include "observable.h"

using namespace irrklang;

#pragma comment(lib,"irrKlang.lib");

class PlayQueue : public MusicList, public Observable{
 private:
   ISoundEngine* engine_;
   ISound* sound_;
   Song* current_;
   int index_;

 public:
   PlayQueue();
   ~PlayQueue();
   Song* get_current();
   void play(int index);
   void pause();
   void next();
   void prev();
   bool current_is_finished();
   string get_song_length();
   string get_song_position();

};

#endif
