#include "cr-cache-file.hpp"
#include "../../../system/sys-file.hpp"

gearoenix::core::cache::file::File::File(system::File* file)
    : file(file)
{
}

void gearoenix::core::cache::file::File::read_offsets()
{
    file->read(offsets);
}
