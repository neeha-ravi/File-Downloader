#define NUM_ARGS 3
#define _GNU_SOURCE
#define ARR_SIZE 1024

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <ctype.h>
#include <dirent.h>
#include <stdint.h>
#include <fcntl.h>
#include <math.h>
#include <sys/stat.h>
#include <curl/curl.h>
#include <curl/easy.h>

typedef struct arraylist arraylist;

struct arraylist{
    int capacity;
    int numitems;
    char ** data ;
};

void validate_args(int argc, char * argv[]);
void verify_args(char *filename, int max);
void spawn_processes(char *fname, int mproc, int procs);
void get_args(char *str, arraylist *args);
arraylist *array_list_new();
void array_list_add_to_end(arraylist *mylist, char *new);
void free_array_list(arraylist *mylist);
void print_array_list(arraylist *mylist);
void remove_trailing(char *str);
void download(arraylist *args);
pid_t spawn();
