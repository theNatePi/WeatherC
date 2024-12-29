#include "include/main.h"
#include "include/env_loader.h"
#include "include/helpers.h"
#include "include/requests.h"
// #include <lgpio.h>
#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

sig_atomic_t sigint = 0;
pthread_mutex_t CURRENT_LOCK;
pthread_mutex_t HISTORY_LOCK;

int LEDS[6] = {15, 14, 17, 4, 3, 2};
int CITY_CODES[6] = {
	350473, // Portland
  // 226396, // Tokyo
  347629, // San Francisco
  351409, // Seattle
  349727, // New York
  53286,  // Vancouver
  300597  // Singapore
};

void handle_sigint(int _) { sigint = 1; }

void *updateThread(void *_) {
  char api_key[50];
  char *pKey = api_key;
  if (loadEnv("WEATHER_KEY", &pKey, ENV_PATH) < 0) {
    perror("Failed to load environment variable WEATHER_KEY");
    return NULL;
  }

  while (1) {
    for (int i = 0; i < 6; i++) {
      char buff[250];
      // Code for replacing spaces with '+'
      // for (int j = 0; j < (int)strlen(city); j++) {
      //   if (city[j] == ' ') {
      //     city[j] = '+';
      //   }
      // }
      char *path = "currentconditions/v1/%d?apikey=%s&details=true";
      snprintf(buff, 250, path, CITY_CODES[i], pKey);

      char *api_recv = malloc(10000);
      if (get(API_URL, buff, &api_recv) < 0) {
        perror("Failed to get API URL");
        free(api_recv);
        return NULL;
      }

      if (api_recv == NULL) {
        perror("API response invalid");
        free(api_recv);
        return NULL;
      }

      // TODO: Get the response code

      double prec = getPrecipitation(api_recv);
      free(api_recv);
      return NULL;

      pthread_mutex_lock(&CURRENT_LOCK);
      pthread_mutex_lock(&HISTORY_LOCK);
      if (HISTORY[i] > 0) {
        if (HISTORY[i] < 0.01) {
          HISTORY[i] = 0;
        } else {
          HISTORY[i] -= 0.01;
        }
      }
      CURRENT[i] = prec;
      HISTORY[i] += prec;
      pthread_mutex_unlock(&CURRENT_LOCK);
      pthread_mutex_unlock(&HISTORY_LOCK);
    }

    time_t rawtime;
    char buffer[80];
    time(&rawtime);
    struct tm *timeinfo = localtime(&rawtime);
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);
    printf("\r\033[K");
    printf("Last Update: %s", buffer);
    fflush(stdout);

    for (int i = 0; i < 30; i++) {
      sleep(20);
      if (sigint) {
        printf("\n");
        return NULL;
      }
    }
  }
}

int main(void) {
  signal(SIGINT, handle_sigint);

  if (pthread_mutex_init(&CURRENT_LOCK, NULL) != 0) {
    perror("Failed to initialize mutex");
    return 1;
  }
  if (pthread_mutex_init(&HISTORY_LOCK, NULL) != 0) {
    perror("Failed to initialize mutex");
    return 1;
  }

  pthread_t threadId;
  pthread_create(&threadId, NULL, updateThread, NULL);

  /*
  int handle = lgGpiochipOpen(0);
  if (handle < 0) {
    perror("Failed to open gpiochip");
    return 1;
  }

  for (int i = 0; i < 6; i++) {
    if (lgGpioClaimOutput(handle, 0, LEDS[i], 0) < 0) {
      perror("Failed to claim output");
      lgGpiochipClose(handle);
      return 1;
    }
  }
  */

  while (1) {
    if (sigint) {
      printf("\nShutting down...\nThis may take up to 10 seconds.\n");
      fflush(stdout);
      pthread_join(threadId, NULL);
      pthread_mutex_destroy(&CURRENT_LOCK);
      pthread_mutex_destroy(&HISTORY_LOCK);

      /*
      for (int i = 0; i < 6; i++) {
        lgGpioFree(handle, LEDS[i]);
      }
      lgGpiochipClose(handle);
      */

      return 0;
    }

    // update LEDs
    pthread_mutex_lock(&CURRENT_LOCK);
    pthread_mutex_lock(&HISTORY_LOCK);
    int handle = 0;
    updateLeds(CURRENT, HISTORY, handle, LEDS);
    pthread_mutex_unlock(&CURRENT_LOCK);
    pthread_mutex_unlock(&HISTORY_LOCK);
    sleep(1);
  }
}
