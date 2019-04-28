#include<stdio.h>
#include<stdlib.h>

int b1[8];

int binary(int a,int b){
    int i=0,s;
    if (b==1)
        s=8;
    else s=4;    
    while(a!=0){
        b1[s-i-1]=a%2;
        a=a/2;
        printf("\n a=%d",a);
        i++;
    }
    return 1;
}

void convert2Binary(char opcode[]){
    int opCode=atoi(opcode);
    printf("opCode=%d",opCode);
    int r,j=4,bin,i=1;

    while(r!=0){
        r=opCode%10;
        bin=binary(r,i);
        i++;
        opCode=opCode/10;
    }
}


void main(){
char a[]="48";
//convert2Binary(a);
int i=0;
printf("\n");
while(i<8)
printf("%d",atoi());
}