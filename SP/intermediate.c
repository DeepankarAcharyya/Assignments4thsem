//for creating the intermediate file--->program file with line numbers
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int findInterval(char* pointer1){
        char line_int[5];
        int i=5,j=0;
        while (i<(sizeof(pointer1)/sizeof(char))){
               line_int[j++]=pointer1[i++];
        }
        return atoi(line_int);
}

int main(){
    FILE* sicxe=fopen("sicxe.txt","r");
    FILE* intermediate_file=fopen("intermediate.txt","w");

    char line[50], line_int[5];
    char* pointer1;
    int line_number=0;
    int interval=0;

    while (!feof(sicxe)){
        interval=0;
        fgets(line,50,sicxe);

        if(strstr(line,"BYTE")!=NULL || strstr(line,"WORD")!=NULL){
            interval=1;
        }
        else if(strstr(line,"RESB")!=NULL){
                pointer1=strstr(line,"RESB");
                interval=findInterval(pointer1);
        }
        else if ( strstr(line,"RESW")!=NULL){
                pointer1=strstr(line,"RESW");
                interval=findInterval(pointer1);
        }
        else interval=3;
 
        fprintf(intermediate_file,"%x    %s",line_number,line);
        line_number+=interval;
    }

    _fcloseall();
    return 0;
}