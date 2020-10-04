#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char * argv[]){
    if (argc>3) {
        fprintf(stderr, "usage: reverse <input> <output>\n");
        exit(1);
    }
    if (argc==3&&strcmp(argv[1],argv[2])==0){
        fprintf(stderr, "reverse: input and output file must differ\n");
        exit(1);
    }

    FILE * input;
    FILE * output;
    char  stout[100]="reverse: cannot open file '";
    if (argc>1) {
        if ((input = fopen(argv[1], "r")) == NULL) {
            fprintf(stderr, "%s\n",strcat(strcat(stout,argv[1]),"'"));
            exit(1);
        }
    }
    if (argc>2) {
        if ((output = fopen(argv[2], "w")) == NULL) {
            fprintf(stderr, "%s\n",strcat(strcat(stout,argv[2]),"'"));
            exit(1);
        }
    }
    if (argc==1){
        input=stdin;
        output=stdout;
    }
    if (argc==2){
        output=input;
    }

    char *in;
    size_t len;
    int filesize;
    //check the size of the file
    fseek(input, 0L, SEEK_END);
    filesize= ftell(input);
    fseek(input, 0L, SEEK_SET);
    char * space=malloc(filesize*sizeof(char));
    while (getline(&in, &len, input) != -1) {
          strcat(space,in);
    }
    int start=filesize-1;
    int end=filesize-1;
    while (start>=0){
        end=start;
        start--;
        while(start>=0&&space[start]!='\n'){
            start--;
        }
        fwrite(&space[start+1],(end-start)*sizeof(char),1,output);
    }
    fclose(input);
    fclose(output);
}
