#include "id3.h"

ID3v1 readID3(string file){
    char buf[BUF_SIZE]="";
    ifstream infile(file.c_str(),ios::binary);
    infile.seekg(-BUF_SIZE,ios::end);
    ID3v1 id3; 
    if(!infile || !infile.read(buf, BUF_SIZE)){
        infile.close();
        return id3; 
    }
    infile.close();
    memcpy(&id3,buf,128);
    return id3;
 
}
