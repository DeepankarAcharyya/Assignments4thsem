//functions
char HexValue[4];
char convert2Hex(int q){
    int r,j = 0;
    while (q!= 0){
        r = q % 16;          
    if (r < 10)
        HexValue[j++] = 48 + r;   
    else
        HexValue[j++] = 55 + r;   
    q= q/ 16;            
    }
}

int convert2Decimal(char l1){
    return l1-'A'+10;
}

int binary2decimal(int a){
    int i=0,b=0;
    int r;
    while(a!=0){
        r=a%10;
        b+=r*pow(2,i);
        i++;
    }
    return b; 
}

void binary(int a){
    int binary[4];
    int i1=0;
    while(a!=0){
        binary[4-i-1]=a%2;
        a=a/2;
        i1++;
    }
    address[1]=binary[0];
    address[2]=binary[1];
}

//yet to be completed
void fillAddress2(int format){
    //converting 
}

void fillAddress0(char opcode[]){
    //adding opcodes to the address
    add_final[0]=opcode[0];
    char b=opcode[1];
    if (b>='0' && b<='9'){
        binary(b-'0');
    }
    else   binary(convert2Decimal(b));
}


void fillAddress1(int ins_length,int disp){
    int i1,format;
    
    if (ins_length==24){
        disp=disp%10000;
        i1=5;
        format=4;
        address[3]=n;
        address[4]=i;
        address[5]=x;
        address[6]=b;
        address[7]=p;
        address[8]=e;
    }
    else if(ins_length==20) {
        disp=disp%1000000;
        i=3;
        format=3;
        address[5]=n;
        address[6]=i;
        address[7]=x;
        address[8]=b;
        address[9]=p;
        address[10]=e;
        }

    while(disp!=0){
        address[11-i1-1]=disp%10;
        disp=disp/10;
        i1++;
    }
    fillAddress2(format);
    return;
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


functions definitions:

-->convert2Hex()-->converting int to hex
-->convert2Decimal()-->converting hex to decimal
-->binary2decimal()-->int to binary

-->binary()-->for opcode (5th and 6th bits)
-->fillAddress0()-->for filling up the opcodes
-->fillAddress1()-->filling up the flag bits+filling up the disp
-->fillAddress2()-->converting address to final address

-->isBaseRelative()-->check whether applicable
-->isProgramCounterRelative()-->check whether applicable

-->scanOpcode()-->loads and stores the mnemonics+opcodes in the memory
-->scanSymbolTable()-->checks symbol table for the mnemonic and return s its address

-->returnValue()-->returns the value to be stored in the registers































 if(strstr(line,"+")!=NULL){
                e=1;
                char* s=strstr(line,"+");
                strcpy(line2,&s[1]);
            }
            else{



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
            
            if(strstr(line,",X")!=NULL){
                //indexed addressing mode
                n=1;
                i=1;
                x=1;

            }

