#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

void print(int ball_x, int ball_y, int count_left, int count_right, int left_rocket, int right_rocket);
void win_left();
void win_right();
void end();
void init();
int main() {
    // флаги для победы и завершения программы
    int flag = 0;

    // счет
    int count_left = 0;
    int count_right = 0;

    // координаты ракеток
    int left_rocket = 12;
    int right_rocket = 12;

    // мяч
    int ball_x = 40;
    int ball_y = 12;
    int direction_ball_x = 1;
    int direction_ball_y = 1;
    init();

    // основной цикл программы
    while (flag == 0) {
        print(ball_x, ball_y, count_left, count_right, left_rocket, right_rocket);
        // ввод и управление ракеток
        char input;
        input = wgetch(stdscr);
        if ((input == 'a' || input == 'A') && left_rocket != 3) {
            left_rocket -= 1;
        } else if ((input == 'z' || input == 'Z') && left_rocket != 23) {
            left_rocket += 1;
        } else if ((input == 'k' || input == 'K') && right_rocket != 3) {
            right_rocket -= 1;
        } else if ((input == 'm' || input == 'M') && right_rocket != 23) {
            right_rocket += 1;
        } else if (input == 'q' || input == 'Q') {
            end();
            return 1;
        }

        //  движение мяча
        ball_x += direction_ball_x;
        ball_y += direction_ball_y;
        if (ball_x == 6 && ball_y == 24 && left_rocket == 23) {
            direction_ball_x = 1;
            direction_ball_y = -1;
        } else if (ball_x == 6 && ball_y == 2 && left_rocket == 2) {
            direction_ball_x = 1;
            direction_ball_y = 1;
        } else if (ball_x == 75 && ball_y == 24 && right_rocket == 23) {
            direction_ball_x = 1;
            direction_ball_y = -1;
        } else if (ball_x == 75 && ball_y == 2 && right_rocket == 2) {
            direction_ball_x = 1;
            direction_ball_y = -1;
        } else if (ball_y == 2 || ball_y == 24) {
            direction_ball_y = -direction_ball_y;
        } else if (ball_x == 75 && (ball_y <= right_rocket + 1 && ball_y >= right_rocket - 1)) {
            direction_ball_x = -direction_ball_x;
        } else if (ball_x == 7 && (ball_y <= left_rocket + 1 && ball_y >= left_rocket - 1)) {
            direction_ball_x = -direction_ball_x;
        } else if (ball_x == 1) {
            ball_x = 40;
            ball_y = 12;
            right_rocket = 12;
            left_rocket = 12;
            direction_ball_x = 1;
            direction_ball_y = 1;
            count_right++;
        } else if (ball_x == 80) {
            ball_x = 40;
            ball_y = 12;
            right_rocket = 12;
            left_rocket = 12;
            direction_ball_x = -1;
            direction_ball_y = 1;
            count_left++;
        }
        if (count_left == 21) {
            flag = 1;
        } else if (count_right == 21) {
            flag = 1;
        }
        napms(250);
    }
    wclear(stdscr);

    if (count_left == 21) {
        printf("Left player win");
    } else if (count_right == 21) {
        printf("Right player win");
    }
    return 0;
}

void print(int ball_x, int ball_y, int count_left, int count_right, int left_rocket, int right_rocket) {
    // размеры поля
    wclear(stdscr);
    int length = 80;
    int height = 27;

    for (int i = 1; i <= height; i++) {
        for (int j = 1; j <= length; j++) {
            if (i == 1 || i == 25 || i == 27) {  //
                printw("-");
            } else if (ball_x == j && ball_y == i) {
                printw("o");
            } else if (i == 26 && j == 35) {
                printw("%d", count_left);
            } else if (i == 26 && j == 45) {
                printw("%d", count_right);
            } else if ((j == 1 && i <= 25) || (j == 80 && i <= 25)) {  // !!!!!!!!!
                printw("#");
            } else if (j == 40 && i <= 25) {
                printw("|");
            } else if (j == 5 && (i == left_rocket || i == left_rocket + 1 || i == left_rocket - 1)) {  //
                printw("[");
            } else if (j == 76 && (i == right_rocket || i == right_rocket + 1 || i == right_rocket - 1)) {  //
                printw("]");
            } else {
                printw(" ");
            }
        }
        printw("\n");
    }
}
void init(){
    initscr();
    noecho();
    cbreak();
    curs_set(0);
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
}
void end(){
    curs_set(1);  // Возвращает курсор
    refresh();    // обновление терминала
    resetty();    // Возвращает исходные настройки терминала
    endwin(); 
}