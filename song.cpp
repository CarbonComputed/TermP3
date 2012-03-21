#include "song.h"

Song::Song(ID3v1 id3,string path): id3_data_(id3), path_(path){
}

string Song::get_path() const{
	return this->path_;
}

string Song::get_metadata(string str) const{
	return this->metadata_.find(str)->second;
}

void Song::add_metadata(string key, string val){
	this->metadata_.insert(pair<string,string>(key,val));
}

ID3v1 Song::get_ID3() const{
  return this->id3_data_;
}
