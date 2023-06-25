#include <stdio.h>
#include <stdlib.h>
#include <zip.h>

#include "./errors.h"

void handle_error(int error_number) {
  if (error_number == 0) {
    return;
  }
  zip_error_t error;
  zip_error_init_with_code(&error, error_number);
  fprintf(stderr, "Exiting with error: %s\n", zip_error_strerror(&error));
  zip_error_fini(&error);
  exit(-1);
}
