#include "metadata.h"

#include <fstream>
#include <iostream>


namespace My {
bool MetaData::write(std::ostream ostrm)
{
    if (ostrm)
    {
        ostrm.write(reinterpret_cast<const char*>(&MAGIC), sizeof(MAGIC));
        ostrm.write(reinterpret_cast<const char*>(&MAX_SIZE), sizeof(MAX_SIZE));
        ostrm.write(reinterpret_cast<const char*>(&BLOCK_SIZE), sizeof(BLOCK_SIZE));


        size_t fat_size = FAT.size();
        ostrm.write(reinterpret_cast<const char*>(fat_size), sizeof(size_t));
        for(const auto& [key, value]: FAT)
        {
            ostrm.write(reinterpret_cast<const char*>(&key), sizeof(key));
            ostrm.write(reinterpret_cast<const char*>(&value), sizeof(value));
        }

    }

    return ostrm.good();

}

bool MetaData::read(std::istream istrm)
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
            FAT[key] = value;
        }
    }
    return istrm.good();

}

void MetaData::info() const
{
    std::cout << "MAX_SIZE: " << MAX_SIZE << std::endl;
    std::cout << "BLOCK_SIZE: " << BLOCK_SIZE << std::endl;
    std::cout << "MAGIC: " << MAGIC << std::endl;
    std::cout << "Number of blocks: " << FAT.size() << std::endl;
    std::cout << "Free space: " << free_space() << std::endl;
}
}