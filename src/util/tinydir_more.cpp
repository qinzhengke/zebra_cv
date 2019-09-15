#include "tinydir_more.hpp"

typedef enum {
    TINYDIR_MORE_NON_ITERATIVE,
    TINYDIR_MORE_ITERATIVE
} TinyDirMoreSearchMode;

static  zcv::StringList
searchFilesIterativeByPattern(std::string path,
                              std::string pattern,
                              TinyDirMoreSearchMode mode)
{
    zcv::StringList folderStack, matchedFileList;
    folderStack.push_back(path);
    std::regex e(pattern.c_str());
    while(!folderStack.empty())
    {
        tinydir_dir dir;
        tinydir_open(&dir, folderStack.back().c_str());
        folderStack.pop_back();
        std::smatch sm;
        while(dir.has_next)
        {
            tinydir_file entry;
            tinydir_readfile(&dir, &entry);
            std::string entry_str = std::string(entry.path);
            std::string entry_name = std::string(entry.name);
            if(entry.is_dir)
            {
                if(TINYDIR_MORE_ITERATIVE == mode)
                {
                    folderStack.push_back(entry_str);
                }
            }
            else
            {
                if(regex_match(entry_name, sm, e))
                {
                    matchedFileList.push_back(entry_name);
                }
            }

            tinydir_next(&dir);
        }
    }
    std::sort(matchedFileList.begin(), matchedFileList.end());

    return matchedFileList;
}

zcv::StringList
searchFilesByPattern(std::string path, std::string pattern)
{
    return searchFilesIterativeByPattern(path, pattern,
                                         TINYDIR_MORE_NON_ITERATIVE);
}

zcv::StringList
searchFilesIterativeByPattern(std::string path, std::string pattern)
{
    return searchFilesIterativeByPattern(path, pattern,
                                         TINYDIR_MORE_ITERATIVE);
}
