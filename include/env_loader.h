#ifndef ENV_LOADER_H
#define ENV_LOADER_H

#define LINE_SIZE 1024

char *_checkLine(char *line, char *variable);
int loadEnv(char *variable, char **value, char *file_path);

#endif //ENV_LOADER_H
