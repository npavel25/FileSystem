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
        // additional block is used to store MetaData
        _blocks.resize((MAX_SIZE / BLOCK_SIZE) + 1);
        //std::cout << "Number of blocks: " << _blocks.size() << std::endl;
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

std::shared_ptr<File> FileSystem::create_file(User& owner, const std::string& name)
{
    std::shared_ptr<File> file { new File(owner, name, *this)};
    _files[name] = file->start_block_id;
    return file;
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

void FileSystem::flush(File& file)
{
    if(hasEnoughFreeSpace(file))
    {
        auto iter = first_empty_block();
        int64_t start_idx = iter->first;
        _files[file._name] = start_idx;

        std::fstream fstr(getFileName(), std::fstream::out | std::fstream::binary);
        
        //write metadata and initial part of file
        //file.

        //for (size_t number_of_blocks = file.size() / BLOCK_SIZE; number_of_blocks; --number_of_blocks)
        size_t number_of_blocks = file.size() / BLOCK_SIZE + 1;
        do
        {
            write_block(fstr, start_idx);
            if(number_of_blocks>1)
            {
                auto itr = first_empty_block();
                int64_t idx = iter->first;
                _FAT[start_idx] = idx;
                start_idx = idx;
            }
            else 
            {
                _FAT[start_idx] = -1;
            }
            
            --number_of_blocks;
        } while(number_of_blocks);
        
        MetaData::write(fstr);
    }
    else
    {
        std::cout << "File System does not have enough free space to store file " << file.name() << std::endl;
    }

}

bool FileSystem::write_block(std::ostream& ostr, int64_t idx)
{
    if(ostr)
    {
        ostr.seekp(BLOCK_SIZE * idx);
        ostr.write(reinterpret_cast<const char*>(_blocks[idx].data()), _blocks[idx].size());
    }
    return ostr.good();

}

}