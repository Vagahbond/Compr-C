#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zip.h>

#include "tui/tui.h"

void handle_error(int error_number) {
  if (error_number == 0) {
    printf("No errors occured !");
    return;
  }
  zip_error_t error;
  zip_error_init_with_code(&error, error_number);
  fprintf(stderr, "Error occured manipulating zip file: %s\n",
          zip_error_strerror(&error));
  zip_error_fini(&error);
  exit(-1);
}

int main(int arc, char **argv) {

  char *filename = argv[1];

  printf("Opening file using Libzip version %s\n", zip_libzip_version());

  int errors;
  zip_t *file;

  if ((file = zip_open(filename, ZIP_CHECKCONS, &errors)) == NULL) {
    handle_error(errors);
  }

  zip_int64_t nb_files = zip_get_num_entries(file, 0);

  char **files = malloc(sizeof(char *) * nb_files);
  for (int i = 0; i < nb_files; ++i) {
    const char *file_name = zip_get_name(file, i, 0);

    files[i] = malloc(sizeof(char) * (strlen(file_name) + 1));

    strcpy(files[i], file_name);
  }

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
    erase();
    draw_header("Welcome to the zip utility.");
    draw_list_window("List of files in archives :", files, nb_files,
                     selected_index);
    refresh();
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

  handle_error(zip_close(file));

   refresh();

  getch();

*/
  return 0;
}
