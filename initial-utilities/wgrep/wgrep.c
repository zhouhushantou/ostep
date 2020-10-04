#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc,char* argv[]) {
    char * in;
    char buffer[100];
    size_t len=0;
    FILE *input;
    char *needle;
    ssize_t read;
    if (argc < 2) {
        printf("wgrep: searchterm [file ...]\n");
        exit(1);
    }
    needle = argv[1];
    if (argc == 2) {
        while (fgets(buffer, 100, stdin)) {
            if (strstr(buffer, needle) != NULL)
                printf("%s", buffer);
        }
    }
    //open the file
    for (int i = 2; i < argc; i++) {
        input = fopen(argv[i], "r");
        if (input == NULL) {
            printf("wgrep: cannot open file\n");
            exit(1);
        }
        while ((read=getline(&in, &len, input) )!= -1) {
            if (strstr(in, needle) != NULL)
                printf("%s", in);
        }
        fclose(input);
    }
    return 0;
}

