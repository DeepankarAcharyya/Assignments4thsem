//object file generation 
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void CreateHeadRecord(char prog_name[],int start_address,int program_length){
    FILE* object_file=fopen("object_file.txt","w");
    fprintf(object_file,"H^%s^%x^%x",prog_name,start_address,program_length);
    fclose(object_file);
    return;
}

void CreateEndRecord(int end_address){
    FILE* object_file=fopen("object_file.txt","a");
    fprintf(object_file,"E^%x",end_address);
    fclose(object_file);
    return;
}

void CreateTextRecord(int first_address){
    FILE* object_file=fopen("object_file.txt","a");
    fprintf(object_file,"T^%x",first_address);
    fclose(object_file);
    return;
}

int main(){
    FILE* machine_code_file=fopen("machinecode.txt","r");
    
    //length of the program
        //--->last address+address of the last line-the starting address
    //program name 
    //No of instructions
    //length of the number of instructions-->hex

    return 0;
}