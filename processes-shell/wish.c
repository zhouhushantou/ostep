#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    char *in;
    size_t len;
    ssize_t read;
    int Npath = 2;
    char *path[Npath];
    path[0] = "/bin/";
    path[1] = "/user/bin/";
    char *first;
    char temp[100];
    printf("wish>");
    while ((read = getline(&in, &len, stdin)) != -1) {
        char *tp;
        //parse the command
        tp = strsep(&in, "\n");
        first = strsep(&tp, " ");
        if (tp == NULL) {
            for (int i = 0; i < Npath; i++) {
                temp[0] = '\0';
                strcat(temp, path[i]);
                strcat(temp, first);
                if (access(temp, X_OK) == 0) {
                    char *argvin[] = {temp,NULL};
                    int rm = fork();
                    if (rm == 0) {
                        execv(argvin[0], argvin);
                    }
                    else {
                       wait(NULL);
                    }
                }
            }
        }
        printf("wish>");
    }
}