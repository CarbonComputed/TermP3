#ifndef MUSIC_LIST_H
#define MUSIC_LIST_H

#include <vector>
#include <string>

#include "song.h"

class MusicList : public vector<Song>{
 public:
  void sort(const string);

};

#endif
