#Designming a PDA for a CFL 
#l2={w0^n|n>=1,w belongs {1,2}* and |w|=n}
#alphabets={0,1}

#stack functions
def push(a,list1):
    list1.append(a)
    return 1

def pop(list1):
    index=len(list1)-1
    if (index>0):
        list1.pop(index)
        return 1
    else:
        return 0