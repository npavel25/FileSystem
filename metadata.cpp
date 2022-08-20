#include "metadata.h"

#include <fstream>
#include <iostream>


namespace My {
bool MetaData::write(std::ostream& ostrm)
{
    if (ostrm)
    {
        ostrm.write(reinterpret_cast<const char*>(&MAGIC), sizeof(MAGIC));
        ostrm.write(reinterpret_cast<const char*>(&MAX_SIZE), sizeof(MAX_SIZE));
        ostrm.write(reinterpret_cast<const char*>(&BLOCK_SIZE), sizeof(BLOCK_SIZE));


        size_t fat_size = _FAT.size();
        ostrm.write(reinterpret_cast<const char*>(&fat_size), sizeof(size_t));
        for(const auto& [key, value]: _FAT)
        {
            ostrm.write(reinterpret_cast<const char*>(&key), sizeof(key));
            ostrm.write(reinterpret_cast<const char*>(&value), sizeof(value));
        }

        size_t files_size = _files.size();
        ostrm.write(reinterpret_cast<const char*>(&files_size), sizeof(size_t));
        for(const auto& [filename, start_idx]: _files)
        {
            size_t filename_size = filename.size();
            ostrm.write(reinterpret_cast<const char*>(&filename_size), sizeof(size_t));
            ostrm.write(reinterpret_cast<const char*>(&filename), filename_size);
            ostrm.write(reinterpret_cast<const char*>(&start_idx), sizeof(start_idx));
        }
    }
    return ostrm.good();
}

bool MetaData::read(std::istream& istrm)
{
    if(istrm)
    {
        int magic = 0;
        istrm.read(reinterpret_cast<char*>(&magic), sizeof(magic));
        if (magic != MAGIC)
         return false;
        
        int max_size = 0;
        istrm.read(reinterpret_cast<char*>(&max_size), sizeof(max_size));
        int block_size = 0;
        istrm.read(reinterpret_cast<char*>(&block_size), sizeof(block_size));
        
        size_t fat_size = 0;
        istrm.read(reinterpret_cast<char*>(&fat_size), sizeof(fat_size));
        for (size_t i = 0; i<fat_size; ++i)
        {
            int64_t key = 0, value = 0;
            istrm.read(reinterpret_cast<char*>(&key), sizeof(key));
            istrm.read(reinterpret_cast<char*>(&value), sizeof(value));
            _FAT[key] = value;
        }

        size_t number_of_files = 0;
        istrm.read(reinterpret_cast<char*>(&number_of_files), sizeof(number_of_files));
        for (size_t i=0; i<number_of_files; ++i)
        {
            size_t filename_size = 0;
            istrm.read(reinterpret_cast<char*>(&filename_size), sizeof(filename_size));
            std::string filename;
            filename.resize(filename_size);
            istrm.read((&filename[0]), filename_size);
            int64_t start_idx = 0;
            istrm.read(reinterpret_cast<char*>(&start_idx), sizeof(start_idx));
            _files[filename] = start_idx;

        }
    }
    return istrm.good();

}


void MetaData::clear_FAT(int64_t start_idx)
{
    int64_t next_idx = 0;
    int64_t crnt_idx = start_idx;
    while(next_idx != -1)
    {
        next_idx = _FAT.at(crnt_idx);
        _FAT[crnt_idx] = 0;
        crnt_idx = next_idx;

        /*auto iter = FAT.find(crnt_idx);
        if(iter != FAT.end())
        {
            next_idx = iter->second;
            iter->second = 0;
            crnt_idx = next_idx;
        }*/
        
    }
}

void MetaData::info() const
{
    std::cout << "MAX_SIZE: " << MAX_SIZE << std::endl;
    std::cout << "BLOCK_SIZE: " << BLOCK_SIZE << std::endl;
    std::cout << "MAGIC: " << MAGIC << std::endl;
    std::cout << "Number of blocks: " << _FAT.size() << std::endl;
    std::cout << "Number of blocks from the other side: " << _files.size() << std::endl;
    std::cout << "Free space: " << free_space() << std::endl;
}
}