#ifndef SONG_H
#define SONG_H

#include <map>
#include <string>

using namespace std;
    
//Contains the properties and data of a given song
class Song {
 private:
   map < string , string > metadata_;
   string path_;
 public:
   string get_path() const;
   string get_metadata(string str) const;
   void add_metadata(string,string);
		
};

#endif
