#include "./navigation.h"
#include "../tui/tui.h"
#include <ncurses.h>

void explorer_page(char *current_path) {
  int stop = 0;

  while (!stop) {
    //
    erase();
    draw_header("Welcome to the zip utility.");
    draw_list_window("List of files in archives :", files, nb_files,
                     selected_index);
    refresh();

    // input
  }
}
