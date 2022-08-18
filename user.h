#ifndef USER_H
#define USER_H

#include <memory>
#include <string>
#include <vector>

namespace My {

class User
{

public:
    User(std::string name)
    :_name(std::move(name))
    {}
    
    std::string name() const { return _name; }
    bool is_root() { return false; };

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
    bool createGroup(std::string name);
    bool is_root() { return true; };
private:

    Root()
    :User("root")
    {}

public:
    Root(const Root& root) = delete;
    Root& operator=(const Root& root) = delete;

private:
    std::vector<std::shared_ptr<User>> _users;
    
};
    std::shared_ptr<User> Root::createUser(std::string name)
    {
        _users.emplace_back(new User(std::move(name)));
        return _users.back();
        //User user(name);
        //return user;

    }
/*
class Group
{
    private:
    Group();
    std::string _name;
    std::set group;

};
*/

}

#endif