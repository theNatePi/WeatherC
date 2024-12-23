#include "include/helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <lgpio.h>

int LEDS[6] = {15, 14, 17, 4, 3, 2};

// API Helpers

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

// GPIO Helpers

int updateLeds(double current[6], double history[6]) {
  for (int i = 0; i < 6; i++) {
    if (current[i] > 0) {
      lgGpioWrite(handle, LEDS[i], 1);
    } else {
      lgGpioWrite(handle, LEDS[i], 0);
    }
  }
  return 0;
}
