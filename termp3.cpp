#include <iostream>
#include <ncurses/curses.h>
#include <pthread.h>
using namespace std;

#include "main_window.h"
#include "manager.h"


void *scan_library(void* ptr){
  Manager* music_manager = (Manager*) ptr;
  int e = music_manager->get_library().scan();
  if(e==E_OPEN){
   // cout<<"Error Opening directory"<<endl;
  }
}

int main(int argc, char* argv[]){
  Manager music_manager("Kevin");
  MainWindow main_window(music_manager);
  music_manager.add_observer(main_window);
  music_manager.get_library().add_observer(main_window);
  music_manager.get_library().add_search_path("/home/kevin/Music");
  main_window.init();
  pthread_t scanner;
  int rc = pthread_create(&scanner,NULL,scan_library,(void*) &music_manager);
  if(rc){
    getch();
    printw("ERROR creating thread %d\n",rc);
    return -1;
  }
  while(true){
  }
 // getch();
  endwin();
 }
