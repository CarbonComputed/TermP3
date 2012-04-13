#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#if defined(__CYGWIN__)
#include <ncurses/curses.h>
#include <ncurses/menu.h>
#else
#include <curses.h>
#include <curses.h>
#endif

#include <iomanip>
#include <sstream>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>
#include <stdlib.h>
#include <algorithm>
#include <cerrno>

#include "manager.h"
#include "observer.h"

using namespace std;

class LSTWINDOW {
  public:
    WINDOW* win;
    MENU *menu;
    ITEM** items;
    int nitems;
};

struct InvalidChar
{
    bool operator()(char c) const {
        return !isprint((unsigned)c);
    }
};

class MainWindow: public Observer{

Manager* model_;

vector<char*> choices;
vector<LSTWINDOW*> wlist;
LSTWINDOW* focused;
int STATE;

int read_line(char input, char* buffer);
void init_song_menu(vector <Song>& songs);
void handle_command(const string buffer);

public:
  MainWindow(Manager& model);
  void init();
  void display();
  void update(int value);
  int get_state() const;
};


#endif

