#include "include/helpers.h"
#include "include/main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include <lgpio.h>

// API Helpers

double getPrecipitation(char *response) {
  // Get the heders
  strtok(response, "\n\n");
  printf("%s\n", response);
  // Skip all headers
  for (int i = 0; i < 10; i++) {
    strtok(NULL, "\n\n");
  }

  int index = 0;

  // Get to the JSON body
  response = strtok(NULL, "\n\n");

  printf("%s\n", response);

  // Skip through all values to get the precipitation
  char *result = strtok(response, "\r\n:,\"");
  while (strcmp(result, "HasPrecipitation") != 0) {
		result = strtok(NULL, "\r\n:,\"");
	}
	result = strtok(NULL, "\r\n:,\"");
	CURRENT[index] = strcmp(result, "true") == 0 ? 1 : 0;

	printf("%d\n", CURRENT[index]);

	while (strcmp(result, "Precip1hr") != 0) {
    result = strtok(NULL, "\r\n:,\"");
	}
	while (strcmp(result, "Metric") != 0) {
    result = strtok(NULL, "\r\n:,\"");
  }
  while (strcmp(result, "Value") != 0) {
    result = strtok(NULL, "\r\n:,\"");
  }
	result = strtok(NULL, "\r\n:,\"");
	printf("result %s\n", result);

	return 0;

  // char *result = strtok(response, ":");
  // for (int i = 0; i < 27; i++) {
  //   result = strtok(NULL, ":");
  // }
  // result = strtok(NULL, ",");
  // return atof(result);
}

// GPIO Helpers

int updateLeds(int current[6], double history[6], int handle, int leds[6]) {
  // for (int i = 0; i < 6; i++) {
  //   if (current[i] > 0) {
  //     if (current[i] > 1) {
  //       // todo: finish
  //     }
  //   	lgTxPwm(handle, leds[i], 1000, , 0 , 0);
  //   } else {
  //   	lgTxPwm(handle, leds[i], 1000, NO_RAIN, 0 , 0);
  //     lgGpioWrite(handle, leds[i], 0);
  //   }
  // }
  return 0;
}
