#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int main(int argc,char* argv[]){
    uint pid = fork();
    if(pid==0){
        sleep(1000);
        printf(1,"%d\n",get_process_lifetime(getpid()));
        exit();
    }
    else{
        wait();
        printf(1,"%d\n",get_process_lifetime(getpid()));
        exit();
    }
}