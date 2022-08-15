#include "file.h"

namespace My {

void File::read()
{
    //TODO: change to find()
    for(int64_t next_block_id = start_block_id; next_block_id != -1; next_block_id = fs.FAT.at(next_block_id)) // fs.FAT[] ??
    {
        //read_block(next_block_id);
    }
}

}