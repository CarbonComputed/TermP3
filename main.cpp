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
//    MusicList list;
//    list.push_back(m);
  ID3v2 id32;
  ID3v1 id31;
    //Library lib("kevin");
  id32 = readID3v2(argv[1]); 
  id31 = readID3(argv[1]); 
//  for(int x=0;x<20;x++)
  cout <<id31.header<<endl;
  printf("%hhd\n", id32.head.version);
  cout<<(int)id32.head.version<<endl;
  cout << id31.title[1] <<endl; 
  cout << id32.frames["TPE1"].data<<endl;
   //lib.add_search_path("/home/kevin/Music");
//    lib.scan();
//    cout<<lib.size()<<endl;
//    cout<<list.at(0).get_metadata("track")<<endl;
  return 0;
}
