#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

//global variables
char opcodes[50][10];
int index_opcode;

//flag bits
int n/*indirect*/,i/*immediate*/,x/*indexed*/,b/*base relative*/,p/*PC relative*/,e/*extended*/;

//registers value
int A/*Accumulator*/,X/*Index register*/,L/*Linkage Register*/,B/*Base Register*/,PC/*Program Counter*/;

//address
int address[11];
char add_final[8];

void scanOpcode();
int scanSymbolTable(char[]);

int main(){
    FILE* intermediate_file=fopen("intermediate.txt","r");
    FILE* machine_code_file=fopen("machinecode.txt","w");
    
    //scanning in all the mnemonics along with the opcodes
    scanOpcode();

    //for reading each line of instruction
    char line[80];

    //common variables for the generation of object codes
    int disp,format,instruction_length,present_address,next_address,opcode1;
    
    while (!feof(intermediate_file)){

        //reading in the line
        fscanf(intermediate_file,"%x",present_address);
        fgets(line,80,intermediate_file);
        fscanf(intermediate_file,"%x",next_address);
        
        fprintf(machine_code_file,"%.4x",present_address);

        if(line[0]=='.' || strstr(line,"START")!=NULL || strstr(line,"END")!=NULL ||strstr(line,"WORD")!=NULL ||strstr(line,"RESW")!=NULL || strstr(line,"RESB")!=NULL ){
            //skipping the assembler directives
            fprintf(machine_code_file,"%s",line);
        }
        else{
            
            if(strstr(line,"BASE")!=NULL){
                fprintf(machine_code_file,"%s",line);
                //for base directive
                char* str1;
                str1=strstr(line,"BASE");
                strcpy(line,&str1[5]);
                if(scanSymbolTable(line)!=-1)
                   B=scanSymbolTable(line); 
                continue;
            }
            
            if(strstr(line,"RSUB")!=NULL){
                line[strlen(line)-1]='\0';
                fprintf(machine_code_file,"%s\t4F0000\n",line);
                continue;
            }

            if(strstr(line,"BYTE")!=NULL){
                char* s1=strstr(line,"BYTE");
                
            }
        }
    _fcloseall();
    return 0;
}