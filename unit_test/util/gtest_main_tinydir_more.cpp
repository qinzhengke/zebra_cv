#include <gtest/gtest.h>
#include "zcv_util.hpp"

using namespace std;
using namespace zcv;

static bool compareStringList(const StringList &l1, const StringList &l2)
{
    if(l1.size() != l2.size())
    {
        return false;
    }

    for(int i=0; i<l1.size(); i++)
    {
        if(l1[i] != l2[i])
        {
            return false;
        }
    }

    return true;
}

TEST(searchFilesTest, PostiveNos)
{
    string test_dir = "tinydir_more_test" + ZCV_PATH_SEP;

    StringList files = searchFilesByPattern(test_dir, "abc(.*)xyz(.*)");
    StringList filesTruth = {"abc1234xyz.b",
                            "abc123xyz.b",
                            "abc12xyz.a",
                            "abc1xyz.a"};
    ASSERT_EQ(compareStringList(files, filesTruth), true);
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    string test_dir = "tinydir_more_test" + ZCV_PATH_SEP;
    createFolder(test_dir);
    createFile(test_dir + "abc1xyz.a");
    createFile(test_dir + "abc12xyz.a");
    createFile(test_dir + "abc123xyz.b");
    createFile(test_dir + "abc1234xyz.b");

    string test_dir_a = test_dir + "a" + ZCV_PATH_SEP;
    createFolder(test_dir_a);
    createFile(test_dir_a + "abc1xyz.a");
    createFile(test_dir_a + "abc12xyz.a");
    createFile(test_dir_a + "abc123xyz.b");
    createFile(test_dir_a + "abc1234xyz.b");

    return RUN_ALL_TESTS();
}


