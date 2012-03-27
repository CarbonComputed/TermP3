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

string Song::get_title() const{
  string title;
  title += this->get_ID3().title;
  if(title.length() <= 0){
    title += this->get_ID3v2().frames["TIT2"].data;
  }
  if(title.length() <= 0){
      title += this->get_ID3v2().frames["TT2"].data;
   }
   if(title.length() <= 0){ 
        size_t found = this->get_path().find_last_of(".");
        size_t found2 = this->get_path().find_last_of("/"); 
        title += this->get_path().substr(found2+1);
   }
   return title;
}

string Song::get_artist() const{
  string artist;
  artist += this->get_ID3().artist;
  if(artist.length() <= 0){
    artist += this->get_ID3v2().frames["TPE1"].data;
  }
  if(artist.length() <= 0){
    artist += this->get_ID3v2().frames["TPE2"].data;
  }
  if(artist.length() <= 0){
    artist += this->get_ID3v2().frames["TP1"].data;
  }
  if(artist.length() <= 0){
    artist = "UNKNOWN";
  }
  return artist;
}
   
string Song::get_album() const{
  string album;
  album += this->get_ID3().album;
  if(album.length() <= 0){
    album += this->get_ID3v2().frames["TALB"].data;
  }
  if(album.length() <= 0){
    album += this->get_ID3v2().frames["TAL"].data;
  }
  if(album.length() <= 0){
    album = "UNKNOWN";
  }
  return album;
}
   
string Song::get_length() const{
  return "0:00";
}


