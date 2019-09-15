#ifndef __ZCV_FILE_OP__
#define __ZCV_FILE_OP__

#include <string>
#include "zcv_log.h"
#include "basic_ret_code.h"

#ifdef __linux__
#define ZCV_PATH_SEP std::string("/")
#define ZCV_PATH_SEP_CHAR '/'
#elif defined _WIN32
#define ZCV_PATH_SEP std::string("\\")
#define ZCV_PATH_SEP_CHAR '\\'
#endif

namespace zcv {

static inline std::string autoCompleteSlash(std::string path)
{
    if("" == path || ZCV_PATH_SEP_CHAR == path.back())
    {
        return path;
    }
    return path + ZCV_PATH_SEP;
}

static inline zcv_ret_code_t createFolder(std::string path)
{
    int st = 0;
    st = system(("mkdir -p " + path).c_str());
    if(0 != st)
    {
        return ZCV_RET_CODE_MAKE(ZCV_RET_ERROR, ZCV_CREATE_FOLDER_FAIL);
    }
    return ZCV_RET_OK;
}

static inline zcv_ret_code_t createFile(std::string path)
{
    int st = 0;

#ifdef __linux__
    st = system(("touch " + path).c_str());
#elif define _WIN32
    st = -1;
#endif
    if(0 != st)
    {
        return ZCV_RET_CODE_MAKE(ZCV_RET_ERROR, ZCV_CREATE_FOLDER_FAIL);
    }
    return ZCV_RET_OK;
}

}

#endif
