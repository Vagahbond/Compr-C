#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zip.h>

#include "tui/tui.h"

int main(int arc, char **argv) {

  char *filename = argv[1];

  printf("Opening file using Libzip version %s\n", zip_libzip_version());

  initscr();
  start_color();
  init_pair(1, COLOR_GREEN, COLOR_BLACK);
  noecho();
  keypad(stdscr, TRUE);

  int exit = 0;

  int selected_index = 0;

  // Main loop !
  while (!exit) {
    // manage display
    // manage input
    int input = getch();

    switch (input) {
    case KEY_UP:
      selected_index =
          selected_index == 0 ? selected_index : selected_index - 1;
      break;
    case KEY_DOWN:
      selected_index =
          selected_index == nb_files - 1 ? selected_index : selected_index + 1;
      break;
    }

    // exit = input == 'q' || input == 'Q' || input == 27;
  }

  endwin();

  /*

  addstr("-----------------\n| Zip Manipulation Program |\n| and actueal "
         "ncurses flex  |\n-----------------\n\n");
  refresh();
  int row = 5;
  int col = 0;

  curs_set(0);

  for (char c = 65; c <= 90; c++) {
    move(row++, col++);
    addch(c);
    refresh();
    napms(100);
  }

  row = 5;
  col = 3;

  for (char c = 97; c <= 122; c++) {
    mvaddch(row++, col++, c);
    refresh();
    napms(100);
  }

  curs_set(1);

  addch('\n');


   refresh();

  getch();

*/
  return 0;
}
