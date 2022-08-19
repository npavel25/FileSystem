#ifndef FILE_H
#define FILE_H

#include "file_metadata.h"
#include "fs.h"
//#include "user.h"

#include <memory>
#include <vector>
//#include <cstdint>
//#include <iostream>

namespace My {
class FileSystem;

class File: private FileMetaData
{
    friend class FileSystem;

public:
    
    void open(const std::string& name);
    void read();
    void write(const void* data, size_t size);
    void append(const void* data, size_t size);
    void flush();
    size_t size() const { return FileMetaData::size() + _size; }
    std::string name() { return _name; }

private:

    File( User& owner, std::string name, FileSystem& filesystem)
        : FileMetaData(owner) 
        , _name(std::move(name))
        , _filesystem(filesystem)
    {}
    File();

    FileSystem& _filesystem;
    //FileMetaData fileMetaData;
    std::string _name;
    size_t _size = 0;
    int64_t start_block_id = -1;
    std::vector<uint8_t> _data;
};

}
#endif