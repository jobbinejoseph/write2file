#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "writenew.h"

int main_fun(int argc, char *argv){
        char *argmv[] = {"./a.out",argv};
        return(main(argc,argmv));
}



int main(int argc , char *argv[]){
        const char *filepath;
        char buffer[4] = { 0 };
        int bytesize = 4;
        FILE *ptr_myfile;
        if(argc!=2){
                fprintf(stderr, "Usage : Program <space> file");
                fprintf(stderr, " Eg: ./binary file.txt\n");
        }

        filepath = argv[1];
        ptr_myfile = fopen(filepath,"wb");
        if(!ptr_myfile){
                printf("Cannot open file");
                return (1);
        }

        fprintf(stderr,"Press ctrl+D once done\n");
        if(!freopen(NULL,"rb",stdin)){
            fprintf(stderr,"Can't open the file");
            return (4);
        }
        while(!feof(stdin)){
                fread(buffer,bytesize,1,stdin);
                fwrite(buffer,bytesize,1,ptr_myfile);
                memset(buffer,0,4);
        }
        fclose(stdin);
        fclose(ptr_myfile);
        fprintf(stderr,"\nExit reading\n");


        return (0);
}

