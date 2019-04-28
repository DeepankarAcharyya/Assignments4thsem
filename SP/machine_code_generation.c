//Pass 2-->generating the machine machine code-->machine code file
//input-->intermediate file
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//global variables
char opcodes[50][10];
int index_opcode;
int opcode_binary[8];

//flag bits
int n/*indirect*/,i/*immediate*/,x/*indexed*/,b/*base relative*/,p/*PC relative*/,e/*extended*/;

//registers value
int A/*Accumulator*/,X/*Index register*/,L/*Linkage Register*/,B/*Base Register*/,PC/*Program Counter*/;

//address
int address[32],address2[20];

//functions
int binary(int a,int b){
    int i=0,s;
    if (b==1)
        s=8;
    else s=4;
    while(a!=0){
        opcode_binary[s-i-1]=a%2;
        a=a/2;
        i++;
    }
    return 1;
}

void convert2Binary(char opcode[]){
    int opCode=atoi(opcode);
    int r,j=4,bin,i=1;

    while(r!=0){
        r=opCode%10;
        bin=binary(r,i);
        i++;
        opCode=opCode/10;
    }
}

void fillAddress1(int ins_length,int disp){
    int index=0;
    while(index<6){
        address[index]=opcode_binary[index];
        index++;
    }
    address[6]=n;
    address[7]=i;
    address[8]=x;
    address[9]=b;
    address[10]=p;
    address[11]=e;

    if (ins_length==24){
        disp=disp%10000;
    }
    else disp=disp%1000000;

    return;
}


int isBaseRelative(int target_address){
    int disp=target_address-B;
    if(disp>=0 && disp<=4095){
        return 1;
    }
    else return 0;
}

int isProgramCounterRelative(int target_address){
    int disp=target_address-PC;
    if (disp>=-2048 && disp<=2047){
        return 1;
    }
    else return 0;
}

void scanOpcode(){
    FILE* opcode_file=fopen("opcode.txt","r");
    index_opcode=0;
    while(!feof(opcode_file)){
        fscanf(opcode_file,"%s %s",opcodes[index_opcode],opcodes[index_opcode+1]);
        index_opcode+=2;
    }
    fclose(opcode_file);
    return;
}

int getOpcode(char mnemonic[]){
    //checking,comparing for mnemonics and returning their opcodes-->from opcodes[]
    int i=0;
    while (i<index_opcode){
        if (strcmp(mnemonic,opcodes[i])==0){
            return atoi(opcodes[i+1]);
        }
        i+=2;
    }
    return -1;
}

int scanSymbolTable(char label2scan[]){
    FILE* symbol_table_file=fopen("symbol_table.txt","r");
    char add[10],label[10];
    while (!feof(symbol_table_file)){
        fscanf(symbol_table_file,"%s %s",add,label);
        if(strcmp(label2scan,label)==0){
            fclose(symbol_table_file);
            return atoi(add);
        }
    }
    fclose(symbol_table_file);
    return -1;
}

int returnValue(char* pointer1){
    int i,j=0;
    int value=0;

    if(strstr(pointer1,"LDX")!=NULL || strstr(pointer1,"LDA")!=NULL)
        i=5;
    else 
        i=6;

    int size=(sizeof(pointer1)/sizeof(char))+1;
        while (i<=size){
            if(pointer1[i]>='0' && pointer1[i]<='9'){
                value*=10;
               value+=pointer1[i]-'0';
               i++;}
            else break;
        }
    return value;
}

//main function
int main(){
    FILE* intermediate_file=fopen("intermediate.txt","r");
    FILE* machine_code_file=fopen("machinecode.txt","w");
    
    //scanning in all the mnemonics along with the opcodes
    scanOpcode();

    //for reading each line of instruction
    char line[80];

    //common variables for the generation of object codes
    int disp,target_address,format,instruction_length,present_address,next_address;
    
    fscanf(intermediate_file,"%x",present_address);
    
    while (!feof(intermediate_file)){
        
        //reading in the line
        fgets(line,80,intermediate_file);
        fscanf(intermediate_file,"%x",next_address);
        
        if(line[0]=='.' || strstr(line,"START")!=NULL || strstr(line,"END")!=NULL || strstr(line,"BYTE")!=NULL ||strstr(line,"WORD")!=NULL ||strstr(line,"RESW")!=NULL || strstr(line,"RESB")!=NULL ){
            //skipping the assembler directives
            fprintf(machine_code_file,"%s",line);
        }
        else{
            //updating the values of registers
            if(strstr(line,"LDX")!=NULL){
                char *pointer1=strstr(line,"LDX");
                X=returnValue(pointer1);
            }
            else if(strstr(line,"LDA")!=NULL){
                char *pointer1=strstr(line,"LDA");
                A=returnValue(pointer1);
            }
            else if(strstr(line,"BASE")!=NULL){
                char *pointer1=strstr(line,"BASE");
                B=returnValue(pointer1);
            }

            //default values
            n=1;i=1;
            //generation of object code:
            
            //extracting the present address and the next address(PC and the target address)

            if(strstr(line,"+")!=NULL){
                //checking for format 4
                e=1;
                p=0;
                b=0;
                format=4;
                }
            else{
            //checking for format 3-->and atlast format 4
            //checking if the instruction is PC relative or Base relative or extended

                if(isBaseRelative(target_address)){
                    b=1;
                    p=0;
                    format=3;
                }
                else if(isProgramCounterRelative(target_address)){
                    b=0;
                    p=1;
                    format=3;
                }
                else{
                    e=1;
                    b=0;
                    p=0;
                    format=4;
                }
            }


            if(strstr(line,"#")!=NULL){
            //immediate addressing mode
                i=1;
                n=0;
                x=0;//cannot be combined with indexed
                }
            else if (strstr(line,"@")!=NULL){
                //indirect addressing mode
                n=1;
                i=0;
                x=0;//cannot be combined with indexed
            }
            
            if (/* condition */){
                //Direct addressing mode   
                n=1;
                i=1;
                b=0;
                p=0;
            }
            
            if(strstr(line,",X")!=NULL){
                //indexed addressing mode
                n=1;
                i=1;
                x=1;

            }

            //checking the format type and process further
            if (format==4){
                instruction_length=32;
                fillAddress1(instruction_length,target_address);
            }
            else if (format==3){
                instruction_length=24;
                fillAddress1(instruction_length,disp);
            }
        }
    }
    
    _fcloseall();
    return 0;
}