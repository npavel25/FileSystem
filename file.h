#ifndef FILE_H
#define FILE_H

#include "fs.h"

//#include <cstdint>
//#include <iostream>

namespace My {

class FileMetaData;
class File
{
    friend class FileSystem;

public:
    File(const std::string &name, int size);
    void read();
    void write();
    void flush();
    size_t size() const { return _size; }

private:
    const FileSystem fs;
    //FileMetaData fileMetaData;
    std::string _name;
    size_t _size;
    int64_t start_block_id = -1;
    void *_data;
};

class FileMetaData
{
    int create_dt;
    //last_modified_dt;
    //created_by
    //modified_by
    //access_rights

};

}
#endif