#include "id3.h"
#include <iostream>
#include <cstdlib>
using namespace std;

ID3v1 readID3(string file){
    ifstream infile(file.c_str(),ios::binary);
    infile.seekg(-128,ios::end);
    ID3v1 id3;
    id3.title[0] = '\0';
    id3.artist[0] = '\0';
    id3.album[0] = '\0';
    if(!infile){
        infile.close();
        return id3; 
    }

    char header[3]="";
   // id3.title[0]='\0';
    infile.read(header,3);
    if(header[0] != 'T' || header[1] != 'A' || header[2] != 'G'){
      return id3;
    }
    strncpy(id3.header,header,3);
    char title[30]="";
    infile.read(title,30);
    strncpy(id3.title,title,30);
    char artist[30]="";
    infile.read(artist,30);
    strncpy(id3.artist,artist,30);
    char album[30];
    infile.read(album,30);
    strncpy(id3.album,album,30);
    char year[4];
    infile.read(year,4);
    strncpy(id3.year,year,4);
    char comment[28];
    infile.read(comment,28);
    strncpy(id3.comment,comment,28);
    infile >> id3.zerobyte; 
    infile >> id3.track;
    infile >> id3.genre;
    infile.close();
    return id3;
 
}

int to_int_32(char* bytes){
  int Int32 = 0;
  Int32 = ((int)bytes[2]) + ((int)bytes[1] << 8) + ((int)bytes[0]<<16);
  return Int32;
}

int syncsafe(int i)
{
 int toReturn = 0;
 toReturn |= ((i & 0x7F000000) >> 24);
 toReturn |= ((i & 0x007F0000) >>  9);
 toReturn |= ((i & 0x00007F00) <<  6);
 toReturn |= ((i & 0x0000007F) << 21);
 return toReturn;     
}

ID3v2 readID3v2(string file){
  ifstream infile(file.c_str(),ios::binary);
  ID3v2 id3;
  ID3v2_header head = readID3v2_head(infile);
  if(head.tag[0] != 'I' || head.tag[1] != 'D' || head.tag[2]!= '3'){
    return id3;
  }
  id3.head = head;  
  int ctr = 0;
  while(ctr <= head.size){
    ID3v2_frame frame = readID3v2_frame(id3,infile);
//    cout<<frame.id<<endl;
//    cout<<frame.data<<endl;
    ctr += frame.size;
    if((int)id3.head.version <=2){
      ctr+=6;
    }
    else{
      ctr += 10;
    }
    if(frame.size < 1){
      break;
    }
    string s;
    s += frame.id;
    if((int)id3.head.version <=2){
      id3.frames[s.substr(0,3)] = frame;
    }
    else{
      id3.frames[s.substr(0,4)] =  frame;
    }
  }
  infile.close();
  return id3;
}

ID3v2_frame readID3v2_frame(ID3v2& id3, ifstream& infile){
  ID3v2_frame frame;
  if(((int)id3.head.version) <= 2){
    infile.read(frame.id,3);
//    cout<<frame.id<<endl;
    int size;
    char b[3];
    infile.read(b,3);
    //infile.read(reinterpret_cast<char*>(&size),3);
   // int32_t s = size;
    frame.size = to_int_32(b);
//    cout<<frame.size<<endl;
    //frame.size = syncsafe(size);
  }
  else{
    infile.read(frame.id,4);
    int size;
    infile.read(reinterpret_cast<char*>(&size), sizeof(size));
    frame.size = size;
    frame.size=syncsafe(frame.size);
    infile.read(frame.flags,2);

  }
  int tempsize = frame.size;
  if(tempsize < 1 || tempsize > 1000){
    return frame;
  }
  if(frame.id[0] == 'T'){
    infile >> frame.enc;
    tempsize -= 1;
  }
//  cout<<tempsize<<endl;
  char buf[tempsize];
  infile.read(buf,tempsize);
  frame.data += buf;
  return frame;
}

ID3v2_header readID3v2_head(ifstream& infile){
    ID3v2_header head;
    infile.read(head.tag,3);
    infile >> head.version;
    infile >> head.subversion;
    infile >> head.flag;
    int size;
    infile.read(reinterpret_cast<char*>(&size), sizeof(size));
    size = syncsafe(size);
    head.size = size;
    return head;
 
}
