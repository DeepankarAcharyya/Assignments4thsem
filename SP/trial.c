#include<stdio.h>

int b1[4];

int binary(int a){
    int i=0;
    while(a!=0){
        b1[4-i-1]=a%2;
        a=a/2;
        printf("\n a=%d",a);
        i++;
    }
    return 1;
}



void main(){
int a=binary(8);
int i=0;
while(i<4)
printf("%d",b1[i++]);
}