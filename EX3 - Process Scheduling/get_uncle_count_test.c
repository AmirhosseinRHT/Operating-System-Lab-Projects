#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
int main(int argc,char* argv[]){
    uint pid1 = 1,pid2 = 1,pid3 = 1,pid4 = 1;
    pid1 = fork();
    if(pid1==0){
        sleep(100);
        
    }
    else{
        pid2 = fork();
        if(pid2==0){
            sleep(100);
        }
        else{
            pid3 = fork();
            if(pid3==0){                
                pid4 = fork();
                if(pid4 == 0){
                    printf(1,"%d\n",get_uncle_count(getpid()));
                }
                else{
                    wait();
                }
            }
        }
        if(pid1 !=0 && pid2 != 0 && pid3 != 0){
            wait();
            wait();
            wait();
        }
    }
    exit();
}