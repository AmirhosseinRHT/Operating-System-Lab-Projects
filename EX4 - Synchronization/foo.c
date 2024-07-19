#include "types.h"
#include "user.h"
#include "fcntl.h"

int main()
{
    for (int i = 0; i < 6; i++)
    {
        int pid = fork();
        if (pid > 0)
            continue;
        if (pid == 0)
        {
            sleep(1000);
            for (int j = 0; j < 500 ; j++)
            {
                long x = 0;
                for (long k = 0; k < 10000000000; k++)
                    x++;
            }
            exit();
        }
    }
    for(int i = 0 ; i < 3 ; i++)
        wait();
    exit();
}