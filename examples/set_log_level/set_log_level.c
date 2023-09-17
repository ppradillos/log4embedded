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

    // Print errors and criticals only
    log_set_level(LOG_MSG_ERR);

    // Hello world that will not be printed, because LOG_MSG_ERR is much more restrictive than LOG_MSG_INFO
    log_print_info("Hello World!\n");

    // Show the colors assigned to every log function
    for(int i = 0; i < 10; ++i)
    {
        if (i%2 == 0)
            log_print_error("Even number: [%d]\n", i); // printed because of selected log level (LOG_MSG_ERR)
        else
            log_print_warning("Odd number: [%d]\n", i);   // NOT printed because of selected log level (LOG_MSG_ERR)
    }

    log_print_critical("Example finished!!\n");   // printed because of selected log level (LOG_MSG_ERR), which is less restrictive than LOG_MSG_CRIT

    //... Rest of your application's code
    
    return 0;
}