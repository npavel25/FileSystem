#include "fs.h"
#include "metadata.h"
#include "user.h"

//#include <filesystem>


int main()
{
    //C:\\Users\\pnikolae\\Documents\\LevelUP\\CppII\\myfs
    std::string mypath = ".\\testfilesys3";
    My::FileSystem fs(".\\testfilesys3", "myfs");
    fs.create();
   /* if(std::filesystem::exists(mypath + ".myfs"))
    {
        std::cout << "Test filesystem has been succesfully created. " << std::endl;
    }
    else 
    {
        std::cout << "Test filesystem has NOT been created. " << std::endl;
    };*/
    /*if(fs.read()) 
    {
        std::cout << "File system has been successfully read." << std::endl;
    }*/
    //fs.destroy();

    My::MetaData meta;
    std::cout << "Free space in meta: " << meta.free_space() << std::endl;
    std::cout << "size of meta: " << meta.size() << std::endl;
    meta.info();

    My::Root &root = My::Root::Instance();
    if(root.is_root())
    {
        std::cout << "Hello, I am root!" << std::endl;
        My::FileSystem& rootFS = root.create_filesystem();
    }
    std::shared_ptr<My::User> currentUser = root.createUser("nikolaev");
    std::cout << "Hello, I am " << currentUser->name() << std::endl;

    std::shared_ptr<My::User> currentUser2 = root.createUser("nikolaev");
    std::cout << "Hello, I am " << currentUser2->name() << std::endl;
    

    return 0;
}