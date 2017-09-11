#ifndef GEAROENIX_NUFRAG_VULKAN_MEMORY_POOL_HPP
#define GEAROENIX_NUFRAG_VULKAN_MEMORY_POOL_HPP
#include <memory>
namespace gearoenix {
namespace nufrag {
namespace render {
namespace device {
class Logical;
}
namespace memory {
class Pool
{
private:
    std::shared_ptr<device::Logical> logical_device;
public:
    Pool(const std::shared_ptr<device::Logical> &logical_device);
    const std::shared_ptr<device::Logical> &get_logical_device() const;
};
} // namespace memory
} // namespace render
} // namespace nufrag
} // namespace gearoenix
#endif // GEAROENIX_NUFRAG_RENDER_MEMORY_POOL_H
