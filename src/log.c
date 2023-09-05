#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <stdbool.h>
#include <unistd.h>

#include "log.h"

// Define ANSI colors for the serial console
#define ANSI_COLOR_RED              "\x1b[31m"
#define ANSI_COLOR_GREEN            "\x1b[32m"
#define ANSI_COLOR_YELLOW           "\x1b[33m"
#define ANSI_COLOR_BLUE             "\x1b[34m"
#define ANSI_COLOR_MAGENTA          "\x1b[35m"
#define ANSI_COLOR_CYAN             "\x1b[36m"
#define ANSI_COLOR_WHITE            "\x1b[37m"

#define ANSI_COLOR_BRIGHT_RED       "\x1b[91m"
#define ANSI_COLOR_BRIGHT_GREEN     "\x1b[92m"
#define ANSI_COLOR_BRIGHT_YELLOW    "\x1b[93m"
#define ANSI_COLOR_BRIGHT_BLUE      "\x1b[94m"
#define ANSI_COLOR_BRIGHT_MAGENTA   "\x1b[95m"
#define ANSI_COLOR_BRIGHT_CYAN      "\x1b[96m"
#define ANSI_COLOR_BRIGHT_WHITE     "\x1b[97m"

#define ANSI_COLOR_RESET            "\x1b[0m"

// Define the abbreviation for the message category
#define CRIT_ABBREV     "[Crit]"
#define ERR_ABBREV      "[Err]"
#define WARN_ABBREV     "[Warn]"
#define INFO_ABBREV     "[Info]"
#define DBG_ABBREV      "[Debug]"

// Define maximum path size for a log file
#define MAX_PATH_SIZE   256

// Define the NULL character
#define NULL_CHAR  '\0'

// attributes of the log library
typedef struct {
    LOG_MSG_CATEGORY log_level;
    char log_file_name[MAX_PATH_SIZE];
    size_t log_file_size;
    bool log_colors_enabled;
} log_attributes_t;

// setup the initial value of log level, LOG_MSG_INFO by default. No log file, stdout logs, colors enabled.
static log_attributes_t log_atts = {.log_level = LOG_MSG_INFO, 
                                    .log_file_name[0] = NULL_CHAR, 
                                    .log_file_size = 0,
                                    .log_colors_enabled = true};


/**
 * @brief Get the Local Date and Time in a fixed string format "YYYY-MM-DD - hh:mm:ss"
 * 
 * @param time_string 
 * @return size_t 
 */
static size_t get_local_date_and_time(char* time_string)
{
    size_t ret = -1;

    if (time_string) 
    {
        time_t     now;
        struct tm *tm;

        /* get local time */
        now = time(NULL);

        /* format local time */
        tm = localtime(&now);
        ret = sprintf(time_string,"%04d/%02d/%02d - %02d:%02d:%02d", tm->tm_year+1900, tm->tm_mon+1, 
                tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec);
    }

    return ret;
}

/**
 * @brief This is the actual printf wrapper. Depending on LOG_MSG_CATEGORY, it will print
 *        a different message format (labels, colors...) along with the current date and time.
 * 
 * @param category 
 * @param fmt 
 * @param args 
 */
static void print_internal_va(LOG_MSG_CATEGORY category, const char* fmt, va_list args)
{
    FILE* log_file;
    bool log_file_flg = false;

    // Check if logs shall be written into a log file
    if (log_atts.log_file_name[0] != NULL_CHAR && log_atts.log_file_size > 0)
    {
        log_file = fopen(log_atts.log_file_name, "a");
        if (!log_file)
        {
            // error at opening/creating the log file. Log messages will be redirected to stdout
            log_enable_colors();
            log_atts.log_file_name[0] = NULL_CHAR;
            log_atts.log_file_size = 0;

            // get local time and date for this log message
            char time[80];
            get_local_date_and_time(time);
            printf("%s[%s] [%s] Log file cannot be opened. Printing logs to the stdout... %s\n", ANSI_COLOR_BRIGHT_YELLOW, WARN_ABBREV, time, ANSI_COLOR_RESET);
        }     
        else
            log_file_flg = true;
    }

    // Print the log message either in a log file or in the stdout, depending on log_file_flg. Also check colors enabled or not
    switch(category)
    {
        case LOG_MSG_CRIT:
            if (log_atts.log_colors_enabled) {
                log_file_flg ? fprintf(log_file,"%s[%s] [%s:%d] ", ANSI_COLOR_RED, CRIT_ABBREV, __FILE__, __LINE__) : 
                printf("%s[%s] [%s:%d] ", ANSI_COLOR_RED, CRIT_ABBREV, __FILE__, __LINE__);
            } else {
                log_file_flg ? fprintf(log_file,"[%s] [%s:%d] ", CRIT_ABBREV, __FILE__, __LINE__) : 
                printf("[%s] [%s:%d] ", CRIT_ABBREV, __FILE__, __LINE__);
            }
        break;

        case LOG_MSG_ERR:
            if (log_atts.log_colors_enabled) {
                log_file_flg ? fprintf(log_file, "%s[%s] [%s:%d] ", ANSI_COLOR_BRIGHT_RED, ERR_ABBREV, __FILE__, __LINE__) :
                printf("%s[%s] [%s:%d] ", ANSI_COLOR_BRIGHT_RED, ERR_ABBREV, __FILE__, __LINE__);
            } else {
                log_file_flg ? fprintf(log_file, "[%s] [%s:%d] ", ERR_ABBREV, __FILE__, __LINE__) :
                printf("[%s] [%s:%d] ", ERR_ABBREV, __FILE__, __LINE__);
            }
        break;

        case LOG_MSG_WARN:
            if (log_atts.log_colors_enabled) {
                log_file_flg ? fprintf(log_file, "%s[%s] ", ANSI_COLOR_BRIGHT_YELLOW, WARN_ABBREV) :
                printf("%s[%s] ", ANSI_COLOR_BRIGHT_YELLOW, WARN_ABBREV);
            } else {
                log_file_flg ? fprintf(log_file, "[%s] ", WARN_ABBREV) :
                printf("[%s] ", WARN_ABBREV);
            }
        break;

        case LOG_MSG_INFO:
            if (log_atts.log_colors_enabled) {
                log_file_flg ? fprintf(log_file, "%s[%s] ", ANSI_COLOR_BRIGHT_GREEN, INFO_ABBREV) :
                printf("%s[%s] ", ANSI_COLOR_BRIGHT_GREEN, INFO_ABBREV);
            } else {
                log_file_flg ? fprintf(log_file, "[%s] ", INFO_ABBREV) :
                printf("[%s] ", INFO_ABBREV);
            }
        break;

        case LOG_MSG_DBG:
        default:
            if (log_atts.log_colors_enabled) {
                log_file_flg ? fprintf(log_file, "%s[%s] [%s:%d] ", ANSI_COLOR_RESET, DBG_ABBREV, __FILE__, __LINE__) :
                printf("%s[%s] [%s:%d] ", ANSI_COLOR_BRIGHT_WHITE, DBG_ABBREV, __FILE__, __LINE__);
            } else {
                log_file_flg ? fprintf(log_file, "[%s] [%s:%d] ", DBG_ABBREV, __FILE__, __LINE__) :
                printf("[%s] [%s:%d] ", DBG_ABBREV, __FILE__, __LINE__);
            }
        break;
    }

    // get local time and date
    char time[80];
    get_local_date_and_time(time);

    if (log_file_flg)
    {
        fprintf(log_file, "[%s] ", time);
        vfprintf(log_file, fmt, args); 
        if (log_atts.log_colors_enabled)
            fprintf(log_file ,"%s", ANSI_COLOR_RESET);
        fclose(log_file);
    }
    else
    {
        printf("[%s] ", time);
        vprintf(fmt, args);    
        printf("%s", ANSI_COLOR_RESET);
    }

    va_end(args);
    return;
}


// Functions about library attributes
void log_set_level(LOG_MSG_CATEGORY log_level)
{
    if (log_level >= LOG_MSG_NONE && log_level <= LOG_MSG_DBG)
        log_atts.log_level = log_level;
}

LOG_MSG_CATEGORY log_get_level()
{
    return log_atts.log_level;
}

void log_set_file(const char* filepath, size_t filepath_size)
{
    // Checks if the file name is valid and if the file exists in the filesystem
    if (filepath && filepath_size <= MAX_PATH_SIZE)
    {
        log_atts.log_file_name[0] = NULL_CHAR;
        snprintf(log_atts.log_file_name, filepath_size, "%s", filepath);
        log_atts.log_file_size = filepath_size;
        log_disable_colors();
        
    }
    else
        log_print_warning("Given log file name is not valid. Logs shall be printed to the stdout.\n");
}

void log_set_file_with_color_text(const char* filepath, size_t filepath_size)
{
    // Checks if the file name is valid and if the file exists in the filesystem
    if (filepath && filepath_size <= MAX_PATH_SIZE)
    {
        log_atts.log_file_name[0] = NULL_CHAR;
        snprintf(log_atts.log_file_name, filepath_size, "%s", filepath);
        log_atts.log_file_size = filepath_size;
        log_enable_colors();
    }
    else
        log_print_warning("Given log file name is not valid. Logs shall be printed to the stdout.\n");
}

void log_enable_colors()
{
    log_atts.log_colors_enabled = true;
}

void log_disable_colors()
{
    log_atts.log_colors_enabled = false;
    printf("%s", ANSI_COLOR_RESET);
}

// print function definitions
void log_print_critical(const char* fmt, ...)
{
    if (fmt && log_atts.log_level >= LOG_MSG_CRIT)
    {
        va_list args;
        va_start(args, fmt);
        print_internal_va(LOG_MSG_CRIT, fmt, args);
        va_end(args);
    }
}


void log_print_error(const char* fmt, ...)
{
    if (fmt && log_atts.log_level >= LOG_MSG_ERR)
    {
        va_list args;
        va_start(args, fmt);
        print_internal_va(LOG_MSG_ERR, fmt, args);
        va_end(args);
    }
}


void log_print_warning(const char* fmt, ...)
{
    if (fmt && log_atts.log_level >= LOG_MSG_WARN)
    {
        va_list args;
        va_start(args, fmt);
        print_internal_va(LOG_MSG_WARN, fmt, args);
        va_end(args);
    }
}


void log_print_info(const char* fmt, ...)
{
    if (fmt && log_atts.log_level >= LOG_MSG_INFO)
    {
        va_list args;
        va_start(args, fmt);
        print_internal_va(LOG_MSG_INFO, fmt, args);
        va_end(args);
    }
}


void log_print_debug(const char* fmt, ...)
{
    if (fmt && log_atts.log_level >= LOG_MSG_DBG)
    {
        va_list args;
        va_start(args, fmt);
        print_internal_va(LOG_MSG_DBG, fmt, args);
        va_end(args);
    }
}