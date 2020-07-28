#include <stdio.h>
#include <stdlib.h>
#include <cmlog.h>
#include <windows.h>

int main()
{
    printf("start\n");
    log_init("mary_test");
    log_set_level(LOG_INFO);
    while(1)
    {
        log_info("test ok");
        Sleep(500);
    }
    
    return 0;
}