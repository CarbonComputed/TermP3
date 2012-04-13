#include "main_window.h"
#include <iostream>
using namespace std;

MainWindow::MainWindow(Manager& model) {
  model_ = &model;
}

void MainWindow::init(){
  initscr();
  start_color();
  assume_default_colors(COLOR_CYAN,COLOR_BLACK);
  cbreak();
  noecho();    
  keypad(stdscr, TRUE); 
  init_pair(1, COLOR_RED, COLOR_BLACK);
  init_pair(2, COLOR_CYAN, COLOR_BLACK);
  refresh();

}

void MainWindow::display(){
  clear();
  init();
  init_song_menu(model_->get_library());
  post_menu((focused)->menu);
  wrefresh((focused)->win);
  refresh();
  this->STATE = 1;
//  move(0,0);
//  deleteln();
 // refresh();
  int ch=0;
  while(ch != KEY_F(1) && STATE == 1){
    ch = getch();
    switch(ch){
      case KEY_DOWN:
        menu_driver((focused)->menu,REQ_DOWN_ITEM);
        break;
      case KEY_UP:
        menu_driver((focused)->menu,REQ_UP_ITEM);
        break;
      case 10 :
        deleteln();
       // printw(lib.at(item_index(current_item((focused)->menu))).get_path().c_str());
        refresh();
        break;
      case ((int)':'):
        char buf[80];
        int x = getcurx(stdscr);
        int y = getcury(stdscr);
        read_line(':',buf);
        string buffer;
        buffer += buf;
        handle_command(buffer);
        deleteln();
        move(y,x);
        break;
    }
    wrefresh((focused)->win);
  }
  
  STATE = 0;
   
  for(int x=0;x<wlist.size();x++){
    for(int y=0;y<wlist.at(x)->nitems;y++){
      free_item(wlist.at(x)->items[y]);
      if(choices.at(y) != NULL){
        delete choices.at(y);
      }
    }
    unpost_menu(wlist.at(x)->menu);
    free_menu(wlist.at(x)->menu);
    
  }
  
  endwin();  
}


void MainWindow::handle_command(const string buffer){
  if(buffer == ":q"){
    STATE = 0;
    return;
  }
  STATE = 1;
}


int MainWindow::read_line(char input,char *buffer){
  string buf = "";
  buf += input;
  int pos = 1;
  mvaddch(LINES-1,pos-1,':');
  move(LINES-1,pos);
  while(buf != ""){
    int ch = getch();
    switch(ch){
      case KEY_BACKSPACE:
        pos--;
        mvdelch(LINES-1,pos);
        if(pos==0){
          return OK;
        }
        buf.erase(pos);
        break;
      case '\n':
        strcpy(buffer,buf.c_str());
        return OK;
      case KEY_LEFT:
        if(pos==0){
          beep();
          break;
        }
        pos--;
        move(LINES-1,pos);
        break;
      case KEY_RIGHT:
        if(pos==(int)buf.length()){
          beep();
          break;
        }
        pos++;
        move(LINES-1,pos);
        break;
      default: 
        buf += ((char)ch);
        pos++;
        addch(ch);  
    }
   
  }
   
  return OK;
}

void MainWindow::update(int value){
  
//  cout<<model_.get_library().size()<<endl;
//
//  refresh();
  if(value == SUCCESS){
    display();
  }
  else{
    move(0,0);
    deleteln();
    printw("Scanning library... ");
    printw("%d%%",model_->get_library().get_percent_scanned());

    refresh();
  }
}

void MainWindow::init_song_menu(vector<Song>& songs){
  int nsongs = (int) songs.size();
  LSTWINDOW* menu_win = new LSTWINDOW;
  ITEM** items = (ITEM **)calloc(nsongs+1, sizeof(ITEM *));
  menu_win->items = items;
  menu_win->nitems = nsongs;
  printw("%d  ",nsongs);
  for(int i = 0; i < nsongs; ++i){
    string choice;
    stringstream out;
 //   out << i;
 //   out << " ";
    string title;
    int width=0;
    title += songs.at(i).get_title();
    title = title.substr(0,30);
    title.erase(std::remove_if(title.begin(),title.end(),InvalidChar()), title.end());
    choice += out.str();
    width = 45- (choice.length()+title.length());
    out << title << setw(width);
    out << " | ";
    string artist;
    artist += songs.at(i).get_artist();
    artist = artist.substr(0,30);
    artist.erase(std::remove_if(artist.begin(),artist.end(),InvalidChar()), artist.end());
    width = 35 -artist.length();
    out << artist << setw(width);
    out<<" | ";
    string album = songs.at(i).get_album();   
    album.erase(std::remove_if(album.begin(),album.end(),InvalidChar()), album.end());
    album = album.substr(0,30);
    width = 35 -album.length();
    out<<songs.at(i).get_album();
    choice += out.str();
    choice.erase(std::remove_if(choice.begin(),choice.end(),InvalidChar()), choice.end());
    char* cpy = new char[choice.size()+1];
    strcpy(cpy, choice.c_str());
    choices.push_back(cpy);
    items[i] = new_item(cpy," ");   
  }
  items[nsongs] = (ITEM *) NULL;
  menu_win->win = newwin(LINES-2,COLS,2,COLS/4);
  menu_win->menu = new_menu((ITEM **)items);
  printw("%d", item_count(menu_win->menu));
  set_menu_win(menu_win->menu,menu_win->win);
  set_menu_sub(menu_win->menu,derwin(menu_win->win,LINES-4,COLS ,0,0));
  set_menu_format(menu_win->menu,LINES-6,1);
  set_menu_mark(menu_win->menu,"*");
  wlist.push_back(menu_win);
  focused = menu_win;    
  menu_opts_off(menu_win->menu,O_SHOWDESC);
}

int MainWindow::get_state() const{
  return STATE;
}
