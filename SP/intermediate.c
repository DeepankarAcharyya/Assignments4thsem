//for creating the intermediate file--->program file with line numbers
#include<stdio.h>
#include<stdlib.h>

int main(){
    FILE* sicxe=fopen("sicxe.txt","r");
    FILE* intermediate_file=fopen("intermediate.txt","w");

    char line[50];
    int line_number=0;

    while (!feof(sicxe)){
        fgets(line,50,sicxe);
        fprintf(intermediate_file,"%x    %s",line_number,line);
        line_number+=3;
    }

    _fcloseall();
    return 0;
}