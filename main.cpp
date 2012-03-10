#include <iostream>

#include "song.h"
#include "music_list.h"

using namespace std;

int main(int args, char* argv[]){
	Song m;
	m.add_metadata("track", "blah.mp3");
	cout << m.get_metadata("track")<<endl;
  MusicList list;
  list.push_back(m);
  cout<<list.at(0).get_metadata("track")<<endl;
	return 0;
}
