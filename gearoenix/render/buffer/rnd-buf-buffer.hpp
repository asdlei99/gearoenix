#ifndef GEAROENIX_RENDER_BUFFER_BUFFER_HPP
#define GEAROENIX_RENDER_BUFFER_BUFFER_HPP
#include "../../core/cr-build-configuration.hpp"
#ifdef USE_VULKAN
#include "../../vulkan/buffer/vk-buf-buffer.hpp"
#else
#error "Not implemented yet"
#endif
#endif // GEAROENIX_RENDER_BUFFER_BUFFER_HPP