#include "vk-img-view.hpp"
#ifdef USE_VULKAN
#include "../../core/cr-static.hpp"
#include "../device/vk-dev-logical.hpp"
#include "../device/vk-dev-physical.hpp"
#include "../memory/vk-mem-memory.hpp"
#include "../vk-check.hpp"
#include "../vk-instance.hpp"
#include "vk-img-image.hpp"

gearoenix::render::image::View::View(Image* img, const VkFormat& format)
    : img(img)
{
    const device::Logical* d = img->get_logical_device();
    const Linker* l = d->get_physical_device()->get_instance()->get_linker();
    VkImageViewCreateInfo view_create_info;
    setz(view_create_info);
    view_create_info.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    view_create_info.image = img->get_vulkan_data();
    view_create_info.viewType = VK_IMAGE_VIEW_TYPE_2D;
    view_create_info.format = format;
    view_create_info.components.r = VK_COMPONENT_SWIZZLE_R;
    view_create_info.components.g = VK_COMPONENT_SWIZZLE_G;
    view_create_info.components.b = VK_COMPONENT_SWIZZLE_B;
    view_create_info.components.a = VK_COMPONENT_SWIZZLE_A;
    view_create_info.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    view_create_info.subresourceRange.levelCount = 1;
    view_create_info.subresourceRange.layerCount = 1;
    VKC(l->vkCreateImageView(d->get_vulkan_data(), &view_create_info, 0, &vulkan_data));
}

gearoenix::render::image::View::View(Image* img,
    const VkImageViewCreateInfo& info)
    : img(img)
{
    const device::Logical* d = img->get_logical_device();
    const Linker* l = d->get_physical_device()->get_instance()->get_linker();
    const VkDevice vk_dev = d->get_vulkan_data();
    VKC(l->vkCreateImageView(vk_dev, &info, 0, &vulkan_data));
}

gearoenix::render::image::View::~View()
{
    const device::Logical* d = img->get_logical_device();
    const Linker* l = d->get_physical_device()->get_instance()->get_linker();
    const VkDevice vk_dev = d->get_vulkan_data();
    l->vkDestroyImageView(vk_dev, vulkan_data, 0);
    delete img;
}

gearoenix::render::image::View* gearoenix::render::image::View::create_depth_stencil(device::Logical* d)
{
    device::Physical* p = d->get_physical_device();
    VkFormat depth_format = p->get_supported_depth_format();
    const VkSurfaceCapabilitiesKHR& surf_cap = p->get_surface_capabilities();
    VkImageCreateInfo image_info;
    setz(image_info);
    image_info.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
    image_info.imageType = VK_IMAGE_TYPE_2D;
    image_info.format = depth_format;
    image_info.extent.width = surf_cap.currentExtent.width;
    image_info.extent.height = surf_cap.currentExtent.height;
    image_info.extent.depth = 1;
    image_info.mipLevels = 1;
    image_info.arrayLayers = 1;
    image_info.samples = VK_SAMPLE_COUNT_1_BIT;
    image_info.tiling = VK_IMAGE_TILING_OPTIMAL;
    image_info.usage = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT;
    image_info.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    Image* img = new Image(d, image_info);
    VkImageViewCreateInfo depth_stencil_view_info;
    setz(depth_stencil_view_info);
    depth_stencil_view_info.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    depth_stencil_view_info.viewType = VK_IMAGE_VIEW_TYPE_2D;
    depth_stencil_view_info.format = depth_format;
    depth_stencil_view_info.subresourceRange.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT | VK_IMAGE_ASPECT_STENCIL_BIT;
    depth_stencil_view_info.subresourceRange.levelCount = 1;
    depth_stencil_view_info.subresourceRange.layerCount = 1;
    depth_stencil_view_info.image = img->get_vulkan_data();
    return new View(img, depth_stencil_view_info);
}

const gearoenix::render::image::Image* gearoenix::render::image::View::get_image() const
{
    return img;
}

gearoenix::render::image::Image* gearoenix::render::image::View::get_image()
{
    return img;
}

const VkImageView& gearoenix::render::image::View::get_vulkan_data() const
{
    return vulkan_data;
}
#endif
