#ifndef ENV_LOADER_H
#define ENV_LOADER_H

#define LINE_SIZE 1024

char *_checkLine(char *line, const char *variable);
int loadEnv(const char *variable, char **value, const char *file_path);

#endif //ENV_LOADER_H
