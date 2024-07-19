#include "types.h"
#include "user.h"
#include "fcntl.h"

int main(){
    const int NUMBER = 7;
    p_init();
    for (int i = 0; i < NUMBER; i++)
    {
      int pid = fork();
      if (pid == 0)
      {
        p_acq();
        sleep(200);
        p_release();
        exit();
      }
    }

    for(int i = 0 ; i < NUMBER; i++)
        wait();
    printf(1, "\nfinished !\n");
    exit();
}