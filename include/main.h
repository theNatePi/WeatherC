#ifndef MAIN_H
#define MAIN_H

#define ENV_PATH ".env"
#define API_URL "http://api.weatherapi.com"

double HISTORY[6];
double CURRENT[6];

char *CITIES[6] = {
    "Tokyo",
    "San Francisco",
    "Seattle",
    "New York",
    "Vancouver",
    "London"
};

void handle_sigint(int _);
void *updateThread(void* _);
int main(void);

#endif //MAIN_H
