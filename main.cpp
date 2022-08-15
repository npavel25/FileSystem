#include "fs.h"

#include <filesystem>

int main()
{
    //C:\\Users\\pnikolae\\Documents\\LevelUP\\CppII\\myfs
    std::string mypath = ".\\testfilesys3";
    My::FileSystem fs(".\\testfilesys3", "myfs");
    fs.create();
    if(std::filesystem::exists(mypath + ".myfs"))
    {
        std::cout << "Test filesystem has been succesfully created. " << std::endl;
    }
    else 
    {
        std::cout << "Test filesystem has NOT been created. " << std::endl;
    };
    /*if(fs.read()) 
    {
        std::cout << "File system has been successfully read." << std::endl;
    }*/
    //fs.destroy();
    return 0;
}