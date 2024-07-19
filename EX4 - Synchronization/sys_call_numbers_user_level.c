#include "types.h"
#include "stat.h"
#include "fcntl.h"
#include "user.h"
#include "mp.h"

#define MAX_LENGTH 32
#define NULL '\0'


int main(int argc, char *argv[]) 
{
    //print_global_sys_call_numbers();
    int pid = fork();
    // int pid1 = fork();
    // int pid2 = fork();
    // int pid3 = fork();
    char result[10] = {'s','a','l','a','m','s','a','l','a','m'};
    int resault_size = 0;
    if(pid ==0){
        int  fd = open("123.txt", O_WRONLY | O_CREATE);
        if (fd < 0 ) 
        {
            printf(1 , "can't open file...\n");
            exit();
        }

        if (write(fd, result, (sizeof(char) * (resault_size+1))) < (sizeof(char) * resault_size))
        {
            printf(1 , "write error...\n");
            close(fd);
            exit();
        }
        exit();
    }
    else{
        int  fd = open("1234.txt", O_WRONLY | O_CREATE);
        if (fd < 0 ) 
        {
            printf(1 , "can't open file...\n");
        }

        if (write(fd, result, (sizeof(char) * (resault_size+1))) < (sizeof(char) * resault_size))
        {
            printf(1 , "write error...\n");
        }
        wait();
        print_global_sys_call_numbers();
        printf(1,"parent process: %d\n",sys_call_numbers());
        exit();

    }
    // if(pid != 0){
    //     wait();
    // }
    // if(pid1 != 0){
    //     wait();
    // }
    // if(pid2 != 0){
    //     wait();
    // }
    // if(pid3 != 0){
    //     wait();
    // }
    
    // exit();
}