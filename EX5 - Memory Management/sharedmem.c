#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

#define MAX_CHILDS 10

int main(int argc, char *argv[]) 
{
    for (int i = 0; i < MAX_CHILDS; i++)
    {
        int pid = fork();
        if (pid > 0)
            continue;
        if (pid == 0)
        {
            open_sharedmem(3);
            sleep(100);
            edit_sharedmem(3,1);
            close_sharedmem(3);
            sleep(100);
            exit();
        }
    }
    open_sharedmem(3);
    sleep(MAX_CHILDS * 20);
    edit_sharedmem(3,0);
    edit_sharedmem(3,0);
    edit_sharedmem(3,0);
    edit_sharedmem(3,0);
    edit_sharedmem(3,0);
    int x = edit_sharedmem(3,0);
    for(int i = 0 ; i < MAX_CHILDS ; i++)
        wait();

    printf(1 , "SharedMemory Final value:  %d \n" , x);
    close_sharedmem(3);
    exit();
}