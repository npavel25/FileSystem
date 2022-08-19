#ifndef METADATA_H
#define METADATA_H

#include <algorithm>
#include <map>

namespace My {

class MetaData
{
protected:
    static constexpr int MAGIC = 31415926;
    static constexpr int MAX_SIZE = 1024;//*1024*256; // 256 Mb
    static constexpr int BLOCK_SIZE = 256;//1024; //1 Kb
    

public:
    MetaData()
    {
        for(int64_t i = 1; i <= MAX_SIZE / BLOCK_SIZE; ++i)
        {
            _FAT[i] = 0;
        }
    }
    bool read(std::istream& istrm);
    bool write(std::ostream& ostrm);
    int size() { return sizeof(MetaData); } //TODO: fix it!
    size_t free_space() const {return BLOCK_SIZE * std::count_if(_FAT.begin(), _FAT.end(), 
                                              [](std::pair<int64_t, int64_t> p) { return 0 == p.second;}
                                              ); }
    void info() const;
    void clear_FAT(int64_t start_idx);
    auto first_empty_block() {return std::find_if(_FAT.begin(), _FAT.end(), 
                                              [](auto p){return 0 == p.second;}
                                              ); };

protected:
    //block_id -> next_block_id
    std::map <int64_t, int64_t> _FAT;
    std::map <std::string, int64_t> _files;
};

}

#endif