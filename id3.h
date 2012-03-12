#ifndef id3_H
#define id3_H

#include <stdio.h>
#include <string.h>
#include <fstream>
#include <string>

using namespace std;

#define BUF_SIZE 128

struct ID3v1{
    char header[3];
    char title[30];
    char artist[30];
    char album[30];
    char year[4];
    char comment[28];
    bool zerobyte;
    bool track;
    bool genre;

};

ID3v1 readID3(string file);
#endif

