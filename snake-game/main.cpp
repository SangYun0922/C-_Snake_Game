#include <fstream>
#include <ncurses.h>
#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

using namespace std;
int width = 50;
int height = 20;

struct point{
    int x;
    int y;
};

int main()
{
    int size;
    cout << "뱀의 길이를 입력해주세요(ex : 5) : " << " ";
    cin >> size;
    char data[50][20];

    WINDOW *win1;
    initscr();
    resize_term(40, 80);
    start_color();
    init_pair(1, COLOR_CYAN, COLOR_WHITE); //wall
    init_pair(2, COLOR_BLACK, COLOR_WHITE); //immune wall
    init_pair(3, COLOR_WHITE, COLOR_WHITE); //field
    init_pair(4, COLOR_YELLOW, COLOR_YELLOW); //head
    init_pair(5, COLOR_BLUE, COLOR_BLUE); //body
    init_pair(6, COLOR_YELLOW, COLOR_YELLOW); //growth
    init_pair(7, COLOR_MAGENTA, COLOR_MAGENTA); // poison
    
    border('*','*','*','*','*','*','*','*');
    mvprintw(1,1,"Whole Window");
    refresh();
    getch();
    win1 = newwin(20, 50, 2, 3);
    wbkgd(win1, COLOR_PAIR(3));
    for (int i = 0; i < width ; i++) {
        for (int j = 0; j < height ; j++) {
            if (i == 0 || i == width-1 || j == 0 || j == height-1) {
                if (((i == 0) || (i == width-1)) && ((j == 0) || (j == height-1))) {
                    wattron(win1,COLOR_PAIR(2));
                    mvwprintw(win1,j,i,"@");
                    wattroff(win1, COLOR_PAIR(2));
                } else {
                    wattron(win1,COLOR_PAIR(1));
                    mvwprintw(win1,j,i,"*");
                    wattroff(win1, COLOR_PAIR(1));
                }
            }
        }
    }
    wattron(win1,COLOR_PAIR(2));
    mvwprintw(win1, 1, 1, "Game Window");
    curs_set(0);
    //wrefresh(win1);

    int head_row = height/2-1; int head_col = width/2-1; //중앙에서 시작

    wattron(win1, COLOR_PAIR(4));
    mvwprintw(win1,head_row,head_col,"h");
    wattroff(win1, COLOR_PAIR(4));

    int body[size][2];

    for(int i=0; i<size; i++){
      body[i][0] = head_row;
      body[i][1] = head_col+i+1;

      wattron(win1,COLOR_PAIR(5));
      mvwprintw(win1,body[i][0],body[i][1],"b");
      wattroff(win1, COLOR_PAIR(5));
    }
    wrefresh(win1);

    keypad(win1, TRUE);
    nodelay(win1, TRUE);
    int key_input, direction = KEY_LEFT;
    bool game = TRUE;
    point growth;
    point poison;
    point tmp_growth;
    point tmp_poison;
    int counter = 0;

    while(game){
        if (counter == 10) {
            wattron(win1, COLOR_PAIR(3));
            mvwprintw(win1,tmp_poison.y,tmp_poison.x,"p");
            mvwprintw(win1,tmp_growth.y,tmp_growth.y,"g");
            wattroff(win1, COLOR_PAIR(3));
            
            cout << 
            
            counter = 0;
        }
        if(counter == 0) {
            growth.x=rand()%(width-2)+1;
            growth.y=rand()%(height-2)+1;
            
            poison.x =rand()%(width-2)+1;
            poison.y=rand()%(height-2)+1;

                
            wattron(win1, COLOR_PAIR(7));
            mvwprintw(win1,poison.y,poison.x,"p");
            wattroff(win1, COLOR_PAIR(7));
            wattron(win1,COLOR_PAIR(6));
            mvwprintw(win1,growth.y,growth.x,"g");
            wattroff(win1, COLOR_PAIR(6));
            
            tmp_growth.x = growth.x;
            tmp_growth.y = growth.y;
            
            tmp_poison.x = poison.x;
            tmp_poison.y = poison.y;
        }
      key_input = wgetch(win1);
      if(key_input == direction) continue;
      if(key_input == ERR) key_input = direction;

      switch(key_input)
      {
      case KEY_DOWN:
        if(direction == KEY_UP || (++head_row) == (height-1))
        game = FALSE;
        break;
      case KEY_UP:
        if(direction == KEY_DOWN || (--head_row) == 0)
        game = FALSE;
        break;
      case KEY_RIGHT:
        if(direction == KEY_LEFT || (++head_col) == (width-1))
        game = FALSE;
        break;
      case KEY_LEFT:
        if(direction == KEY_RIGHT || (--head_col) == 0)
        game = FALSE;
        break;
      
      }


      wattron(win1,COLOR_PAIR(3));
      mvwprintw(win1,body[size-1][0],body[size-1][1],"b");
      wattroff(win1, COLOR_PAIR(3));


      for(int i=size-1; i-1>-1; i--){
        if(body[i][0] == head_row && body[i][1] == head_col) {
          game = FALSE;
          break;
        }
        body[i][0] = body[i-1][0];
        body[i][1] = body[i-1][1];

        wattron(win1,COLOR_PAIR(5));
        mvwprintw(win1,body[i][0],body[i][1],"b");
        wattroff(win1, COLOR_PAIR(5));
      }


      body[0][0] = head_row;
      body[0][1] = head_col;

      wattron(win1,COLOR_PAIR(5));
      mvwprintw(win1,body[0][0],body[0][1],"b");
      wattroff(win1, COLOR_PAIR(5));


      wattron(win1, COLOR_PAIR(4));
      mvwprintw(win1,head_row,head_col,"h");
      wattroff(win1, COLOR_PAIR(4));

      wrefresh(win1);
      direction = key_input;
        counter += 1;
      usleep(300000);
    }

    getch();
    delwin(win1);
    endwin();
    return 0;
}
