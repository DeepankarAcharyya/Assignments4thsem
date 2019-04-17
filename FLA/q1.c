#include<stdio.h>

int main(){
    int state=0; //0 is the initial state
    char c;

    c =getchar();
    for(;;c =getchar()){
        if(c=='a'){
            //if the input is 'a' then it remains/goes to state 2
            state=2;
        }
        else if(c=='b' || c=='c'){
            state=1;
        }
        else if (c=='\n'){
            if(state==1){
                //if the input is 'b' or 'c' then it remains/goes to state 1
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
