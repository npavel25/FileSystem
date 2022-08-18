#ifndef METADATA_H
#define METADATA_H

#include <algorithm>
#include <map>

namespace My {

class MetaData
{
    static constexpr int MAGIC = 31415926;
    static constexpr int MAX_SIZE = 1024*1024*256; // 256 Mb
    static constexpr int BLOCK_SIZE = 1024; //1 Kb
    

public:
    MetaData()
    {
        for(int64_t i = 1; i <= MAX_SIZE / BLOCK_SIZE; ++i)
        {
            FAT[i] = 0;
        }
    }
    bool read(std::istream istrm);
    bool write(std::ostream ostrm);
    int size() { return sizeof(MetaData); }
    size_t free_space() const {return BLOCK_SIZE * std::count_if(FAT.begin(), FAT.end(), 
                                              [](std::pair<int64_t, int64_t> p) { return 0 == p.second;}
                                              ); }
    void info() const;

private:
    std::map <int64_t, int64_t> FAT;
};

}

#endif