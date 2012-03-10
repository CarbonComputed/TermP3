#ifndef LIBRARY_H
#define LIBRARY_H

#include <vector>
#include <string>

#include "music_list.h"

class Library : public MusicList{  
 private:
   string owner_;
   vector<string> search_paths_;
 public:
   Library(string);
   string get_owner() const;
   void add_search_path(const string);
   vector<string> get_paths() const; 
};

#endif
