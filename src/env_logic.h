#pragma once
#include <stdbool.h>

typedef struct {
    char *key;
    char *value;
} EnvVar;

typedef struct {
    EnvVar *vars;
    int count;
    int capacity;
} EnvVarList;

void load_envvarlist(EnvVarList *list);
EnvVar parse_var(char *env);
bool add_to_list(EnvVarList *list, EnvVar *var);
void free_envvarlist(EnvVarList *list);
