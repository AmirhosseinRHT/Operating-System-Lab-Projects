#include "types.h"
#include "stat.h"
#include "fcntl.h"
#include "user.h"

int main(int argc, char* argv[]){
    uint bef_ecx;
    asm volatile( "movl %%ecx, %0\n\t" 
    "movl %1, %%ecx" 
    : "=r"(bef_ecx) 
    : "r"(atoi(argv[1]))
    )
    ;
    int ret = find_digital_root();

    asm volatile( "movl %0, %%ecx" 
        :: "r"(bef_ecx));
    
    printf(1, "%d\n", ret);
    exit();
}