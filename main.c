#include "include/main.h"
#include "include/env_loader.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  char *key = malloc(256);
  int result = loadEnv("WEATHER_KEY", &key, 256, ".env");
  printf("%s\n", key);
  free(key);
  return 0;
}
