#include <zip.h>

typedef struct {
  char *name;
} file_t;

typedef struct dir {
  char *name;
  struct dir *dirs;
  size_t nb_dir;
  file_t *files;
  size_t nb_files;
} dir_t;

typedef struct {
  zip_t *handle;
  dir_t *root;
} archive_t;

archive_t *init_archive(char *path);

void destroy_archive(archive_t *archive);
