#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

#define MAX_LENGTH 32
#define NULL '\0'

void compareStrings(const char *str1, const char *str2, char *result) 
{
    int length = strlen(str1);
    if (length < strlen(str2))
        length = strlen(str2);
    for (int i = 0; i < length; i++)
        if (str1[i] <= str2[i])
            result[i] = '1';
        else
            result[i] = '0';
}

int main(int argc, char *argv[]) 
{
    if (argc < 3)
        exit();
    const char *str1 = argv[1] , *str2 = argv[2];
    char result[MAX_LENGTH];
    int resault_size = 0;

    compareStrings(str1, str2, result);
    for(int i = 0 ; i < MAX_LENGTH ; i++)
        if (result[i] == NULL)
        {
            resault_size = i;
            result[i] = '\n';
            break;
        }
        
    int fd = open("strdiff_result.txt", O_WRONLY);
    if (fd < 0) 
    {
        printf(1 , "can't open file...\n");
        exit();
    }

    if (write(fd, result, (sizeof(char) * (resault_size+1))) < (sizeof(char) * resault_size))
    {
        printf(1 , "write error...\n");
        exit();
    }
    close(fd);
    exit();
}
