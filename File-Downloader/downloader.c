#include "downloader.h"

int main(int argc, char *argv[]) {
    validate_args(argc, argv);
    char *fname = argv[1];
    int mproc = atoi(argv[2]);
    verify_args(fname, mproc);
    int procs = 0;
    spawn_processes(fname, mproc, procs);
    return 0;
}

void spawn_processes(char *fname, int mproc, int procs) {
    printf("max processes: %d \n", mproc);
    FILE *f;
    f = fopen(fname, "r");
    char *str = NULL;
    size_t n;
    int status = 3;
    while (getline(&str, &n, f) > 0) {
        procs ++;
        if ((spawn() == 0) && (procs <= mproc)) {
            printf("process starting ");
            printf("child process pid %d at line %d \n", getpid(), procs);
            arraylist *args;
            args = array_list_new();
            get_args(str, args);
            download(args);
            free_array_list(args);
        }
        else if (procs > mproc) {
            wait(&status);
            printf("process terminated at line %d \n \n", procs);
        }
        else {
            wait(&status);
            printf("process terminated at line %d \n \n", procs);
        }
    }
    fclose(f);
}

void download(arraylist *args) { // only runs the curl command
    char *fname = args -> data[0];
    char *url = args -> data[1];
    char *otag = "-o";
    char *mtag = "-m";
    char *stag = "-s";
    if (args -> numitems == 3) {
        char *time = args -> data[2];
        execlp("curl", "curl", mtag, time, otag, fname, stag, url, 0);
        perror("spec time");
    } else {
        execlp("curl", "curl", otag, fname, stag, url, 0);
        perror("no spec time");
    }
    exit(1);
}

void get_args(char *str, arraylist *args) {  // get each cmd line argument
    char *token;
    int x = 0;
    while ((token = strsep(&str, " ")) != NULL) {
        remove_trailing(token);
        array_list_add_to_end(args, token);
        x ++;
    }
}

void verify_args(char *filename, int max) { // make sure specificed file name exists
    int result;
    result = access (filename, F_OK);
    if (result == 0 && max > 0) {
        return;
    } else {
        printf("ERROR: %s doesn't exist\n",filename);
        exit(1);
    }
}

void validate_args(int argc, char * argv[]) {
    if (argc > NUM_ARGS) {
        fprintf(stderr, "usage: %s file \n", argv[0]);
        exit(1);
    }
}

arraylist *array_list_new() {
    arraylist *mylist;
    mylist = (arraylist *)malloc(sizeof(arraylist));
    mylist->capacity = 10;
    mylist->data = (char **)malloc(sizeof(char *) * mylist->capacity);
    memset(mylist -> data, '\0', sizeof(char *) * mylist->capacity);
    mylist->numitems = 0;
    return mylist;
}


void array_list_add_to_end(arraylist *mylist, char *new) {
    if (mylist -> numitems == mylist -> capacity) {
        mylist -> data = (char **) realloc (mylist -> data, sizeof(char *) * mylist -> capacity * 2);
        mylist -> capacity = (mylist -> capacity) * 2;
    }
    mylist -> data[mylist -> numitems] = new;
    (mylist -> numitems)++;
}

void free_array_list(arraylist *mylist){
    int i;
    for (i = 0; i < mylist -> capacity; i ++) {
        free(mylist -> data[i]);
    }
    free(mylist->data);
    free(mylist);
}

void print_array_list(arraylist *mylist) {
    int i;
    for (i = 0; i < mylist -> numitems; i ++) {
        printf ("%d: %s\n", i, mylist -> data[i]);
    }
}

void remove_trailing(char *str) { // remove trailing whitespaces
    ssize_t len = strlen(str);
    int i;
    for (i = 0; i < len; i ++) {
        char c = str[i];
        if (c == '\n') {
            str[i] = '\0';
        }
    }
}

pid_t spawn() {
    pid_t pid;
    pid = fork();
    if ((pid < 0)) {
        perror(" ");
        exit(1);
    }
    else {
        return pid;
    }
} 