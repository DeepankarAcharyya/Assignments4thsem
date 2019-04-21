//Roll-No: CSB17017

/*
Starting State: 0-- it will read the string character by character
-if it sees a 'a'-->it moves to state 2 from state 0
                        -->if it sees a 'b' or 'c' -->it moves to state 1
-else if it sees a 'b' or 'c'-->it moves to state 1 from state 0
                        -->if it sees a 'a'-->it moves to state 2

-if the final state is 1, i.e. the last element was either a 'b' or 'c'-->the string will be accepted
-else the string will be rejected
*/


#include<stdio.h>

int main(){
    int state=0; //0 is the initial state
    char c;

    printf("\nEnter the string:");

    c =getchar();
    for(;;c =getchar()){
        if(c=='a'){
            //if the input is 'a' then it remains/goes to state 2
            state=2;
        }
        else if(c=='b' || c=='c'){
            //if the input is 'b' or 'c' then it remains/goes to state 1
            state=1;
        }
        else if (c=='\n'){
            if(state==1){
                printf("\n The String is accepted by the DFA!");
            }
            else
            {
                printf("\nThe string is not accepted by the DFA!");
            }
            break;
            }
        else {
            printf("\nThe string is not accepted by the DFA!");
            break;
        }
    }
    
    return 0;
}