#include "file.h"

#include <cstring>

namespace My {


void File::open(const std::string& name)
{
    //auto iter = fs._files.find(name);

}
void File::read()
{
    //TODO: change to find()
    //for(int64_t next_block_id = start_block_id; next_block_id != -1; next_block_id = fs._FAT.at(next_block_id)) // fs.FAT[] ??
    {
        //read_block(next_block_id);
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

}