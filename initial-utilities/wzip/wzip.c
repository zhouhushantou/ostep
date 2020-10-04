#include <stdlib.h>
#include <string.h>
#include "stdio.h"
int main(int argc,char *argv[]){
    FILE *input;
    FILE *output;
    input=fopen(argv[1],"r");
    output=fopen(argv[3],"w");
    char *in;
    if (input == NULL||output==NULL) {
        printf("wzip: cannot open file\n");
        exit(1);
    }
    size_t len;
    char start;
    int i,lens,j;
    while (getline(&in, &len, input) != -1) {
        lens=strlen(in);
        i=0;
        while(i<lens){
            start=in[i];
            j=1;
            i++;
            while(i<lens&&in[i]==start){
                i++;
                j++;
            }
            printf("%d%c",j,start);
            fwrite(&j,4,1,output);
            fwrite(&start,1,1,output);
        }
    }
    fclose(input);
    fclose(output);
    return 0;
}

