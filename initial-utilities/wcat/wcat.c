#include <stdio.h>
#include <stdlib.h>

int main(int argc,char* argv[]) {

    //open the file
    char in[100];
    FILE *input;
    for (int i=1;i<argc;i++) {
        input = fopen(argv[i], "r");
        if (input == NULL) {
            printf("wcat: cannot open file\n");
            exit(1);
        }
        while (fgets(in, 100, input) != NULL)
            printf("%s", in);
        fclose(input);
    }
    return 0;
}
