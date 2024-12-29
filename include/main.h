#ifndef MAIN_H
#define MAIN_H

#define ENV_PATH ".env"
#define API_URL "https://dataservice.accuweather.com"

extern int CITY_CODES[6];

double HISTORY[6];
int CURRENT[6];

void handle_sigint(int _);
void *updateThread(void* _);
int main(void);

#endif //MAIN_H
