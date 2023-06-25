#include "./tui.h"
#include <ncurses.h>
#include <stdint.h>

void draw_rectangle(int x, int y, int width, int height) {
  int x2 = x + width;
  int y2 = y + height;

  mvhline(y, x, 0, x2 - x);
  mvhline(y2, x, 0, x2 - x);
  mvvline(y, x, 0, y2 - y);
  mvvline(y, x2, 0, y2 - y);
  mvaddch(y, x, ACS_ULCORNER);
  mvaddch(y2, x, ACS_LLCORNER);
  mvaddch(y, x2, ACS_URCORNER);
  mvaddch(y2, x2, ACS_LRCORNER);
}

void draw_header(char *content) {
  int win_height, win_width;
  getmaxyx(stdscr, win_height, win_width);

  draw_rectangle(0, 0, win_width - 1, (2 * PADDING + 2));

  mvaddstr(1 + PADDING, 1 + PADDING, content);
}

void draw_window_frame(int *width, int *height) {
  int win_height, win_width;
  getmaxyx(stdscr, win_height, win_width);
  int header_bottom = PADDING * 2 + 3;
  int window_bottom = win_height - (header_bottom + 1);

  *width = win_width - 1 - PADDING * 2;
  *height = win_height - 2 - header_bottom;
  draw_rectangle(0, header_bottom, win_width - 1, window_bottom);
}

void draw_list_window(char *header, char **elements, size_t nb_elements,
                      size_t selected_element) {
  int height, width;

  draw_window_frame(&width, &height);
  int window_top = PADDING * 2 + 4;
  int nb_max_elements = height - PADDING * 2 - 2;

  mvaddstr(window_top + PADDING, PADDING + 1, header);

  for (size_t i = 0; i < nb_elements && i < nb_max_elements; ++i) {
    int current_line = window_top + 2 + PADDING + i;

    if (i == selected_element) {
      attron(COLOR_PAIR(1));
      mvaddch(current_line, PADDING + 1, '>');
      mvaddstr(current_line, PADDING + 2, elements[i]);
      attroff(COLOR_PAIR(1));

    } else {
      mvaddstr(current_line, PADDING + 1, elements[i]);
    }
  }
}
