#include <ncurses.h>
#include <stdio.h>

void evolution(int earth[][80], int w, int h);
void draw(int earth[][80], int w, int h);
void init();
void finish();
void input_1(int earth[][80], int w, int h);
void input_2(int earth[][80], int w, int h);
int logic(int x, int y, int earth[][80], int w, int h);

int main() {
    int flag = 0;
    int x = 0;
    char ch = 0;
    int speed = 100;                    // скорость
    int w = 80;                         // длина
    int h = 25;                         // высота
    int earth[h][w];                    // матрица
    printf("Введите режим работы:\n");  //Вариации ввода
    printf("1, если считываете из stdin\n");
    printf("2, если считываете из файла\n");
    printf("Если введено другое число, то случайная генерация\n");
    if (scanf("%d", &x) != 1) {
        printf("Ошибка");
    } else {
        if (x == 1) {
            input_1(earth, w, h);
        }
        if (x == 2) {
            input_2(earth, w, h);
        } else {
            printf("Ошибка выбора режима");
        }
    }
    init();
    while ((ch != 'q') && (ch != 'Q')) {  // основной цикл программы перед нажатием на триггер выхода (q, Q)
        clear();                          // очитска cmd
        napms(speed);
        draw(earth, w, h);
        ch = getch();  // считывание кнопок
        evolution(earth, w, h);
        if ((ch == 'w') || (ch == 'W')) {  // контроль скорости (вверх)
            speed -= 10;
        }
        if ((ch == 's') || (ch == 'S')) {  // контроль скорости (вниз)
            speed += 10;
        }
    }
    finish();
    return flag;
}
void input_1(int earth[][80], int w, int h) {  // ввод второго варианта файла
    printf("Не забудь, матрица должна состоять из 1 и 0\n");
    printf("Введите матрицу:\n");
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if (scanf("%d", &earth[i][j]) != 1) {
                printf("Ошибка ввода. Пожалуйста, введите число.n");
            }
        }
    }
}

void input_2(int earth[][80], int w, int h) {  // ввод второго варианта файла
    FILE *f;
    char file[50];
    printf("Введите имя файла в формате txt*.txt:\n");
    scanf("%49s", file);
    f = fopen(file, "r");
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            fscanf(f, "%d", &earth[y][x]);
        }
    }
    fclose(f);
}
void evolution(int earth[][80], int w, int h) {  // функция создания жизн
    int new[h][w];                 // второй массив создания новой жизни
    for (int y = 0; y < h; y++) {  // цикл пробега по матрице
        for (int x = 0; x < w; x++) {
            int lives = logic(x, y, earth, w, h);

            new[y][x] =
                (lives == 3 ||
                 (lives == 2 &&
                  earth[y][x] != 0));  // если число жизней == 3 или число жизней == 2 и элемент не равен
                                       // NULL, то новый элемент = 1, если неверно, новый элемент = 0;
        }
    }

    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {  // скопированный цикл
            earth[y][x] = new[y][x];
        }
    }
}

void draw(int earth[][80], int w,
          int h) {  // цикл для печати #, если в stdin 1, иначе печатать пробел
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
        int ASCII = 7;
        char cASCII = (char)ASCII;
            printw(earth[y][x] ? "%c" : " ", cASCII);
        }
        printw("\n");
    }
}

void init() {
    initscr();  //  Функция библиотеки curses. Инициализирует все функции-флаги
                //  библиотеки curses
    savetty();  //  Функция библиотеки curses. Сохраняет первичные настройки
                //  терминала
    cbreak();  //  Функция библиотеки curses. Благодаря ей не нужно нажимать enter
               //  при вводе переменной
    noecho();  //  Функция библиотеки curses. Убирает введенное значение с
               //  терминала
    timeout(0);  //  Функция библиотеки curses. Не блокирующее чтение переменной
    curs_set(0);  //  Функция библиотеки curses. Убирает курсор
}

void finish() {
    curs_set(1);  //  Функция библиотеки curses. Возвращает курсор
    refresh();    //  Функция библиотеки curses. обновляет терминал
    resetty();  //  Функция библиотеки curses. Возвращает исходные настройки
                //  терминала
    endwin();  //  Функция библиотеки curses. Заканчивает работу библиотки ncurses
}
int logic(int x, int y, int earth[][80], int w, int h) {
    int lives = 0;                             // подсчет кол-ва живых клеток в 3x3
    for (int yd = y - 1; yd <= y + 1; yd++) {  // цикл для прохождения небольшой матрицы 3x3
        for (int xd = x - 1; xd <= x + 1; xd++) {
            if (earth[(yd + h) % h][(xd + w) % w] !=
                0) {  // проверка соседей в углах и на противоположной стороне
                lives++;
            }
        }
    }
    if (earth[y][x] != 0) {
        lives--;
    }
    return lives;
}