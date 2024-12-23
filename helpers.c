#include "include/helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <lgpio.h>

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
  int exitVal = 0;

  int handle = lgGpiochipOpen(0);
  if (handle < 0) {
    perror("Failed to open gpiochip");
    return -1;
  }

  for (int i = 0; i < 6; i++) {
    if (lgGpioClaimOutput(handle, 0, LEDS[i], 0) < 0) {
      perror("Failed to claim output");
      exitVal = -1;
      goto cleanup;
    }
  }

  for (int i = 0; i < 6; i++) {
    if (current[i] > 0) {
      lgGpioWrite(handle, LEDS[j], 1);
    } else {
      lgGpioWrite(handle, LEDS[j], 0);
    }
  }

  cleanup:
  for (i = 0; i < 6; i++) {
    lgGpioFree(handle, leds[i]);
  }
  lgGpiochipClose(handle);
  return exitVal;
}
