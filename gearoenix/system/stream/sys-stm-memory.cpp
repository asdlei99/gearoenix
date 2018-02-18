#include "sys-stm-memory.hpp"
#include "../../core/cr-build-configuration.hpp"
#include "../sys-log.hpp"
#include <cstring>

gearoenix::system::stream::Memory::Memory() {}

gearoenix::system::stream::Memory::~Memory() {}

gearoenix::core::Count gearoenix::system::stream::Memory::read(void* d, core::Count length)
{
    const core::Count sz = length + index;
    const core::Count result = sz > mem_data.size() ? mem_data.size() - index : length;
#ifdef DEBUG_MODE
    if (0 == result)
        UNEXPECTED;
#endif
    std::memcpy(d, &(mem_data[index]), result);
    index += result;
    return result;
}

gearoenix::core::Count gearoenix::system::stream::Memory::write(const void* d, core::Count length)
{
    const core::Count sz = length + index;
    if (sz > mem_data.size())
        mem_data.resize(sz);
    std::memcpy(&(mem_data[index]), d, length);
    index = sz;
    return length;
}

void gearoenix::system::stream::Memory::seek(core::Count offset)
{
#ifdef DEBUG_MODE
    if (offset > mem_data.size())
        UNEXPECTED;
#endif
    index = offset;
}

gearoenix::core::Count gearoenix::system::stream::Memory::tell()
{
    return index;
}
