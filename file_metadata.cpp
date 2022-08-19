#include "file_metadata.h"

namespace My {


bool FileMetaData::read(std::istream& istrm)
{
    if(istrm)
    {
        size_t ownername_size = 0;
        istrm.read(reinterpret_cast<char*>(&ownername_size), sizeof(ownername_size));
        std::string ownername;
        istrm.read(reinterpret_cast<char*>(&ownername), ownername_size);
    }
    return istrm.good();
}

bool FileMetaData::write(std::ostream& ostrm)
{
    if (ostrm)
    {
        std::string name = _owner.name();
        size_t size = name.size();
        ostrm.write(reinterpret_cast<const char*>(&size), sizeof(size));
        ostrm.write(reinterpret_cast<const char*>(name.data()), size);
    }
    return ostrm.good();
}

}