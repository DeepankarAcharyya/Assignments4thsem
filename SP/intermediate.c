//for creating the intermediate file--->program file with line numbers+the symbol table
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//global variables
char prog_name[15];
int start_address,end_address;

//functions
int findInterval(char* pointer1,int k){
        int i,j=0;
        int address=0;

        if(k==1)
            i=6;
        else if (k==0)
        i=5;
        else if(k==2){
            if(strstr(pointer1,"C'")!=NULL){
                pointer1=strstr(pointer1,"C\'");
            }
            else if(strstr(pointer1,"X'")!=NULL){
                pointer1=strstr(pointer1,"X\'");
            }
            j=2;
            while(pointer1[j]!='\''){
                address++;
                j++;
            }
            //printf("\nBYTE CASE:%d",address);
            return address;
        }
        int size=(sizeof(pointer1)/sizeof(char))+1;
        while (i<=size){
            if(pointer1[i]>='0' && pointer1[i]<='9'){
                address*=10;
               address+=pointer1[i]-'0';
               i++;}
            else break;
        }
        //printf("\n%d %s %d",size,pointer1,address);
        return address;
}

void getProgramName(char line[]){
    int i=0;
    while(line[i]!=' '){
        prog_name[i]=line[i];
        i++;
    }
}

void printlabel(char line[],int line_number){
        FILE* symbol_table_file=fopen("symbol_table.txt","a");
        char label1[10];
        int i=0,j=0;
        while (line[i]!=' '){
            label1[j++]=line[i++];
        }
        //printf("\nLabel=%s",label1);
         fprintf(symbol_table_file,"%x   %s\n",line_number,label1);
         fclose(symbol_table_file);
}

//main
int main(){
    FILE* sicxe=fopen("sicxe.txt","r");
    FILE* intermediate_file=fopen("intermediate.txt","w");
    FILE* symbole_table=fopen("symbol_table.txt","w");
    
    char line[50], line_int[5];
    char* label1;
    char* pointer1;
    int line_number=0;
    int interval=0;

    while (!feof(sicxe)){
        interval=0;
        fgets(line,50,sicxe);
        
        if(strstr(line,"BASE")!=NULL || line[0]=='.'){
            fprintf(intermediate_file,"\t%s",line);
            continue;
        }
        else if(strstr(line,"START")!=NULL){
            getProgramName(line);
            pointer1=strstr(line,"START");
            line_number=findInterval(pointer1,1);
            start_address=line_number;
       }
        else if(strstr(line,"END")!=NULL){
            end_address=line_number;
            fprintf(intermediate_file,"%x \t %s",line_number,line);
            break;
        }
        else if(strstr(line,"BYTE")!=NULL){
            pointer1=strstr(line,"BYTE");
            interval=findInterval(pointer1,2);
            printlabel(line,line_number);
        }
        else if(strstr(line,"WORD")!=NULL){
            interval=3;
            printlabel(line,line_number);
        }
        else if(strstr(line,"RESB")!=NULL){
                pointer1=strstr(line,"RESB");
                interval=findInterval(pointer1,0);
                printlabel(line,line_number);
        }
        else if ( strstr(line,"RESW")!=NULL){
                pointer1=strstr(line,"RESW");
                interval=findInterval(pointer1,0);
                printlabel(line,line_number);
        }
        else if(strstr(line,"+")!=NULL){
            interval=4;
        }
        else if(line[0]!=' '){
            printlabel(line,line_number);
            interval=3;
        }
        else interval=3;
        fprintf(intermediate_file,"%x \t %s",line_number,line);
        line_number+=interval;
    }

    _fcloseall();
    return 0;
}