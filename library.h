#ifndef LIBRARY_H
#define LIBRARY_H

#include <sys/types.h>
#include <dirent.h>
#include <vector>
#include <string>
#include <fstream>

#include "music_list.h"
#include "defines.h"
#include "id3.h"

class Library : public MusicList{  
 private:
   string owner_;
   vector<string> search_paths_;
 public:
   Library(string);
   string get_owner() const;
   void add_search_path(const string);
   vector<string> get_paths() const;
   int scan(); 
};

#endif
