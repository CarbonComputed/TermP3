#include "song.h"

Song::Song(ID3v1 id3,string path): id3_data_(id3), path_(path){
}

string Song::get_path() const{
	return this->path_;
}


ID3v1 Song::get_ID3() const{
  return this->id3_data_;
}

ID3v2 Song::get_ID3v2() const{
  return this->id3v2_data_;
}

void Song::set_ID3v2(ID3v2 id3v2){
  this->id3v2_data_ = id3v2;
}
