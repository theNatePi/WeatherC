#ifndef HELPERS_H
#define HELPERS_H

#define NO_RAIN 0
#define LOW_RAIN 20
#define MED_RAIN 50
#define HIGH_RAIN 100

double getPrecipitation(char *response);
int updateLeds(double current[6], double history[6], int handle, int leds[6]);

#endif // HELPERS_H
