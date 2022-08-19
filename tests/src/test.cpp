#include "gtest/gtest.h"
#include "buddy.h"

#include "file.h"
#include "fs.h"
#include "user.h"

#include <fstream>
//#include <filesystem>
#include <string>

TEST(FileSystem_test, create_test)
{
  static const std::string mypath = "C:\\Users\\pnikolae\\Documents\\LevelUP\\CppII\\myfs\\testfilesys2";
  //C:\\Users\\pnikolae\\Documents\\LevelUP\\CppII\\myfs
  
  //EXPECT_FALSE(std::experimental::filesystem::exists(mypath + ".myfs"));
  std::ifstream infile1(mypath + ".myfs");
  EXPECT_FALSE(infile1.good());
  
   My::FileSystem fs(mypath, "myfs");
   fs.create();
   std::ifstream infile2(mypath + ".myfs");
  EXPECT_TRUE(infile2.good());
}

TEST(FileSystem_test, destroy_test)
{
  static const std::string mypath = "C:\\Users\\pnikolae\\Documents\\LevelUP\\CppII\\myfs\\testfilesys2destr";

  My::FileSystem fs(mypath, "myfs");
  fs.create();
  std::ifstream infile2(mypath + ".myfs");
  EXPECT_TRUE(infile2.good());
  infile2.close();

  fs.destroy();
  std::ifstream infile3(mypath + ".myfs");
  EXPECT_FALSE(infile3.good());

}

TEST(FileSystem_test, read_test)
{
  static const std::string mypath = "C:\\Users\\pnikolae\\Documents\\LevelUP\\CppII\\myfs\\testfilesys2read";
  {
    My::FileSystem fs(mypath, "myfs");
    fs.create();
  }
  My::FileSystem fs2(mypath, "myfs");
  //fs.create();
  EXPECT_TRUE(fs2.read());

  fs2.destroy();

  std::ifstream infile3(mypath + ".myfs");
  EXPECT_FALSE(infile3.good());

}

TEST(File_test, write_test)
{
  static const std::string mypath = "C:\\Users\\pnikolae\\Documents\\LevelUP\\CppII\\myfs\\testfilesys2write";
  
  My::FileSystem fs(mypath, "myfs");
  fs.create();
  My::User user("test");
  std::shared_ptr<My::File> file1 = fs.create_file(user, "file1");
  file1->write("aaa", 3);
  
  std::shared_ptr<My::File> file2 = fs.create_file(user, "file2");
  file2->write("bbbb", 4);

  file1->flush();
  file2->flush();

}
/*
TEST(TEST_FOR_TASK, TEST2)
{
  EXPECT_TRUE(buddyStrings("ba","ab"));
}*/