//Pass 2-->generating the machine machine code-->machine code file
//input-->intermediate file
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

//global variables
char mnemonics[50][10];
int  opcodes[50];
int index_opcode;

//flag bits
int n,i,x,b,p,e;
//registers value
int A,X,L,B,PC;

//address
char add_final[8];

//functions:


void scanOpcode(){
    FILE* opcode_file=fopen("opcode.txt","r");
    index_opcode=0;
    while(!feof(opcode_file)){
        fscanf(opcode_file,"%s %x",&mnemonics[index_opcode],&opcodes[index_opcode]);
        //printf("\n%s %x",mnemonics[index_opcode],opcodes[index_opcode]);
        index_opcode++;
    }
    fclose(opcode_file);
    return;
}

int getOpcode(char mnemonic[]){
    //checking,comparing for mnemonics and returning their opcodes-->from opcodes[]
    int i=0;
    while (i<index_opcode){
        if (strcmp(mnemonic,mnemonics[i])==0){
            return opcodes[i];
        }
        i+=2;
    }
    return -1;
}

int scanSymbolTable(char label2scan[]){
    FILE* symbol_table_file=fopen("symbol_table.txt","r");
    char label[10];
    int add;
    while (!feof(symbol_table_file)){
        fscanf(symbol_table_file,"%x %s",&add,label);
        if(strcmp(label2scan,label)==0){
            fclose(symbol_table_file);
            return add;
        }
    }
    fclose(symbol_table_file);
    return -1;
}

//main function
int main(){
    FILE* intermediate_file=fopen("intermediate.txt","r");
    FILE* machine_code_file=fopen("machinecode.txt","w");
    
    //scanning in all the mnemonics along with the opcodes
    scanOpcode();

    //for reading each line of instruction
    char line[80],line2[10];

    //common variables for the generation of object codes
    int disp,format,instruction_length,present_address,next_address,opcode1;
    
    //as next address will become present address
    fscanf(intermediate_file,"%x",present_address);

    while (!feof(intermediate_file)){
        
        //reading in the line
        fgets(line,80,intermediate_file);
        //read the next address
        fscanf(intermediate_file,"%x",next_address);
        
        fprintf(machine_code_file,"%.4x",present_address);

        if(line[0]=='.' || strstr(line,"START")!=NULL || strstr(line,"END")!=NULL ||strstr(line,"WORD")!=NULL ||strstr(line,"RESW")!=NULL || strstr(line,"RESB")!=NULL ){
            //skipping the assembler directives+comments
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
            
           
        present_address=next_address;
    }}

    _fcloseall();
    return 0;
}