#ifndef USER_H
#define USER_H

#include <memory>
#include <string>
#include <vector>

namespace My {

class FileSystem;

class User
{
public:
    User(std::string name)
    :_name(std::move(name))
    {}
    
    std::string name() const { return _name; }
    virtual bool is_root() { return false; };

private:
    std::string _name;
};

class Root: public User
{
public:
    static Root& Instance()
    {
        static Root theRoot;
        return theRoot;
    }
    
    std::shared_ptr<User> createUser(std::string name);
    bool is_root() { return true; };
    FileSystem& create_filesystem();

    Root(const Root& root) = delete;
    Root& operator=(const Root& root) = delete;

private:
    Root()
    :User("root")
    {}

    std::vector<std::shared_ptr<User>> _users;
};

}

#endif