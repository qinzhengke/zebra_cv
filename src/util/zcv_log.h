#ifndef __ZCV_LOG_H__
#define __ZCV_LOG_H__

#include "zcv_defines.h"

#include <stdint.h>

typedef int32_t zcv_ret_code_t;

typedef enum
{
    ZCV_RET_FATAL = -2,
    ZCV_RET_ERROR = -1,
    ZCV_RET_OK = 0,
    ZCV_RET_WARNING = 1,
} zcv_ret_type_t;

#define ZCV_RET_CODE_MAKE(type,rec_code) (((type)<<28) | (rec_code))

extern char *g_basic_ret_code_string[];

#ifdef __cplusplus
extern "C"{
#endif

void zcv_log_report(zcv_ret_type_t ret_type, int32_t ret_code,
                    const char *file_name, const char *func_name,
                    int32_t line_number, const char *str_fmt, ...);

#ifdef __cplusplus
}
#endif

#define ZCV_REPORT_MORE(ret_type,ret_code,str_fmt,...)                         \
    do{                                                                        \
        zcv_log_report((ret_type), (ret_code), __FILENAME__, __ZCV_FUNCTION__,     \
        __LINE__, (str_fmt), ##__VA_ARGS__);                                   \
} while(0)

#define ZCV_REPORT(ret_type,ret_code)                         \
    do{                                                                        \
        zcv_log_report((ret_type), (ret_code), __FILENAME__, __ZCV_FUNCTION__,     \
        __LINE__, "");                                   \
} while(0)

#endif
