#include "archives.h"
#include "../errors/errors.h"
#include <stdlib.h>
#include <string.h>

dir_t *init_files_structure(zip_t *archive_handle) {
  dir_t *root = malloc(sizeof(dir_t));

  zip_int64_t nb_files = zip_get_num_entries(archive_handle, 0);

  for (int i = 0; i < nb_files; ++i) {
    const char *file_name = zip_get_name(archive_handle, i, 0);
    char delimiter[] = "/";
    char *token = strtok(file_name, delimiter);
    while (token) {
      char *current_token = malloc(strlen(token) * sizeof(char));
      if (token = strtok(NULL, " ")) == NULL) {
      }
      else {
      }
    }
  }

  return root;
}

archive_t *init_archive(char *path) {
  archive_t *archive = malloc(sizeof(archive_t));
  int errors;

  if ((archive->handle = zip_open(path, ZIP_CHECKCONS, &errors)) == NULL) {
    handle_error(errors);
  }
  archive->root = init_files_structure(archive->handle);

  char **files = malloc(sizeof(char *) * nb_files);
  return archive;
}

void destroy_archive(archive_t *archive) {
  handle_error(zip_close(archive->handle));
}
