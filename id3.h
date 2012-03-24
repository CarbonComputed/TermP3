#ifndef id3_H
#define id3_H

#include <stdio.h>
#include <string.h>
#include <fstream>
#include <string>
#include <map>

using namespace std;

struct ID3v1{
    char header[3];
    char title[30];
    char artist[30];
    char album[30];
    char year[4];
    char comment[28];
    char zerobyte;
    char track;
    char genre;

};

struct ID3v2_header{
  char tag[3];
  unsigned char version;
  unsigned char subversion;
  char flag;
  int size;
};


struct ID3v2_frame{
  char id[4];
  int size;
  char flags[2];
  char enc;
  string data;
};

struct ID3v2{
  ID3v2_header head;
  map<string,ID3v2_frame> frames;
};

ID3v1 readID3(string file);
ID3v2_header readID3v2_head(ifstream& infile);
ID3v2_frame readID3v2_frame(ifstream& infile);
ID3v2 readID3v2(string file);
#endif

