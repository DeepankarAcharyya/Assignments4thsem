#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

char mnemonics[50][10];
int  opcodes[50],index_opcode;

//flag bits
int ni,x,b,p,e;
//registers value
int A,X,B;

void scanOpcode(){
    FILE* opcode_file=fopen("opcode.txt","r");
    index_opcode=0;
    while(!feof(opcode_file)){
        fscanf(opcode_file,"%s %x",&mnemonics[index_opcode],&opcodes[index_opcode]);
        index_opcode++;
    }
    fclose(opcode_file);
    return;
}

int getOpcode(char mnemonic[]){
    int i=0;
    while (i<index_opcode){
        if (strcmp(mnemonic,mnemonics[i])==0){
            return opcodes[i];
        }
        i++;
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
            return add;
        }
    }
    
    fclose(symbol_table_file);
    return -1;
}

void main(){
    FILE* intermediate_file=fopen("intermediate.txt","r");
    FILE* machine_code_file=fopen("machinecode.txt","w");
    
    scanOpcode();
    
    char line[80],line2[10];
    int disp,instruction_length,present_address,next_address,opcode,immediate;
    
    while (!feof(intermediate_file)){
        opcode=0;
        fgets(line,80,intermediate_file);

        if(line[0]=='.' || strstr(line,"START")!=NULL || strstr(line,"END")!=NULL ||strstr(line,"RESW")!=NULL || strstr(line,"RESB")!=NULL ){
            fprintf(machine_code_file,"%s",line);
        }
        else{
            
            if(strstr(line,"WORD")!=NULL){
                line[strlen(line)-1]='\0';
                fprintf(machine_code_file,"%s\t\t",line);
                char* str1;
                str1=strstr(line,"WORD");
                strcpy(line,str1+7);

                int index=0,sum=0;
                puts(line);
                while(index<strlen(line)){
                        sum*=10;
                        sum+=line[index]-'0';
                        index++;
                    }
                
                fprintf(machine_code_file,"\t%.6x\n",sum);
                continue;
            }
            else if(strstr(line,"BASE")!=NULL){
                fprintf(machine_code_file,"%s",line);
                char* str1;
                str1=strstr(line,"BASE");
                strcpy(line,str1+5);
                line[strlen(line)-1]='\0';
                if(scanSymbolTable(line)!=-1)
                   B=scanSymbolTable(line);
                continue;
            }
            else if(strstr(line,"RSUB")!=NULL){
                line[strlen(line)-1]='\0';
                fprintf(machine_code_file,"%s\t\t4F0000\n",line);
                continue;
            }
            else if(strstr(line,"BYTE")!=NULL){
                line[strlen(line)-1]='\0';
                fprintf(machine_code_file,"%s\t\t",line);
                char* str1;
                str1=strstr(line,"BYTE");
                strcpy(line,str1+5);

                char c=line[0];
                int index=0;
                
                str1=strstr(line,"\'");
                strcpy(line,str1+1);

                while(index<strlen(line)){
                        if(line[index]=='\''){
                            line2[index]='\0';
                            break;}
                        line2[index]=line[index];
                        index++;
                    }

                if(c=='C'){
                    index--;
                    
                    while(index>=0){
                        fprintf(machine_code_file,"%x",line2[strlen(line2)-index-1]);
                        index--;
                    }
                    fprintf(machine_code_file,"\n ");
                }
                else if(c=='X'){
                    if (strlen(line2) % 2 != 0)
                        fprintf(machine_code_file, "0");
        
                    fprintf(machine_code_file,"%s\n",line2);
                }
                continue;
            }


            

            if(strstr(line,"+")!=NULL){
                e=1;
                char* str1;
                str1=strstr(line,"+");
                strcpy(line,str1+1);
                
                int index=0;
                //getting the mnemonic
                while(index<strlen(line)){
                    if(line[index]==' '){
                        line2[index]='\0';
                        break;}
                    line2[index]=line[index];
                    index++;
                }
                //getting the opcode
                opcode=getOpcode(line2);
                int j=0;
                index++;
                //getting the operand
                while(index<strlen(line)){
                    if(line[index]==' '){
                        line2[j]='\0';
                        break;}
                    line2[j++]=line[index];
                    index++;
                }
                
                if(strstr(line2,"#")!=NULL){
                    ni=0x01;
                }
                else if(strstr(line2,"@")!=NULL){
                    ni=0x10;
                }

                if(strstr(line2,",X")!=NULL){
                    line2[strlen(line2)-1]='\0';
                    x=1;
                }
            }


            //printing the hexcode from xbpe
            fprintf(machine_code_file,"%x",e*1+p*2+b*4+x*8);

            if(e==1 && immediate==0){}
            else if(e==1 && immediate!=0){}
            else if(e==0 && immediate==0){}
            else if(e==0 && immediate!=0){}
            

        }
        present_address=next_address;
    }

    _fcloseall();
}


