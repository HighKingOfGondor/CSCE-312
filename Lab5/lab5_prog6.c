//File named “lab5_prob6.c” 
#include <stdio.h>
int very_fast_function(int i)
{
    //if ( (i*64 +1) > 1024) return i++;
    //else return 0;
    int result;
    asm ("movl $0x1, %%eax;"
            "movl $0x40, %%ebx;"
            "movl %1, %%ecx;"
            "imull %%ecx, %%ebx;"
            "addl %%eax, %%ebx;"
            "subl $1024, %%ebx;"
            "jg IF;"
            "ELSE: movl $0x0, %%ebx;"
            "jmp DONE;"
            "IF: addl %%eax, %%ebx; "
            "DONE: movl %%ebx, %0; " : "=g" (result) : "g" (i));
    return result;
}
int main(int argc, char *argv[]) 
{
    int i;
    i=40;
    printf("The function value of i is %d\n", very_fast_function(i) ); 
    return 0;
}
