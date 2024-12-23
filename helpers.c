#include "include/helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

double getPrecipitation(char *response) {
  // Get the heders
  strtok(response, "\n\n");
  // Skip all headers
  for (int i = 0; i < 22; i++) {
    strtok(NULL, "\n\n");
  }

  // Get to the JSON body
  response = strtok(NULL, "\n\n");

  // Skip through all values to get the precipitation
  // Measured in mm
  char *result = strtok(response, ":");
  for (int i = 0; i < 27; i++) {
    result = strtok(NULL, ":");
  }
  result = strtok(NULL, ",");
  return atof(result);
}
