#include <ncurses.h>
#include <unistd.h>
#include <pthread.h>

#define DERELICTS_POSITION 24
unsigned short current_frame = 0, quit = 0;
const char logo1[19][36] = {
"            -#@@@@@@@@:             ",
"          -@@@@@@@@@@@#:@@@=        ",
"      *@@@@= +@@@@@@@@@ @@@@@@      ",
"    +@@@@@@@@@  @@@@@@@:+@@@@@@@    ",
"   @@@@@@@@@@@@@* :@@@@@ @@@@@@@@   ",
"  @@@@@@@@@@#-.      -@@ @@@@@@@@+  ",
" =@=     :*@             +@@@@@@ %@ ",
" @@@@@@@@@*              :@@@@=-@@@=",
"%@@@@@@@@:                @@@ %@@@@@",
"@@@@@@@% .                +- @@@@@@@",
"#@@@@@- @@                 *@@@@@@@#",
".@@@@.#@@@:               @@@@@@@@@.",
" %@= @@@@@+             -@@@%=.     ",
"   #@@@@@@@ @=            .-%@@@@@: ",
"   @@@@@@@@ *@@@- :@@@@@@@@@@@@@@-  ",
"    #@@@@@@* @@@@@@  @@@@@@@@@@@    ",
"      %@@@@@ @@@@@@@@*.*@@@@@@:     ",
"        =@@@:+@@@@@@@@@@- %=        ",
"             .@@@@@@@@@*            "};

const char logo2[19][36] = {
"           -%@@@% @@@@@@+           ",
"        %@@@@@@@@% @@@@@@@@@        ",
"     .@@@@@@@@@@@@% @@@@@@@@@:      ",
"    =. .=%@@@@@@@@@@ #@@@@@@@:@@.   ",
"  +@@@@@@@#:  .+@@@@@ #@@@@@ %@@@*  ",
" =@@@@@@@@@@@@-        *@@@#.@@@@@+ ",
" @@@@@@@@@+             -@@ @@@@@@@.",
"+@@@@@@: :               -+:@@@@@@@@",
"@@@+.-%@@@                 @@@@@@@@@",
"  %@@@@@@-                -@@@@@@@- ",
"@@@@@@@@@                 @@@@*.-@@@",
"=@@@@@@@::                =..#@@@@@%",
" @@@@@@@ @@              -@@@@@@@@@ ",
" :@@@@@ +@@@:        .#@@@@@@@@@@@: ",
"  :@@@# @@@@@=-@@@#-   .=@@@@@@@@.  ",
"    @@:#@@@@@@=:@@@@@@@@@*.   .+    ",
"      .@@@@@@@@+.@@@@@@@@@@@@@      ",
"        *@@@@@@@%.@@@@@@@@@#        ",
"           .*@@@@#:@@@@#-           "};

const char logo3[19][36] = {
"             +@@@@@@@@#-            ",
"        .@@@% *@@@@@@@@@@ #.        ",
"      %@@@@@@@* #@@@@@@@@ @@@%      ",
"    #@@@@@@@@@@@+ #@@@@@@ @@@@@*    ",
"   @@@@@@@@@@@@@@@: @@@@@ @@@@@@@   ",
"  ...........         @@@ @@@@@@@@  ",
" @@@@@@@@@@@            @ @@@@@@@@# ",
"=@@@@@@@@@                @@@@@@@=- ",
"@@@@@@@%                  @@@@@.+@@#",
"@@@@@% =@=                @@@ +@@@@%",
"%@@@ +@@@-                - =@@@@@@+",
":%.#@@@@@=                +@@@@@@@@ ",
" #@@@@@@@=              +@@@@@@@@@* ",
" .@@@@@@@= @@          =++++*++*+=  ",
"  .@@@@@@= @@@@ :@@@@@@@@@@@@@@@@   ",
"    %@@@@- @@@@@% *@@@@@@@@@@@@*    ",
"      @@@= @@@@@@@%.#@@@@@@@@@      ",
"        -. @@@@@@@@@* @@@@@-        ",
"            +@@@@@@@@@.             "};

// Colors
void colors() {
  start_color();
  // Names
  init_pair(1, COLOR_WHITE, COLOR_BLACK);
  // Active
  init_pair(2, COLOR_GREEN, COLOR_BLACK);
  // Inactive
  init_pair(3, COLOR_RED, COLOR_BLACK);
  // Boxes
  init_pair(4, COLOR_BLUE, COLOR_BLACK);
  // Logo
  init_pair(5, COLOR_CYAN, COLOR_BLACK);
  // Cursor
  init_pair(6, COLOR_WHITE, COLOR_BLACK);
}

void active_color(const unsigned short color, const unsigned short activated) {
  if (activated)
    attron(COLOR_PAIR(color));
  else 
    attroff(COLOR_PAIR(color));
}

// Names
void show_derelicts() {
  active_color(1, 1);
  attron(A_BOLD);
  mvprintw(DERELICTS_POSITION - 1, 3, "Derelicts:");
  attroff(A_BOLD);
  mvprintw(DERELICTS_POSITION, 4, "Mirad:");
  mvprintw(DERELICTS_POSITION + 1, 4, "Malenz:");
  mvprintw(DERELICTS_POSITION + 2, 4, "Bio-Beta:");
  mvprintw(DERELICTS_POSITION + 3, 4, "Alphus:");
  mvprintw(DERELICTS_POSITION + 4, 4, "Amos:");
  active_color(1, 0);
  active_color(2, 1);
  mvprintw(DERELICTS_POSITION, 11, "Online.");
  mvprintw(DERELICTS_POSITION + 1, 12, "Online.");
  mvprintw(DERELICTS_POSITION + 2, 14, "Online.");
  mvprintw(DERELICTS_POSITION + 3, 12, "Online.");
  active_color(2, 0);
  active_color(3, 1);
  attron(A_BLINK | A_BOLD);
  mvprintw(DERELICTS_POSITION + 4, 10, "Offline.");
  active_color(3, 0);
  attroff(A_BLINK | A_BOLD);
}

void show_power () {
   active_color(1, 1);
   attron(A_BOLD);
   mvprintw(DERELICTS_POSITION + 7, 3, "Linus Infinus Status:");
   attroff(A_BOLD);
   mvprintw(DERELICTS_POSITION + 8, 4, "Energy nodes:");
   mvprintw(DERELICTS_POSITION + 9, 4, "Energy Days Left:");
   mvprintw(DERELICTS_POSITION + 10, 4, "Oxygen Days Left:");
   active_color(1, 0);
   active_color(2, 1);
   mvprintw(DERELICTS_POSITION + 8, 18, "7");
   mvprintw(DERELICTS_POSITION + 9, 22, "14");
   active_color(2, 0);
   active_color(3, 1);
   attron(A_BOLD | A_BLINK);
   mvprintw(DERELICTS_POSITION + 10, 22, "2");
   attroff(A_BOLD | A_BLINK);
   active_color(3, 0);
}

void show_earth() {
  active_color(1, 1);
  attron(A_BOLD);
  mvprintw(DERELICTS_POSITION - 1, 25, "Signals from Earth:");
  attroff(A_BOLD);
  mvprintw(DERELICTS_POSITION, 26, "Connection:");
  mvprintw(DERELICTS_POSITION + 1, 26, "Messages:");
  active_color(1, 0);
  active_color(3, 1);
  attron(A_BLINK | A_BOLD);
  mvprintw(DERELICTS_POSITION, 38, "Failed.");
  mvprintw(DERELICTS_POSITION + 1, 36, "None.");
  attroff(A_BLINK | A_BOLD);
  active_color(3, 0);
}

void draw_boxes() {
  // Info
  // Largo, ancho, posy, posx
  WINDOW *info_win = newwin(17, 47, 21, 0);
  wattron(info_win, COLOR_PAIR(4));
  box(info_win, 0, 0);
  wrefresh(info_win);
  wattroff(info_win, COLOR_PAIR(4));
  delwin(info_win);

  // Logo
  WINDOW *logo_win = newwin(21, 47, 0, 0);
  wattron(logo_win, COLOR_PAIR(4));
  box(logo_win, 0, 0);
  wrefresh(logo_win);
  wattroff(logo_win, COLOR_PAIR(4));
  delwin(logo_win);

  // Terminal
  WINDOW *term_win = newwin(38, 88, 0, 48);
  wattron(term_win, COLOR_PAIR(4));
  box(term_win, 0, 0);
  wrefresh(term_win);
  wattroff(term_win, COLOR_PAIR(4));
  delwin(term_win);
}

void *draw_logo(void *vargp) {
  while (!quit) {
    for (unsigned short y = 0; y != 19; y++) {
      for (unsigned short x = 0; x != 36; x++) {
        mvaddch(y + 1, x + 4, ' ');
      }
    }
    sleep(1);
    active_color(5, 1);
    char line[36];
    for (unsigned short y = 0; y != 19; y++) {
      if (current_frame == 0)
        sprintf(line, "%s", logo1[y]);
      else if (current_frame == 1)
        sprintf(line, "%s", logo2[y]);
      else if (current_frame == 2)
        sprintf(line, "%s", logo3[y]);
      for (unsigned short x = 0; x != 36; x++)
        if (line[x] != '\0')
          mvaddch(y + 1, x + 4, line[x]);
    }
    active_color(5, 0);
    current_frame++;
    if (current_frame == 3)
      current_frame = 0;
    refresh();
  }
  return NULL;  
}

int main() {
  initscr();
  noecho();
  curs_set(FALSE);
  colors();
  unsigned short key = 0;
  
  // Hilo
  pthread_t thread_id;
  pthread_create(&thread_id, NULL, draw_logo, NULL);
    
  while (!quit) {
    refresh();
    active_color(1, 1);
    attron(A_BOLD);
    mvaddch(1, 50, '>');
    active_color(1, 0);
    attroff(A_BOLD);
    active_color(6, 1);
    attron(A_BLINK);
    mvaddch(1, 52, '_');
    active_color(6, 0);
    attroff(A_BLINK);
    draw_boxes();
    show_derelicts();
    show_power();
    show_earth();
    refresh();
    key = getch();
    if (key == 10)
      quit = 1;
  }
  endwin();
  return 0;
}
