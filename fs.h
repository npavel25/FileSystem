#ifndef FS_H
#define FS_H


//#include "file.h"
#include "metadata.h"

#include <cstdint>
#include <iostream>
#include <map>
#include <memory>
#include <vector>

namespace My {
class File;

class FileSystem: private MetaData 
{
    /*static constexpr int MAX_SIZE = 1024*1024*256; // 256 Mb
    static constexpr int BLOCK_SIZE = 1024; //1 Kb
    static constexpr int MAGIC = 31415926;*/

public:
    using block_t = std::vector<uint8_t>;
    
    FileSystem(const std::string &fileName, const std::string &fileExt)
    : _fileName(fileName)
    , _fileExt(fileExt)
    {}

    void create();
    bool read();
    void destroy();

    std::shared_ptr<File> create_file(std::string name);
    void flush(File& file);
    void remove_file();

    bool hasEnoughFreeSpace(const File &file);
    std::string getFileName () const { return _fileName + "." +_fileExt; }

private:
    
    const std::string _fileName;
    const std::string _fileExt;
    std::vector<block_t> _blocks;   

};


}

#endif