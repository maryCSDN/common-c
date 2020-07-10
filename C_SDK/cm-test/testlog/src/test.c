#include <stdio.h>
#include <cmlog.h>

int main()
{
    log_init("mary_test");
    log_set_level(LOG_WARN);
    log_info("test ok");
    return 0;
}