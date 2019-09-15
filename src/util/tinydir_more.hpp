#ifndef __TINYDIR_MORE_HPP__
#define __TINYDIR_MORE_HPP__

#include <vector>
#include <regex>
#include "zcv_util_types.h"
#include "../../3rd-party/tinydir.h"

zcv::StringList searchFilesByPattern(std::string path, std::string regex);

zcv::StringList searchFilesIterativeByPattern(std::string path, std::string
                                                pattern);

#endif
