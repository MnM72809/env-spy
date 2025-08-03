#include "env_logic.h"
#include "windows.h"
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
// #include "main.c"

extern AppWindows *windowsPtr;

/*
 * TODO: Implement environment variable loading logic.
 *
 * Plan:
 * 1.  Define Data Structures:
 *     - Create a struct `EnvironmentVariable` to hold a single key-value pair
 * (char *key, char *value).
 *     - Create a struct `EnvironmentList` to act as a dynamic array manager for
 * the variables. It should contain:
 *         - `EnvironmentVariable *variables`: A pointer to the array of
 * variables.
 *         - `int count`: The current number of variables stored.
 *         - `int capacity`: The allocated capacity of the array.
 *
 * 2.  Create a `load_environment_variables()` function:
 *     - This function will be responsible for populating the `EnvironmentList`.
 *     - It will iterate through the `environ` global variable (from
 * <unistd.h>), which is a NULL-terminated array of "KEY=VALUE" strings.
 *     - For each string, it must:
 *       a. Parse the string to find the '=' delimiter.
 *       b. Allocate new memory for the key and the value separately. `strdup()`
 * is ideal for this. (This is critical because we need to store them as two
 * independent strings). c. Add the new `EnvironmentVariable` to our dynamic
 * list. d. If `count` reaches `capacity`, use `realloc()` to double the array's
 * capacity.
 *
 * 3.  Create a `free_environment_list()` function:
 *     - This function is essential for preventing memory leaks.
 *     - It must loop through every variable in the list and:
 *       a. `free()` the `key` string.
 *       b. `free()` the `value` string.
 *     - After freeing all the strings, it must `free()` the `variables` array
 * itself.
 */

void load_envvarlist(EnvVarList *list) {
    extern char **environ;

    // Parse the array
    for (char **env = environ; *env != NULL; env++) {
        char *current_var_string = *env;
        /*wprintw(windowsPtr->left_pane_win, "TEST: %s\n",
         * current_var_string);*/
        /*printf("TEST printf: %s\n", current_var_string);*/
        /*wrefresh(windowsPtr->left_pane_win);*/

        EnvVar var = parse_var(*env);
        add_to_list(list, &var);
    }
}

EnvVar parse_var(char *env) {
    EnvVar tmp = {"keytest", "valuetest"};
    return tmp;
}

bool add_to_list(EnvVarList *list, EnvVar *var) {
    if (list->count < 0)
        return false;
    if (list->count >= list->capacity) {
        list->capacity *= 2;
        // Reallocate memory
        EnvVar *new_vars = realloc(list->vars, list->capacity * sizeof(EnvVar));
        if (!new_vars)
            return false;
        for (int i = list->count; i < list->capacity; ++i) {
            new_vars[i].key = NULL;
            new_vars[i].value = NULL;
        }
        list->vars = new_vars;
    }

    EnvVar *entry = &list->vars[list->count];

    if (entry->key)
        free(entry->key);
    entry->key = strdup(var->key);
    if (!entry->key)
        return false;

    if (entry->value)
        free(entry->value);
    entry->value = strdup(var->value);
    if (!entry->value)
        return false;

    list->count++;

    return true;
}
