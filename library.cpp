#include "library.h"
#include <iostream>

using namespace std;

Library::Library(string owner) :  owner_(owner), scanned_(0.0f) {
}

string Library::get_owner() const{
  return this->owner_;
}

void Library::add_search_path(const string path){
  this->search_paths_.push_back(path);
}

vector<string> Library::get_paths() const{
  return this->search_paths_;
}

int Library::get_total_files(){
  int total = 0;
  unsigned char is_folder = 0x4;
  vector<string> stack_sim;
  vector<string>::iterator path;
  char* default_dir = getcwd(NULL,0);
  for(path = search_paths_.begin(); path != search_paths_.end(); path++){
    DIR* dp = NULL;
    if((dp = opendir((*path).c_str())) == NULL) {
        cout << "Error"<<endl;
        return E_OPEN;
    }
    closedir(dp);
    stack_sim.push_back(*path);
    dirent* dirp = NULL;
    while((int)stack_sim.size() > 0){
      chdir(stack_sim.at(0).c_str());
      dp = opendir(stack_sim.at(0).c_str());
      stack_sim.erase(stack_sim.begin());
      while ((dirp = readdir(dp)) != NULL){
        if(dirp->d_name[0] != '.'){
          char* buf = getcwd(NULL,0);
          string str = buf;
          delete buf;
          str += "/";
          str += dirp->d_name;
          if(dirp->d_type == is_folder){
            stack_sim.insert(stack_sim.begin(),str);
          }
          else{
            string type="";
            size_t found = str.find_last_of(".");
            type = str.substr(found+1);
            if(type == "mp3"){
                total++;
            }
          }
        }
      }
          closedir(dp);
    }
  }
  chdir(default_dir);
  free (default_dir);
  return total;
}

int Library::get_percent_scanned() const{
  return (int)(scanned_ * 100.0);
}

int Library::scan(){
  unsigned char is_folder = 0x4;
  int count = 0;
  int total = get_total_files();
  vector<string> stack_sim;
  vector<string>::iterator path;
  char* default_dir = getcwd(NULL,0);
  
  for(path = search_paths_.begin(); path != search_paths_.end(); path++){
    DIR* dp = NULL;
    if((dp = opendir((*path).c_str())) == NULL) {
        return E_OPEN;
    }
    closedir(dp);
    stack_sim.push_back(*path);
    dirent* dirp = NULL;
    while((int)stack_sim.size() > 0){
      chdir(stack_sim.at(0).c_str());
      dp = opendir(stack_sim.at(0).c_str());
      stack_sim.erase(stack_sim.begin());
      while ((dirp = readdir(dp)) != NULL){
        if(dirp->d_name[0] != '.'){ 
          char* buf = getcwd(NULL,0);
          string str = buf;
          delete buf;
          str += "/";
          str += dirp->d_name;
          if(dirp->d_type == is_folder){
            stack_sim.insert(stack_sim.begin(),str);
          }
          else{
            string type="";
            size_t found = str.find_last_of(".");
            type = str.substr(found+1);
            if(type == "mp3"){
              Song s = Song(readID3(str),str);
              if(s.get_ID3().title[0] == '\0' || s.get_ID3().header[0] == '\0'){
                s.set_ID3v2(readID3v2(str)); 
//                cout<<s.get_ID3v2().frames["TIT2"].data<<endl;
              }
              count++;
              scanned_ = (float)count /(float) total;
              notify_observers(SCANNING);
              this->push_back(s);
//              string title;
//              title += s.get_ID3().title; 
             // title += "\0";
               
//              cout<<s.get_ID3().header[0]<<" "<<title<<"----"<<str<<endl;
            }
             
          }
        }
  //      delete dirp;
  //      dirp = NULL;
      }
          closedir(dp);
      //  delete dp;
      //  delete dirp;
//        dp = NULL;
    }
}
  chdir(default_dir);
  free (default_dir);
  notify_observers(SUCCESS);
  return 1; 
}
