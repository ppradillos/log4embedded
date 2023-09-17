#include <string.h>
#include <stdlib.h>

#include "log4embedded.h"

/*  By default, logs from all log level categories (see LOG_MSG_CATEGORY in log4embedded.h) will be printed through the stdout, except 
    those logs coming from calling "log_print_debug" function. Log messages shall be printed in color:
        - log_print_critical --> RED
        - log_print_error --> BRIGHT RED
        - log_print_warning --> BRIGHT YELLOW
        - log_print_info --> BRIGHT GREEN
        - log_print_debug --> NO PRINTED BY DEFAULT
    
    To enable debug logs, an explicit call to "log_set_level(LOG_MSG_DBG)" is needed. Debug logs have no special color assigned, they
    will be displayed with the default foregroung color in the virtual terminal.
*/
int main() {

    // Write logs stright to a file. When selecting this option, then no colors by default
    // Please, note if "logs" folder does not exist beforehand, it shall not create the "log.txt" file.
    const char log_file_name[12] = "log/log.txt";
    log_set_file(log_file_name, sizeof(log_file_name));

    // log all prints
    log_set_level(LOG_MSG_DBG);

    // Hello world that will not be printed, because LOG_MSG_ERR is much more restrictive than LOG_MSG_INFO
    log_print_info("Hello World!\n");

    for(int i = 0; i < 10; ++i)
    {
        if (i%2 == 0)
            log_print_error("Even number: [%d]\n", i);
        else
            log_print_warning("Odd number: [%d]\n", i);
    }

    log_print_critical("Example finished!!\n");

    //... Rest of your application's code

    log_print_debug("Exiting application!\n"); 
    
    return 0;
}