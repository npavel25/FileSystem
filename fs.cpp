#include "file.h"
#include "fs.h"

#include <fstream>
#include <cstdio>

namespace My {

void FileSystem::create()
{
    std::fstream fstrm;
    fstrm.open(getFileName(), std::fstream::out | std::fstream::binary);
    if(fstrm.is_open())
    {
        //fs.write((char*)&MAGIC, sizeof(MAGIC));
        
        _blocks.resize(MAX_SIZE / BLOCK_SIZE + 1);
        for (auto& elem: _blocks)
        {
            elem.resize(BLOCK_SIZE);
            std::fill(elem.begin(), elem.end(), 0);
            fstrm.write(reinterpret_cast<const char*>(elem.data()), elem.size());

        }
        fstrm.seekp(0);
        MetaData::write(fstrm);
        
        /*uint64_t j = 0;
        for (int i=0; i < MAX_SIZE / sizeof(j); ++i)
        {
          fstrm.write((char*)&j, sizeof(j));
        }*/
        std::cout << "File System has been successfully created." << std::endl;
    }
    fstrm.close();
}

bool FileSystem::read()
{
    /*std::fstream fs;
    fs.open(getFileName(), std::fstream::in | std::fstream::binary);
    if(fs.is_open())
    {
        int magic = 0;
        fs.read((char*)&magic, sizeof(magic));
        return magic == MAGIC;
    }
    else return false;*/

    std::fstream fs;
    fs.open(getFileName(), std::fstream::in | std::fstream::binary);
    if(fs.is_open())
    {
        return MetaData::read(fs);
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
//candidate for inline?
bool FileSystem::hasEnoughFreeSpace(const File &file) 
{ 
    return file.size() < free_space(); 
}

std::shared_ptr<File> FileSystem::create_file(std::string name)
{

}

void FileSystem::remove_file(const std::string& name)
{
    auto iter = _files.find(name);
    if (iter != _files.end())
    {
        int64_t start_idx = iter->second;
        clear_FAT(start_idx);
        _files.erase(iter);
        
        std::fstream fstrm;
        fstrm.open(getFileName(), std::fstream::out | std::fstream::binary);
        if(fstrm.is_open())
        {
            MetaData::write(fstrm);
        }
    }

}

}