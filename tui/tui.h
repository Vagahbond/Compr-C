#include <zip.h>

#define PADDING 1

enum Page { EXPLORER, READER };
void draw_list_window(char *header, char **elements, size_t nb_elements,
                      size_t selected_element);
void ls(zip_stat_t *entries, int nb_files);
void draw_rectangle(int x, int y, int width, int height);
void draw_window_frame();
void draw_header(char *content);
