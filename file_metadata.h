#ifndef FILE_METADATA_H
#define FILE_METADATA_H

#include<iostream>

namespace My {

class FileMetaData
{
    int create_dt;
    //User &owner;
    //last_modified_dt;
    //created_by
    //modified_by
    //access_rights

    bool read(std::istream& istrm);
    bool write(std::ostream& ostrm);

};

}
#endif
