
#include "../archives/archives.h"

enum Page { EXPLORER, READER };

typedef struct {
  enum Page current_page;
  dir_t *current_directory;
  file_t *current_file;
} router_t;

router_t *init_router(dir_t *);

void destroy_router(router_t *);

void explorer_page(router_t *);
