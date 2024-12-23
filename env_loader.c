#include "include/env_loader.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *_checkLine(char *line, char *variable) {
  char *value = strtok(line, "=");


  // Trim whitespace
  while (value[strlen(value) - 1] == ' ') {
    value[strlen(value) - 1] = '\0';
  }
  while (value[0] == ' ') {
    char *tmp = malloc(strlen(value) - 1);
    strcpy(tmp, value+1);
    strcpy(value, tmp);
    free(tmp);
  }

  if (strcmp(value, variable) == 0) {
    value = strtok(NULL, "="); // Get after the =
    value = strtok(value, "\""); // Get before the "
    value = strtok(NULL, "\""); // Get after the "
    return value;
  }
  return NULL;
}

int loadEnv(char *variable, char **value, int value_len, char *file_path) {
  int result = -1;

  FILE *file = fopen(file_path, "r");
  if (file == NULL) {
    fprintf(stderr, "Failed to open file %s\n", file_path);
    return result;
  }

  char *line = malloc(LINE_SIZE * sizeof(char));
  line = fgets(line, LINE_SIZE, file);

  char *_value = NULL;
  while (line != NULL) {
    _value = _checkLine(line, variable);
    if (_value != NULL) {
      strncpy(*value, _value, value_len);
      result = 0;
      break;
    }
    line = fgets(line, LINE_SIZE, file);
  }

  free(line);
  fclose(file);

  return result;
}
