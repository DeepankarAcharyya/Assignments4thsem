//loading in the mnemonics and checking for the same
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(){
    FILE* mnemonics=fopen("opcode.txt","r");
    FILE* intermediate=fopen("intermediate.txt","r");
    FILE* mnemonicsChecker=fopen("mnemonicsChecker.txt","w");

    char line2[50], m[20][8];
    int m_i=0;

    //read-in the mnemonics
    while(!feof(mnemonics)){
        fscanf(mnemonics,"%s",m[m_i]);
        m_i++;
    }
        
    while(!feof(intermediate)){
        int j1=0; 
        fgets(line2,50,intermediate);

        printf("\n%s",line2);

        while(j1<m_i){
            if(strstr(line2,m[j1])!=NULL){
                fprintf(mnemonicsChecker,"%s   %d",line2,line2[++j1]);
                j1++;
            }
            else    j1+=2;
        }
    }

    _fcloseall();

    return 0;
}