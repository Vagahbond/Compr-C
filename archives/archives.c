#include "archives.h"
#include "../errors/errors.h"
#include <stdlib.h>
#include <string.h>
file_t *init_file(char *name) {
  file_t *res = malloc(sizeof(file_t));

  res->name = malloc(sizeof(char) * strlen(name) + 1);
  strcpy(res->name, name);

  return res;
}

void destroy_file(file_t *file) {
  free(file->name);
  free(file);
}

dir_t *init_dir(char *name) {
  dir_t *res = malloc(sizeof(dir_t));

  res->name = malloc(sizeof(char) * strlen(name) + 1);
  strcpy(res->name, name);

  res->dirs = malloc(sizeof(dir_t));
  res->nb_dirs = 0;

  res->files = malloc(sizeof(file_t));
  res->nb_files = 0;

  return res;
}

void destroy_dir(dir_t *dir) {
  for (int i = 0; i < dir->nb_files; ++i) {
    destroy_file(dir->files + i);
  }

  free(dir->files);

  for (int i = 0; i < dir->nb_dirs; ++i) {
    destroy_dir(dir->dirs + i);
  }

  free(dir->dirs);

  free(dir->name);

  free(dir);
}
// TODO: memcpy !
void add_file_to_dir(char *name, dir_t *dir) {
  dir->files = realloc(dir->files, sizeof(file_t) * (++dir->nb_files));
  dir->files[dir->nb_files - 1] = init_file(name);
}

void add_dir_to_dir(char *name, dir_t *dir) {
  dir->dirs = realloc(dir->dirs, sizeof(dir_t) * (++dir->nb_dirs));
  dir->dirs[dir->nb_dirs - 1] = init_dir(name);
}

dir_t *init_files_structure(zip_t *archive_handle) {
  dir_t *root = init_dir("/");

  zip_int64_t nb_files = zip_get_num_entries(archive_handle, 0);

  // TODO: remove useless copies
  for (int i = 0; i < nb_files; ++i) {
    const char *file_name = zip_get_name(archive_handle, i, 0);
    char *delimiter = malloc(sizeof(char) * 2);
    char *file_name_copy = malloc(sizeof(char) * strlen(file_name) + 1);
    strcpy(delimiter, "/");
    strcpy(file_name_copy, file_name);

    char *token = strtok(file_name_copy, delimiter);
    char *new_token;
    dir_t *cur_dir = root;
    while ((new_token = strtok(NULL, " ")) == NULL) {
      add_dir_to_dir(token, cur_dir);
      cur_dir = cur_dir->dirs + (cur_dir->nb_files - 1);
      token = new_token;
    }

    add_file_to_dir(token, cur_dir);

    free(delimiter);
    free(file_name_copy);
  }

  return root;
}

char **list_entries(dir_t *dir, int *nb_entries) {
  (*nb_entries) = dir->nb_dirs + dir->nb_files;
  char **entries = malloc(sizeof(char *) * (*nb_entries));

  for (int i = 0; i < dir->nb_dirs; ++i) {
    entries[i] = malloc(sizeof(char) * strlen(dir->dirs[i].name) + 1);
  }

  for (int i = 0; i < dir->nb_files; ++i) {
    entries[i] = malloc(sizeof(char) * strlen(dir->files[i].name) + 1);
  }

  return entries;
}

archive_t *init_archive(char *path) {
  archive_t *archive = malloc(sizeof(archive_t));
  int errors;

  if ((archive->handle = zip_open(path, ZIP_CHECKCONS, &errors)) == NULL) {
    handle_error(errors);
  }
  archive->root = init_files_structure(archive->handle);

  return archive;
}

void destroy_archive(archive_t *archive) {
  destroy_dir(archive->root);
  handle_error(zip_close(archive->handle));

  free(archive);
}
