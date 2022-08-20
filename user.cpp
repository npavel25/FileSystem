#include "fs.h"
#include "user.h"

namespace My {

std::shared_ptr<User> Root::createUser(std::string name)
{
    _users.emplace_back(new User(std::move(name))); //make_share, check if exist emplace to retrun iterator
    return _users.back();
}

FileSystem& Root::create_filesystem()
{
    static FileSystem fs(".\\rootfilesys", "myfs");
    return fs;
}

}