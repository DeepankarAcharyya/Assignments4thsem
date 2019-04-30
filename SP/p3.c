#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

char mnemonics[50][10];
int  opcodes[50],index_opcode;
char line[80],line2[10];

//flag bits
int ni,x,b,p,e;
//registers value
int A,X,B;
int a1,x1;

void readnextterm(){
    char* str1;
            str1=strstr(line,line2);
            strcpy(line,str1+strlen(line2));
            sscanf(line,"%s",line2);
}
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
            return i;
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

int isBaserelative(int disp){
    if(disp>=0 && disp<=4095){
        return 1;
    }
    else return 0;
}

int isPCrelative(int disp){
    if (disp>=-2048 && disp<=2047){
        return 1;
    }
    else return 0;
}

void main(){
    FILE* intermediate_file=fopen("intermediate.txt","r");
    FILE* machine_code_file=fopen("machinecode.txt","w");
    
    scanOpcode();

    int disp,instruction_length,present_address,target_address,opcode,immediate;

    while (!feof(intermediate_file)){
        ni=0x3;x=0;b=0;p=0;e=0,a1=0,x1=0;
        
        fgets(line,80,intermediate_file);

        if(line[0]=='.' || strstr(line,"START")!=NULL || strstr(line,"END")!=NULL ||strstr(line,"RESW")!=NULL || strstr(line,"RESB")!=NULL ){
            fprintf(machine_code_file,"%s",line);
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
        else{
            line[strlen(line)-1]='\0';
            sscanf(line,"%x %[^/n]s",&present_address,line);
            fprintf(machine_code_file,"%x\t%s\t",present_address,line);

            if(strstr(line,"WORD")!=NULL){                
                char* str1;
                str1=strstr(line,"WORD");
                strcpy(line,str1+7);

                int sum;
                sscanf(line,"%d",&sum);
                fprintf(machine_code_file,"\t%.6x\n",sum);
                continue;
            }

            else if(strstr(line,"RSUB")!=NULL){
                fprintf(machine_code_file,"4f0000\n");
                continue;
            }

            else if(strstr(line,"BYTE")!=NULL){
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
            
             if(strstr(line,"LDA")!=NULL || strstr(line,"STA")!=NULL){ a1=1;}
            else if(strstr(line,"LDX")!=NULL){x1=1;}
            
            target_address=0x0;

            if(strstr(line,"+")!=NULL){
                e=1;
                char* str1;
                str1=strstr(line,"+");
                strcpy(line,str1+1);
            }

            //getting the mnemonic
            sscanf(line,"%s",line2);
            
            //getting the opcode
            while(1){
            if(getOpcode(line2)!=-1){
                //getting the operand
                opcode=getOpcode(line2);
                readnextterm();
                break;
            }
            readnextterm();
            }
            
            //determining the values of N and I
            if(strstr(line2,"#")!=NULL){
                ni=0x1;
                char* str1;
                str1=strstr(line,"#");
                strcpy(line,str1+1);
            }
            else if(strstr(line2,"@")!=NULL){
                ni=0x2;
                char* str1;
                str1=strstr(line,"@");
                strcpy(line,str1+1);  
            }
            //printing the first 2 bytes of the object code
            opcode=opcodes[opcode];
            fprintf(machine_code_file,"%.2x", (opcode) + ni - ((opcode)% 16) % 4);
            
            if(strstr(line2,",X")!=NULL){
                line2[strlen(line2)-2]='\0';
                x=1;
            }

            //disp calculation
            immediate=1;
            if(scanSymbolTable(line2)!=-1){
               target_address=scanSymbolTable(line2);
                immediate=0;
            }

            if(e==1){
                p=0;b=0;
            }
            else{
                e=0;
                if(immediate==1){
                    b=0;p=0;
                }
                else{
                    disp=target_address-present_address-3;
                    if(isPCrelative(disp)){
                        p=1;b=0;
                    }
                    else {
                        disp=target_address-B;
                        p=0;b=1;
                    }
                }
            }
            
            if (disp<0){
                    disp= ~disp+ 0x01;          
                }

            //printing the hexcode from xbpe
            fprintf(machine_code_file,"%x",e*1+p*2+b*4+x*8);

            if(line2[0]=='#'){
                strcpy(line2,line2+1);
            }

            int add1;
            if(scanSymbolTable(line2)!=-1){
                add1=scanSymbolTable(line2);
            }
            else add1=atoi(line2);
            
            if(a1==1){
                A=add1;
            }
            else if (x1==1){
                X==add1;
            }

            if(e==1 && immediate==0){
                fprintf(machine_code_file,"%.5x",add1);
                }
            
            else if(e==1 && immediate!=0){
                fprintf(machine_code_file, "%.5x",add1);
            }

            else if(e==0 && immediate==0){

                fprintf(machine_code_file, "%.3x", disp % 0x1000);
            }

            else if(e==0 && immediate!=0){
                 int q = 3 - strlen(line2);
            while (q > 0)
            {
                fprintf(machine_code_file, "%x", 0);
                q--;
            }
            fprintf(machine_code_file, "%s\n", line2);
            }
            fprintf(machine_code_file,"\n");
        }
    }
    _fcloseall();
}