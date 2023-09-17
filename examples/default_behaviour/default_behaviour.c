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

    // Print info
    log_print_info("Hello World!\n");

    // Show the colors assigned to every log function
    for(int i = 0; i < 8; ++i)
    {
        switch(i)
        {
            case 2:
                log_print_critical("Number: [%d]\n", i);
            case 3:
                log_print_error("Number: [%d]\n", i);
            case 4:
                log_print_warning("Number: [%d]\n", i);
            case 5:
                log_print_debug("Number: [%d]\n", i);  // it will not be printed
            default:
                log_print_info("Number: [%d]\n", i);
        }            
    }

    // Enable debug messages. Please, call configuration functions PRIOR TO creating threads, if your app is multi-threaded
    log_set_level(LOG_MSG_DBG);
    log_print_debug("Example done\n");  // Now, it will be printed

    //... Rest of your application's code
    
    return 0;
}