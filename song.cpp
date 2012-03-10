#include "song.h"

string Song::get_path() const{
	return this->path_;
}

string Song::get_metadata(string str) const{
	return this->metadata_.find(str)->second;
}

void Song::add_metadata(string key, string val){
	this->metadata_.insert(pair<string,string>(key,val));
}

