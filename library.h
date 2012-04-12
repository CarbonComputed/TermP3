#ifndef LIBRARY_H
#define LIBRARY_H

#include <sys/types.h>
#include <dirent.h>
#include <vector>
#include <string>
#include <stdlib.h>
#include <fstream>

#include "music_list.h"
#include "observable.h"
#include "defines.h"
#include "id3.h"

class Library : public MusicList, public Observable{  
 private:
   string owner_;
   vector<string> search_paths_;
   float scanned_;
 public:
   Library(string);
   string get_owner() const;
   void add_search_path(const string);
   vector<string> get_paths() const;
   int scan();
   int get_total_files();
   int get_percent_scanned() const; 
};

#endif
