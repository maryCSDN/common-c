#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cmlog.h"

int main(int argc, char **argv)
{
    log_debug("this is debug");
    log_info("this is info");
    log_warn("this is warn");
    log_error("configuration file");

    return 0;
}