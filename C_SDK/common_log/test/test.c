#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cmlog.h"

int main(int argc, char **argv)
{
    log_info("this is info");
    log_warn("this is warn");
    log_info_module("test", "this is test info");
    log_error_module(null, "this is test error");
    get_config_path();
    return 0;
}