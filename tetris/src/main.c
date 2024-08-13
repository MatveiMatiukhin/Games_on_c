#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "tetris.h"
#include <unistd.h> 
#include <ncurses.h>

TetBlock tet_templates[] = {
    0,0,1,0,0,
    0,0,1,0,0,
    0,0,1,0,0,
    0,0,1,0,0,
    0,0,1,0,0,

    0,0,0,0,0,
    0,0,1,0,0,
    0,1,1,1,0,
    0,0,0,0,0,
    0,0,0,0,0,

    0,0,0,0,0,
    0,0,1,1,0,
    0,0,1,0,0,
    0,0,1,0,0,
    0,0,0,0,0,

    0,0,0,0,0,
    0,1,1,0,0,
    0,0,1,0,0,
    0,0,1,0,0,
    0,0,0,0,0,

    0,0,0,0,0,
    0,0,1,1,0,
    0,1,1,0,0,
    0,0,0,0,0,
    0,0,0,0,0,

    0,0,0,0,0,
    0,1,1,0,0,
    0,0,1,1,0,
    0,0,0,0,0,
    0,0,0,0,0,
};

void printTetGame(TetGame* tetg){
    TetField* tf = tetg->field;
    TetFigure* t = tetg->figure;
    for(int i = 0; i < tf->height;i++){
        for(int j = 0; j < tf->width; j++){
            int sym = 1;
            if(tf->blocks[i*tf->width+j].b!=0)
            sym = 2;
            else{
                int x = j - t->x;
                int y = i - t->y;
                if(x>=0 && x<t->size && y>=0 && y<t->size )
                    if(t->blocks[y*t->size+x].b!=0)
                    sym = 2;
            }
            attron(COLOR_PAIR(sym));
            mvaddch(i, j, ' ');
            attroff(COLOR_PAIR(sym));
        }
    }
}

int main(int argc, char* argv[]){
    struct timespec sp_start, sp_end, ts1, ts2;

    initscr();
    start_color();
    init_pair(1, COLOR_BLACK, COLOR_GREEN);
    init_pair(2, COLOR_BLACK, COLOR_WHITE);
    cbreak();
    noecho();
    nodelay(stdscr, TRUE);
    scrollok(stdscr, TRUE);
    TetGame* tetg = createTetGame(35,  30,  5,  6, tet_templates);
    
    int make_des = rand() % 30;
    //int make_des_left = rand() % 30;
    
    TetPlayer player;
    player.action = TET_PLAYER_NOP;
    tetg->player = &player;
    dropNewFigure(tetg);
    while(tetg->playing != TET_GAMEOVER){
        clock_gettime(CLOCK_MONOTONIC, &sp_start);
        int ch = getch();
        switch(ch){
            case ERR:
                player.action = TET_PLAYER_NOP;
                break;
            case 'w':
                player.action = TET_PLAYER_UP;
                break;
            case 'a':
                player.action = TET_PLAYER_LEFT;
                break;
            case 'd':
                player.action = TET_PLAYER_RIGHT;
                break;
            case 's':
                player.action = TET_PLAYER_DOWN;
                break;
            default:
                player.action = TET_PLAYER_NOP;
                break;
        }
        // if(make_des_left <= 0 ){
        //     make_des_left = rand () % 30;
        //     player.action = rand() % 5;
        // }
        calculateTet(tetg);
        printTetGame(tetg);
        //make_des_left--;
        clock_gettime(CLOCK_MONOTONIC, &sp_end);
        ts2.tv_sec = 0;
    ts2.tv_nsec = 33000000 - (sp_end.tv_nsec - sp_start.tv_nsec);
    if (ts2.tv_nsec > 0) {
    nanosleep(&ts2, &ts1);
    }
}
    freeTetGame(tetg);
    return 0;
}