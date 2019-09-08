#include "zcv_log.h"

#include <string.h>
#include <stdio.h>
#include <stdarg.h>

#define ZCV_LOG_MAX_LEN 500

void zcv_log_report(zcv_ret_type_t ret_type, int32_t ret_code,
                    const char *file_name, const char *func_name,
                    int32_t line_number, const char *str_fmt, ...)
{
    char str_ret_type[20];
    switch(ret_type)
    {
    case ZCV_RET_FATAL:
        strcpy(str_ret_type, "\033[31mFATAL\033[0m");
        break;
    case ZCV_RET_ERROR:
        strcpy(str_ret_type, "\033[31mERROR\033[0m");
        break;
    case ZCV_RET_SUCCESS:
        strcpy(str_ret_type, "");
        break;
    case ZCV_RET_WARNING:
        strcpy(str_ret_type, "\033[31mWARNING\033[0m");
        break;
    }

    va_list va;
    va_start(va, str_fmt);

    char extra_info[ZCV_LOG_MAX_LEN];
    snprintf(extra_info, ZCV_LOG_MAX_LEN, str_fmt, va);

    char str[ZCV_LOG_MAX_LEN];
    snprintf(str, ZCV_LOG_MAX_LEN, "%s,%s,%s,%s,%d", str_ret_type,
             g_basic_ret_code_string[ret_code], file_name, func_name,
             line_number);

    char str_output[ZCV_LOG_MAX_LEN];
    snprintf(str_output, ZCV_LOG_MAX_LEN, "%s,%s\n", str, extra_info);

    printf("%s", str_output);
}
