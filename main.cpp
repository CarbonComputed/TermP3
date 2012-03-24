#include <iostream>

#include "song.h"
#include "music_list.h"
#include "library.h"

using namespace std;

int main(int args, char* argv[]){
//  Song m;
//  m.add_metadata("track", "blah.mp3");
//    m.add_metadata("track", "blah2.mp3");
//  cout << m.get_metadata("track")<<endl;
    MusicList list;
//    list.push_back(m);
    Library lib("kevin");
    lib.add_search_path("/home/kevin/Music");
    lib.scan();
    cout<<lib.size()<<endl;
//    cout<<list.at(0).get_metadata("track")<<endl;
  return 0;
}
