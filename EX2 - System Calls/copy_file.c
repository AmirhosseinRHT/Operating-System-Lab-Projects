
#include "types.h"
#include "stat.h"
#include "fcntl.h"
#include "user.h"

int main(int argc, char* argv[]){
    if (argc < 3){
        printf(1, "error\n");
        exit();
    }
    int ret = copy_file(argv[1], argv[2]);
    if (ret < 0){
        printf(1, "%d\n", ret);
    }
    exit();
}