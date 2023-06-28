#include "./navigation.h"
#include "../tui/tui.h"
#include <ncurses.h>
#include <stdlib.h>

router_t *init_router(dir_t *root_dir) {
  router_t *router = malloc(sizeof(router_t));

  router->current_file = NULL;
  router->current_directory = root_dir;
  router->current_page = EXPLORER;

  return router;
}

void destroy_router(router_t *router) { free(router); }

void explorer_page(router_t *router) {
  int stop = 0;

  int nb_entries;

  char **entries = list_entries(router->current_directory, &nb_entries);

  int selected_index = 0;

  while (!stop) {
    erase();

    draw_header("Currently in the explorer.");
    draw_list_window("List of files in archives :", entries,
                     router->current_directory->nb_files, selected_index);

    int input = getch();

    switch (input) {
    case KEY_UP:
      selected_index =
          selected_index == 0 ? selected_index : selected_index - 1;
      break;
    case KEY_DOWN:
      selected_index = selected_index == nb_entries - 1 ? selected_index
                                                        : selected_index + 1;
      break;
    }

    refresh();
  }

  // free entries as they're malloc'd
  for (int i = 0; i < nb_entries; ++i) {
    free(entries[i]);
  }

  free(entries);
}
