#include <ctype.h>
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// functia pentru meniu
void afisare_menu(WINDOW *menu_win, int highlight, char *alegeri[],
                  int nr_alegeri) {
    int rand_meniu, col_meniu, i;

    col_meniu = 10;
    rand_meniu = 12;

    box(menu_win, 0, 0);

    // titlu facut din stelute
    mvwprintw(menu_win, 1, 3, "%s",
              " ********     **     ****     ** ********    ****  **   **    "
              "**   **** ");
    mvwprintw(menu_win, 2, 3, "%s",
              "/**/////     ****   /**/**   /**/**/////    */// */**  **    "
              "*/*  */// *");
    mvwprintw(menu_win, 3, 3, "%s",
              "/**         **//**  /**//**  /**/**        /    /*/** **    * "
              "/* /*   /*");
    mvwprintw(menu_win, 4, 3, "%s",
              "/*******   **  //** /** //** /**/*******      *** /****    "
              "******/ **** ");
    mvwprintw(menu_win, 5, 3, "%s",
              "/**////   **********/**  //**/**/**////      *//  /**/**  "
              "/////*  */// *");
    mvwprintw(menu_win, 6, 3, "%s",
              "/**      /**//////**/**   //****/**         *     /**//**     "
              "/* /*   /*");
    mvwprintw(menu_win, 7, 3, "%s",
              "/**      /**     /**/**    //***/********  /******/** //**    "
              "/* / **** ");
    mvwprintw(menu_win, 8, 3, "%s",
              "//       //      // //      /// ////////   ////// //   //     / "
              "  ////  ");

    for (i = 0; i < nr_alegeri; i++) {
        if (highlight == i + 1) {
            wattron(menu_win, A_REVERSE);
            mvwprintw(menu_win, rand_meniu, col_meniu, "%s", alegeri[i]);
            wattroff(menu_win, A_REVERSE);
        } else {
            mvwprintw(menu_win, rand_meniu, col_meniu, "%s", alegeri[i]);
        }
        rand_meniu++;
    }
    wrefresh(menu_win);
}

// functia care preagteste jocul
// initializeaza totul cu 0 si dupa adauga 2 patrate random cu 2/4
void new_game(int tabel[4][4]) {
    int i, j;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            tabel[i][j] = 0;
        }
    }

    srand(time(NULL));
    int random_number1;
    random_number1 = rand() % 4;
    int random_number2;
    random_number2 = rand() % 4;
    int random_number3;
    random_number3 = rand();
    int random_number4;
    random_number4 = rand() % 4;
    int random_number5;
    random_number5 = rand() % 4;
    int random_number6;
    random_number6 = rand();

    tabel[random_number1][random_number2] = (random_number3 % 2) * 2 + 2;
    while (random_number4 == random_number1 ||
           random_number5 == random_number2) {
        random_number4 = rand() % 4;
        random_number5 = rand() % 4;
    }

    tabel[random_number4][random_number5] = (random_number6 % 2) * 2 + 2;
}

// functia de afisat tabelul in timpul jocului
void afisareTabel(int tabel[4][4], int scor) {
    clear();

    int i, j;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            // grid-ul in care sunt numerele
            mvprintw(i * 4, j * 7 + 5, "+-------+");
            mvprintw(i * 4 + 1, j * 7 + 5, "|      |");
            mvprintw(i * 4 + 3, j * 7 + 5, "|      |");
            mvprintw(i * 4 + 4, j * 7 + 5, "+------+");
            mvprintw(i * 4 + 2, j * 7 + 5, "|");
            mvprintw(i * 4 + 2, j * 7 + 5, "|");

            // culorile pentru fiecare valoare
            if (tabel[i][j] == 0) {
                attron(COLOR_PAIR(1));
            } else if (tabel[i][j] == 2) {
                attron(COLOR_PAIR(2));
            } else if (tabel[i][j] == 4) {
                attron(COLOR_PAIR(3));
            } else if (tabel[i][j] == 8) {
                attron(COLOR_PAIR(4));
            } else if (tabel[i][j] == 16) {
                attron(COLOR_PAIR(5));
            } else if (tabel[i][j] == 32) {
                attron(COLOR_PAIR(6));
            } else if (tabel[i][j] == 64) {
                attron(COLOR_PAIR(7));
            } else if (tabel[i][j] == 128) {
                attron(COLOR_PAIR(8));
            } else if (tabel[i][j] == 256) {
                attron(COLOR_PAIR(9));
            } else if (tabel[i][j] == 512) {
                attron(COLOR_PAIR(10));
            } else if (tabel[i][j] == 1024) {
                attron(COLOR_PAIR(11));
            } else if (tabel[i][j] == 2048) {
                attron(COLOR_PAIR(12));
            }

            mvprintw(i * 4 + 2, j * 7 + 5, "%4d",
                     tabel[i][j]);  // Afiseaza fiecare valoare la pozitia
                                    // corespunzatoare

            attroff(COLOR_PAIR(1));
            attroff(COLOR_PAIR(2));
            attroff(COLOR_PAIR(3));
            attroff(COLOR_PAIR(4));
            attroff(COLOR_PAIR(5));
            attroff(COLOR_PAIR(6));
            attroff(COLOR_PAIR(7));
            attroff(COLOR_PAIR(8));
            attroff(COLOR_PAIR(9));
            attroff(COLOR_PAIR(10));
            attroff(COLOR_PAIR(11));
            attroff(COLOR_PAIR(12));
        }
    }

    time_t currentTime;
    struct tm *localTime;

    time(&currentTime);
    localTime = localtime(&currentTime);

    mvprintw(4, 50, "ORA: %02d:%02d:%02d\n", localTime->tm_hour,
             localTime->tm_min, localTime->tm_sec);
    mvprintw(5, 50, "Scoru tau: %d", scor);
    mvprintw(6, 50, "Apasa W pt sus");
    mvprintw(7, 50, "Apasa S pt jos");
    mvprintw(8, 50, "Apasa A pt stanga");
    mvprintw(9, 50, "Apasa D pt dreapta");
    mvprintw(10, 50, "Apasa Q pt a iesi");

    refresh();  // Actualizeaza ecranul
}

// functiile pentru miscarea celulelor
int Sus(int tabel[4][4]) {
    int i, j, scor = 0;
    for (j = 0; j < 4; j++) {
        for (i = 1; i < 4; i++) {
            if (tabel[i][j] != 0) {
                int k = i - 1;
                while (k >= 0 && tabel[k][j] == 0) {
                    tabel[k][j] = tabel[k + 1][j];
                    tabel[k + 1][j] = 0;
                    k--;
                }
                if (k >= 0 && tabel[k][j] == tabel[i][j]) {
                    scor += 2 * tabel[k][j];
                    tabel[k][j] *= 2;
                    tabel[i][j] = 0;
                }
            }
        }
    }
    return scor;
}

int Jos(int tabel[4][4]) {
    int i, j, scor = 0;
    for (j = 0; j < 4; j++) {
        for (i = 2; i >= 0; i--) {
            if (tabel[i][j] != 0) {
                int k = i + 1;
                while (k < 4 && tabel[k][j] == 0) {
                    tabel[k][j] = tabel[k - 1][j];
                    tabel[k - 1][j] = 0;
                    k++;
                }
                if (k < 4 && tabel[k][j] == tabel[i][j]) {
                    scor += 2 * tabel[k][j];
                    tabel[k][j] *= 2;
                    tabel[i][j] = 0;
                }
            }
        }
    }
    return scor;
}

int Stanga(int tabel[4][4]) {
    int i, j, scor = 0;
    for (i = 0; i < 4; i++) {
        for (j = 1; j < 4; j++) {
            if (tabel[i][j] != 0) {
                int k = j - 1;
                while (k >= 0 && tabel[i][k] == 0) {
                    tabel[i][k] = tabel[i][k + 1];
                    tabel[i][k + 1] = 0;
                    k--;
                }
                if (k >= 0 && tabel[i][k] == tabel[i][j]) {
                    scor += 2 * tabel[i][k];
                    tabel[i][k] *= 2;
                    tabel[i][j] = 0;
                }
            }
        }
    }
    return scor;
}

int Dreapta(int tabel[4][4]) {
    int i, j, scor = 0;
    for (i = 0; i < 4; i++) {
        for (j = 2; j >= 0; j--) {
            if (tabel[i][j] != 0) {
                int k = j + 1;
                while (k < 4 && tabel[i][k] == 0) {
                    tabel[i][k] = tabel[i][k - 1];
                    tabel[i][k - 1] = 0;
                    k++;
                }
                if (k < 4 && tabel[i][k] == tabel[i][j]) {
                    scor += 2 * tabel[i][k];
                    tabel[i][k] *= 2;
                    tabel[i][j] = 0;
                }
            }
        }
    }
    return scor;
}

// functia care adauga pe parcursul jocului celule de 2/4 random
void adaugare_random(int tabel[4][4]) {
    int val, spatii_libere[16], cnt = 0;
    //caut cate celule au 0 si le salvez intr-un vector
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (tabel[i][j] == 0) {
                spatii_libere[cnt++] = i * 4 + j;
            }
        }
    }
    if (cnt > 0) {
        srand(time(NULL));
        //aleg din celulele cu 0 una random
        int randomu = spatii_libere[rand() % cnt];
        int randul = randomu / 4;
        int coloana = randomu % 4;
        //generare numar random
        if (rand() % 2 == 0)
            val = 2;
        else
            val = 4;
        tabel[randul][coloana] = val;
    }
}

// functia de determina daca s-a incheiat jocul
// fie ca s-a ajuns la 2048, fie ca nu mai exista mutari posibile
int game_over(int tabel[4][4]) {
    int i, j;
    //daca se gaseste un 2048, ai castigat
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            if (tabel[i][j] == 2048) return 2;
        }
    }
    //verifica daca mai sunt 0-uri pe tabla
    //daca mai sunt, inseamna ca mai sunt mutari posibile
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            if (tabel[i][j] == 0) return 0;
        }
    }
    //verific pe linii daca elementele alaturate sunt de acelasi tip
    //daca sunt inseamna ca mai exista mutari
    for (i = 0; i < 4; i++) {
        for (j = 1; j < 3; j++) {
            if (tabel[i][j] == tabel[i][j - 1] ||
                tabel[i][j] == tabel[i][j + 1])
                return 0;
        }
    }
    //verific pe coloane daca elementele alaturate sunt de acelasi tip
    //daca sunt inseamna ca mai exista mutari
    for (i = 1; i < 3; i++) {
        for (j = 0; j < 4; j++) {
            if (tabel[i][j] == tabel[i - 1][j] ||
                tabel[i][j] == tabel[i + 1][j])
                return 0;
        }
    }

    //1 inseamna ca nu mai exista mutari posibile si ca s-a terminat jocul
    return 1;
}

void start_new_game() {
    int tabel[4][4], scor = 0;

    initscr();             // Initializare ncurses
    keypad(stdscr, TRUE);  // Activeaza tastatura speciala (sageata)
    noecho();              // Nu afiseaza caracterele tastate
    curs_set(FALSE);       // Ascunde cursorul

    char comanda;
    new_game(tabel);
    afisareTabel(tabel, scor);

    while (1) {
        int x = game_over(tabel);
        comanda = wgetch(stdscr);

        if (tolower(comanda) == 'q') break;

        if (x == 0) {
            switch (tolower(comanda)) {
                case 'a':
                    scor += Stanga(tabel);
                    adaugare_random(tabel);
                    afisareTabel(tabel, scor);
                    break;
                case 'd':
                    scor += Dreapta(tabel);
                    adaugare_random(tabel);
                    afisareTabel(tabel, scor);
                    break;
                case 'w':
                    scor += Sus(tabel);
                    adaugare_random(tabel);
                    afisareTabel(tabel, scor);
                    break;
                case 's':
                    scor += Jos(tabel);
                    adaugare_random(tabel);
                    afisareTabel(tabel, scor);
                    break;
            }
        }

        if (x == 2) mvprintw(12, 50, "BRAVO SHEFULE AI CASTIGAT");

        if (x == 1) mvprintw(12, 50, "NASOL BRO AI PIERDUT");

        refresh();
    }

    clear();
    refresh();

    endwin();
}

int main(void) {

    initscr();
    clear();
    noecho();
    cbreak();

    //alegerile din meniu
    char *alegeri[] = {"New Game", "Resume", "Quit"};
    int nr_alegeri = sizeof(alegeri) / sizeof(char *);
    int highlight = 1;
    int c, ce_alegi_din_meniu = 0;

    // facem window pt input
    WINDOW *menu_win;
    menu_win = newwin(20, 78, 0, 0);
    refresh();
    // pt a fol sagetile
    keypad(menu_win, true);

    afisare_menu(menu_win, highlight, alegeri, nr_alegeri);

    refresh();

    start_color();
    init_pair(1, COLOR_BLACK, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    init_pair(3, COLOR_GREEN, COLOR_BLACK);
    init_pair(4, COLOR_YELLOW, COLOR_BLACK);
    init_pair(5, COLOR_CYAN, COLOR_BLACK);
    init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(7, COLOR_RED, COLOR_WHITE);
    init_pair(8, COLOR_GREEN, COLOR_WHITE);
    init_pair(9, COLOR_YELLOW, COLOR_WHITE);
    init_pair(10, COLOR_CYAN, COLOR_WHITE);
    init_pair(11, COLOR_MAGENTA, COLOR_WHITE);

    while (1) {
        c = wgetch(menu_win);
        switch (c) {
            case KEY_UP:
                if (highlight == 1)
                    highlight = nr_alegeri;
                else
                    highlight--;
                break;
            case KEY_DOWN:
                if (highlight == nr_alegeri)
                    highlight = 1;
                else
                    highlight++;
                break;
            case 10:  // cand apas ENTER
                ce_alegi_din_meniu = highlight;
                break;
            default:
                break;
        }

        afisare_menu(menu_win, highlight, alegeri, nr_alegeri);

        refresh();

        if (ce_alegi_din_meniu != 0) {
            switch (ce_alegi_din_meniu) {
                case 1:  // New Game
                    start_new_game();
                    break;
                case 2:  // Resume
                mvprintw(20, 5, "BROTHERE NU AM FUNCTIA ASTA INCA");
                    break;
                case 3:  // Quit
                    endwin();
                    return 0;
                default:
                    break;
            }
            ce_alegi_din_meniu = 0;  // resetez alegerea pentru a reveni la
                                     // meniu
            afisare_menu(menu_win, highlight, alegeri, nr_alegeri);
        }
    }

    refresh();
    endwin();
    return 0;
}