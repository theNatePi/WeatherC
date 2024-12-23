#include "include/main.h"
#include "include/env_loader.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  char *key;
  int result = loadEnv("WEATHER_KEY", &key, ".env");
  printf("%s\n", key);
  free(key);
  return 0;
}
