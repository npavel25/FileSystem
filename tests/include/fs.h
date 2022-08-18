#ifndef FS_H
#define FS_H


//#include "file.h"
#include "metadata.h"

#include <cstdint>
#include <iostream>
#include <map>
#include <vector>

namespace My {

class FileSystem: private MetaData 
{
    /*static constexpr int MAX_SIZE = 1024*1024*256; // 256 Mb
    static constexpr int BLOCK_SIZE = 1024; //1 Kb
    static constexpr int MAGIC = 31415926;*/

public:
    FileSystem(const std::string &fileName, const std::string &fileExt)
    : _fileName(fileName)
    , _fileExt(fileExt)
    {
        /*for(int64_t i = 1; i <= MAX_SIZE / BLOCK_SIZE; ++i)
        {
            FAT[i] = 0;
        }*/
    }
    void create();
    bool read();
    void destroy();

   // bool hasEnoughFreeSpace(const File &file) {return file.size() < free_space();}

private:
    std::string getFileName () const { return _fileName + "." +_fileExt; }
    const std::string _fileName;
    const std::string _fileExt;
public:
    //block_id -> next_block_id
    //std::map <int64_t, int64_t> FAT; // what if I need 4?

    //std::vector<void> data;

};


}

#endif