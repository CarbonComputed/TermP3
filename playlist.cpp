#include "playlist.h"

Playlist::Playlist(string name) : name_(name) {}

string Playlist::get_name() const{
  return this->name_;
}
