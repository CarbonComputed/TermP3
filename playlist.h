#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <string>

#include "music_list.h"

class Playlist : public MusicList {
 private:
   string name_;
 public:
   Playlist(string);
   string get_name() const;

};

#endif
