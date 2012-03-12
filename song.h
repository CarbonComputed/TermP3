#ifndef SONG_H
#define SONG_H

#include <map>
#include <string>

#include "id3.h"

using namespace std;
    
//Contains the properties and data of a given song
class Song {
 private:
   map < string , string > metadata_;
   string path_;
   ID3v1 id3_data_;

 public:
   string get_path() const;
   string get_metadata(string str) const;
   void add_metadata(string,string);
   ID3v1 get_ID3() const;
   Song(ID3v1 id3);		
};

#endif
