#ifndef REQUESTS_H
#define REQUESTS_H

#define MAX_RESPONSE_SIZE 4096
#define MAX_REQUEST_SIZE 1024

int get(const char *url, char *path, char **response);

#endif //REQUESTS_H
