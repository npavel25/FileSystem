#include "fs.h"

#include <fstream>
#include <cstdio>

namespace My {

void FileSystem::create()
{
    std::fstream fs;
    fs.open(getFileName(), std::fstream::out | std::fstream::binary);
    if(fs.is_open())
    {
        fs.write((char*)&MAGIC, sizeof(MAGIC));
        uint64_t j = 0;
        for (int i=0; i < MAX_SIZE / sizeof(j); ++i)
        {
          fs.write((char*)&j, sizeof(j));
          //if (i%100 == 0) std::cout << "i:" << i << std::endl;
        }
        std::cout << "File System has been successfully created." << std::endl;
    }
    fs.close();
}

bool FileSystem::read()
{
    std::fstream fs;
    fs.open(getFileName(), std::fstream::in | std::fstream::binary);
    if(fs.is_open())
    {
        int magic = 0;
        fs.read((char*)&magic, sizeof(magic));
        return magic == MAGIC;
    }
    else return false;

}

void FileSystem::destroy()
{
    
    if (0 == remove( getFileName().c_str() ))
    {
        std::cout << "File " << getFileName() << "has been sucessfully deleted." << std::endl;
    }
    else
    {
        std::cerr << "Could not delete file " << getFileName() << std::endl;

    }
}

}