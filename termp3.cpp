#include <iostream>
#include <ncurses/curses.h>
#include <pthread.h>
using namespace std;

#include "main_window.h"
#include "manager.h"
#include "defines.h"


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
  music_manager.get_playqueue().add_observer(main_window);
  music_manager.get_library().add_search_path("/home/kevin/Music/Kanye West");
  music_manager.get_library().add_search_path("/home/kevin/Music/Saved");
  music_manager.get_library().add_search_path("./");
 // music_manager.get_library().add_search_path("/home/kevin/Music");
  main_window.init();
  pthread_t scanner;
  int rc = pthread_create(&scanner,NULL,scan_library,(void*) &music_manager);
  if(rc){
    getch();
    printw("ERROR creating thread %d\n",rc);
    return -1;
  }
  while(main_window.get_state() != 0){
    main_window.update(REFRESH);
    if(music_manager.get_playqueue().current_is_finished()){
      music_manager.get_playqueue().next();
    }
    sleep(1);
  }
  //cout<<"Exiting"<<endl;
  sleep(0.5);
  pthread_exit(NULL);
 // getch();
 // endwin();
 }
