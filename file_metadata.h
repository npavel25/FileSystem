#ifndef FILE_METADATA_H
#define FILE_METADATA_H

#include "user.h"

#include<iostream>

namespace My {

class FileMetaData
{
    //int create_dt;
    User& _owner;
    //last_modified_dt;
    //created_by
    //modified_by
    //access_rights
public:
    FileMetaData( User& owner)
                :_owner(owner)
    {}
    bool read(std::istream& istrm);
    bool write(std::ostream& ostrm);
    size_t size() const { return _owner.name().size(); }

};

}
#endif
