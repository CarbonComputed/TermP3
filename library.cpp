#include "library.h"

Library::Library(string owner) :  owner_(owner) {}

string Library::get_owner() const{
  return this->owner_;
}

void Library::add_search_path(const string path){
  this->search_paths_.push_back(path);
}

vector<string> Library::get_paths() const{
  return this->search_paths_;
}
