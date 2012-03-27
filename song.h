#ifndef SONG_H
#define SONG_H

#include <map>
#include <string>

#include "id3.h"

using namespace std;
    
//Contains the properties and data of a given song
class Song {
 private:
   ID3v1 id3_data_;
   string path_;
   ID3v2 id3v2_data_;

 public:
   string get_path() const;
   string get_metadata(string str) const;
   void add_metadata(string,string);
   ID3v1 get_ID3() const;
   ID3v2 get_ID3v2() const;
   void set_ID3v2(ID3v2 id3v2);
   string get_title() const;
   string get_artist() const;
   string get_album() const;
   string get_length() const;

   Song(ID3v1 id3, string path);	
};

#endif
