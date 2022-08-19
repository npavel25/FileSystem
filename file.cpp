#include "file.h"

#include <cstring>
#include <fstream>

namespace My {


void File::open(const std::string& name)
{
    auto iter = _filesystem._files.find(name);
    if(iter != _filesystem._files.end())
    {
        start_block_id = iter->second;
    }
}
void File::read()
{
    //1. read file meta data - skip for now
    //std::vector<uint8_t> _data;
    int64_t idx = start_block_id;
    int block_count = 0;

    while(idx != -1)
    {
        //read_block(next_block_id);
        _data.resize((block_count+1)*_filesystem.BLOCK_SIZE);
        memcpy(_data.data() + block_count*_filesystem.BLOCK_SIZE, _filesystem._blocks[idx].data(), _filesystem.BLOCK_SIZE);
        idx = _filesystem._FAT[idx];
    }
}

void File::write(const void *data, size_t size)
{
    _size = size;
    _data.reserve(size);
    memcpy(_data.data(), data, size);
    //_data.shrink_to_fit(); DO I need it?

}

void File::append(const void *data, size_t size)
{
    size_t old_size = _data.size();
    _size = old_size + size;
    _data.reserve(_size);
    memcpy(_data.data()+old_size, data, size);
}

void File::flush()
{
    _filesystem.flush(*this);
}

}