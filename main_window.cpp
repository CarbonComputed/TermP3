#include <curses.h>
#include <cstring>
#include <string>

using namespace std;

int read_line(char *buffer){
  string buf = ":";
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
        strcpy(buffer,buf.substr(1).c_str());
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
        if(pos==buf.length()){
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

int main(int argc, char* argv[]){
  initscr();
  cbreak();
  noecho();    
  keypad(stdscr, TRUE); 
  refresh();
  int ch=0;
  
  while(ch != KEY_F(1)){
    ch = getch();
    switch(ch){
      case KEY_UP:
        break;
      case KEY_DOWN:
        break;
      case ((int)':'):
        char buf[80];
        read_line(buf);
        deleteln();
        printw(buf);
        break;
    }
  }
 // getch();
  endwin();  
}


