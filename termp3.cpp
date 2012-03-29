#include <iostream>
using namespace std;

#include "main_window.h"
#include "manager.h"

int main(int argc, char* argv[]){
  Manager music_manager("Kevin");
  music_manager.get_library().add_search_path("/home/kevin/Music");
  music_manager.get_library().scan();
  MainWindow main_window(music_manager);
  music_manager.add_observer(main_window);


}
