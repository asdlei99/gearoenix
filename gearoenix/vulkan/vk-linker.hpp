#ifndef GEAROENIX_VULKAN_LINKER_HPP
#define GEAROENIX_VULKAN_LINKER_HPP
#include "../core/cr-build-configuration.hpp"
#ifdef USE_VULKAN
#ifdef IN_ANDROID
#define VK_USE_PLATFORM_ANDROID_KHR
#elif defined(IN_LINUX)
#define VK_USE_PLATFORM_XCB_KHR
#elif defined(GX_IN_WINDOWS)
#define VK_USE_PLATFORM_WIN32_KHR
#else
#error "It is not implemented yet!"
#endif
#ifdef DEBUG_MODE
#define USE_DEBUG_EXTENTIONS
#endif
#define VK_NO_PROTOTYPES 1
#include <vulkan/vulkan.h>
namespace gearoenix {
namespace render {
    class Linker {
    public:
        Linker();

        PFN_vkCreateInstance vkCreateInstance;
        PFN_vkDestroyInstance vkDestroyInstance;
        PFN_vkEnumeratePhysicalDevices vkEnumeratePhysicalDevices;
        PFN_vkGetPhysicalDeviceFeatures vkGetPhysicalDeviceFeatures;
        PFN_vkGetPhysicalDeviceFormatProperties vkGetPhysicalDeviceFormatProperties;
        PFN_vkGetPhysicalDeviceImageFormatProperties
            vkGetPhysicalDeviceImageFormatProperties;
        PFN_vkGetPhysicalDeviceProperties vkGetPhysicalDeviceProperties;
        PFN_vkGetPhysicalDeviceQueueFamilyProperties
            vkGetPhysicalDeviceQueueFamilyProperties;
        PFN_vkGetPhysicalDeviceMemoryProperties vkGetPhysicalDeviceMemoryProperties;
        PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr;
        PFN_vkGetDeviceProcAddr vkGetDeviceProcAddr;
        PFN_vkCreateDevice vkCreateDevice;
        PFN_vkDestroyDevice vkDestroyDevice;
        PFN_vkEnumerateInstanceExtensionProperties
            vkEnumerateInstanceExtensionProperties;
        PFN_vkEnumerateDeviceExtensionProperties vkEnumerateDeviceExtensionProperties;
        PFN_vkEnumerateInstanceLayerProperties vkEnumerateInstanceLayerProperties;
        PFN_vkEnumerateDeviceLayerProperties vkEnumerateDeviceLayerProperties;
        PFN_vkGetDeviceQueue vkGetDeviceQueue;
        PFN_vkQueueSubmit vkQueueSubmit;
        PFN_vkQueueWaitIdle vkQueueWaitIdle;
        PFN_vkDeviceWaitIdle vkDeviceWaitIdle;
        PFN_vkAllocateMemory vkAllocateMemory;
        PFN_vkFreeMemory vkFreeMemory;
        PFN_vkMapMemory vkMapMemory;
        PFN_vkUnmapMemory vkUnmapMemory;
        PFN_vkFlushMappedMemoryRanges vkFlushMappedMemoryRanges;
        PFN_vkInvalidateMappedMemoryRanges vkInvalidateMappedMemoryRanges;
        PFN_vkGetDeviceMemoryCommitment vkGetDeviceMemoryCommitment;
        PFN_vkBindBufferMemory vkBindBufferMemory;
        PFN_vkBindImageMemory vkBindImageMemory;
        PFN_vkGetBufferMemoryRequirements vkGetBufferMemoryRequirements;
        PFN_vkGetImageMemoryRequirements vkGetImageMemoryRequirements;
        PFN_vkGetImageSparseMemoryRequirements vkGetImageSparseMemoryRequirements;
        PFN_vkGetPhysicalDeviceSparseImageFormatProperties
            vkGetPhysicalDeviceSparseImageFormatProperties;
        PFN_vkQueueBindSparse vkQueueBindSparse;
        PFN_vkCreateFence vkCreateFence;
        PFN_vkDestroyFence vkDestroyFence;
        PFN_vkResetFences vkResetFences;
        PFN_vkGetFenceStatus vkGetFenceStatus;
        PFN_vkWaitForFences vkWaitForFences;
        PFN_vkCreateSemaphore vkCreateSemaphore;
        PFN_vkDestroySemaphore vkDestroySemaphore;
        PFN_vkCreateEvent vkCreateEvent;
        PFN_vkDestroyEvent vkDestroyEvent;
        PFN_vkGetEventStatus vkGetEventStatus;
        PFN_vkSetEvent vkSetEvent;
        PFN_vkResetEvent vkResetEvent;
        PFN_vkCreateQueryPool vkCreateQueryPool;
        PFN_vkDestroyQueryPool vkDestroyQueryPool;
        PFN_vkGetQueryPoolResults vkGetQueryPoolResults;
        PFN_vkCreateBuffer vkCreateBuffer;
        PFN_vkDestroyBuffer vkDestroyBuffer;
        PFN_vkCreateBufferView vkCreateBufferView;
        PFN_vkDestroyBufferView vkDestroyBufferView;
        PFN_vkCreateImage vkCreateImage;
        PFN_vkDestroyImage vkDestroyImage;
        PFN_vkGetImageSubresourceLayout vkGetImageSubresourceLayout;
        PFN_vkCreateImageView vkCreateImageView;
        PFN_vkDestroyImageView vkDestroyImageView;
        PFN_vkCreateShaderModule vkCreateShaderModule;
        PFN_vkDestroyShaderModule vkDestroyShaderModule;
        PFN_vkCreatePipelineCache vkCreatePipelineCache;
        PFN_vkDestroyPipelineCache vkDestroyPipelineCache;
        PFN_vkGetPipelineCacheData vkGetPipelineCacheData;
        PFN_vkMergePipelineCaches vkMergePipelineCaches;
        PFN_vkCreateGraphicsPipelines vkCreateGraphicsPipelines;
        PFN_vkCreateComputePipelines vkCreateComputePipelines;
        PFN_vkDestroyPipeline vkDestroyPipeline;
        PFN_vkCreatePipelineLayout vkCreatePipelineLayout;
        PFN_vkDestroyPipelineLayout vkDestroyPipelineLayout;
        PFN_vkCreateSampler vkCreateSampler;
        PFN_vkDestroySampler vkDestroySampler;
        PFN_vkCreateDescriptorSetLayout vkCreateDescriptorSetLayout;
        PFN_vkDestroyDescriptorSetLayout vkDestroyDescriptorSetLayout;
        PFN_vkCreateDescriptorPool vkCreateDescriptorPool;
        PFN_vkDestroyDescriptorPool vkDestroyDescriptorPool;
        PFN_vkResetDescriptorPool vkResetDescriptorPool;
        PFN_vkAllocateDescriptorSets vkAllocateDescriptorSets;
        PFN_vkFreeDescriptorSets vkFreeDescriptorSets;
        PFN_vkUpdateDescriptorSets vkUpdateDescriptorSets;
        PFN_vkCreateFramebuffer vkCreateFramebuffer;
        PFN_vkDestroyFramebuffer vkDestroyFramebuffer;
        PFN_vkCreateRenderPass vkCreateRenderPass;
        PFN_vkDestroyRenderPass vkDestroyRenderPass;
        PFN_vkGetRenderAreaGranularity vkGetRenderAreaGranularity;
        PFN_vkCreateCommandPool vkCreateCommandPool;
        PFN_vkDestroyCommandPool vkDestroyCommandPool;
        PFN_vkResetCommandPool vkResetCommandPool;
        PFN_vkAllocateCommandBuffers vkAllocateCommandBuffers;
        PFN_vkFreeCommandBuffers vkFreeCommandBuffers;
        PFN_vkBeginCommandBuffer vkBeginCommandBuffer;
        PFN_vkEndCommandBuffer vkEndCommandBuffer;
        PFN_vkResetCommandBuffer vkResetCommandBuffer;
        PFN_vkCmdBindPipeline vkCmdBindPipeline;
        PFN_vkCmdSetViewport vkCmdSetViewport;
        PFN_vkCmdSetScissor vkCmdSetScissor;
        PFN_vkCmdSetLineWidth vkCmdSetLineWidth;
        PFN_vkCmdSetDepthBias vkCmdSetDepthBias;
        PFN_vkCmdSetBlendConstants vkCmdSetBlendConstants;
        PFN_vkCmdSetDepthBounds vkCmdSetDepthBounds;
        PFN_vkCmdSetStencilCompareMask vkCmdSetStencilCompareMask;
        PFN_vkCmdSetStencilWriteMask vkCmdSetStencilWriteMask;
        PFN_vkCmdSetStencilReference vkCmdSetStencilReference;
        PFN_vkCmdBindDescriptorSets vkCmdBindDescriptorSets;
        PFN_vkCmdBindIndexBuffer vkCmdBindIndexBuffer;
        PFN_vkCmdBindVertexBuffers vkCmdBindVertexBuffers;
        PFN_vkCmdDraw vkCmdDraw;
        PFN_vkCmdDrawIndexed vkCmdDrawIndexed;
        PFN_vkCmdDrawIndirect vkCmdDrawIndirect;
        PFN_vkCmdDrawIndexedIndirect vkCmdDrawIndexedIndirect;
        PFN_vkCmdDispatch vkCmdDispatch;
        PFN_vkCmdDispatchIndirect vkCmdDispatchIndirect;
        PFN_vkCmdCopyBuffer vkCmdCopyBuffer;
        PFN_vkCmdCopyImage vkCmdCopyImage;
        PFN_vkCmdBlitImage vkCmdBlitImage;
        PFN_vkCmdCopyBufferToImage vkCmdCopyBufferToImage;
        PFN_vkCmdCopyImageToBuffer vkCmdCopyImageToBuffer;
        PFN_vkCmdUpdateBuffer vkCmdUpdateBuffer;
        PFN_vkCmdFillBuffer vkCmdFillBuffer;
        PFN_vkCmdClearColorImage vkCmdClearColorImage;
        PFN_vkCmdClearDepthStencilImage vkCmdClearDepthStencilImage;
        PFN_vkCmdClearAttachments vkCmdClearAttachments;
        PFN_vkCmdResolveImage vkCmdResolveImage;
        PFN_vkCmdSetEvent vkCmdSetEvent;
        PFN_vkCmdResetEvent vkCmdResetEvent;
        PFN_vkCmdWaitEvents vkCmdWaitEvents;
        PFN_vkCmdPipelineBarrier vkCmdPipelineBarrier;
        PFN_vkCmdBeginQuery vkCmdBeginQuery;
        PFN_vkCmdEndQuery vkCmdEndQuery;
        PFN_vkCmdResetQueryPool vkCmdResetQueryPool;
        PFN_vkCmdWriteTimestamp vkCmdWriteTimestamp;
        PFN_vkCmdCopyQueryPoolResults vkCmdCopyQueryPoolResults;
        PFN_vkCmdPushConstants vkCmdPushConstants;
        PFN_vkCmdBeginRenderPass vkCmdBeginRenderPass;
        PFN_vkCmdNextSubpass vkCmdNextSubpass;
        PFN_vkCmdEndRenderPass vkCmdEndRenderPass;
        PFN_vkCmdExecuteCommands vkCmdExecuteCommands;

        // VK_KHR_surface
        PFN_vkDestroySurfaceKHR vkDestroySurfaceKHR;
        PFN_vkGetPhysicalDeviceSurfaceSupportKHR vkGetPhysicalDeviceSurfaceSupportKHR;
        PFN_vkGetPhysicalDeviceSurfaceCapabilitiesKHR
            vkGetPhysicalDeviceSurfaceCapabilitiesKHR;
        PFN_vkGetPhysicalDeviceSurfaceFormatsKHR vkGetPhysicalDeviceSurfaceFormatsKHR;
        PFN_vkGetPhysicalDeviceSurfacePresentModesKHR
            vkGetPhysicalDeviceSurfacePresentModesKHR;

        // VK_KHR_swapchain
        PFN_vkCreateSwapchainKHR vkCreateSwapchainKHR;
        PFN_vkDestroySwapchainKHR vkDestroySwapchainKHR;
        PFN_vkGetSwapchainImagesKHR vkGetSwapchainImagesKHR;
        PFN_vkAcquireNextImageKHR vkAcquireNextImageKHR;
        PFN_vkQueuePresentKHR vkQueuePresentKHR;

        // VK_KHR_display
        PFN_vkGetPhysicalDeviceDisplayPropertiesKHR
            vkGetPhysicalDeviceDisplayPropertiesKHR;
        PFN_vkGetPhysicalDeviceDisplayPlanePropertiesKHR
            vkGetPhysicalDeviceDisplayPlanePropertiesKHR;
        PFN_vkGetDisplayPlaneSupportedDisplaysKHR
            vkGetDisplayPlaneSupportedDisplaysKHR;
        PFN_vkGetDisplayModePropertiesKHR vkGetDisplayModePropertiesKHR;
        PFN_vkCreateDisplayModeKHR vkCreateDisplayModeKHR;
        PFN_vkGetDisplayPlaneCapabilitiesKHR vkGetDisplayPlaneCapabilitiesKHR;
        PFN_vkCreateDisplayPlaneSurfaceKHR vkCreateDisplayPlaneSurfaceKHR;

        // VK_KHR_display_swapchain
        PFN_vkCreateSharedSwapchainsKHR vkCreateSharedSwapchainsKHR;

#ifdef VK_USE_PLATFORM_XLIB_KHR
        // VK_KHR_xlib_surface
        PFN_vkCreateXlibSurfaceKHR vkCreateXlibSurfaceKHR;
        PFN_vkGetPhysicalDeviceXlibPresentationSupportKHR
            vkGetPhysicalDeviceXlibPresentationSupportKHR;
#endif

#ifdef VK_USE_PLATFORM_XCB_KHR
        // VK_KHR_xcb_surface
        PFN_vkCreateXcbSurfaceKHR vkCreateXcbSurfaceKHR;
        PFN_vkGetPhysicalDeviceXcbPresentationSupportKHR
            vkGetPhysicalDeviceXcbPresentationSupportKHR;
#endif

#ifdef VK_USE_PLATFORM_WAYLAND_KHR
        // VK_KHR_wayland_surface
        PFN_vkCreateWaylandSurfaceKHR vkCreateWaylandSurfaceKHR;
        PFN_vkGetPhysicalDeviceWaylandPresentationSupportKHR
            vkGetPhysicalDeviceWaylandPresentationSupportKHR;
#endif

#ifdef VK_USE_PLATFORM_MIR_KHR
        // VK_KHR_mir_surface
        PFN_vkCreateMirSurfaceKHR vkCreateMirSurfaceKHR;
        PFN_vkGetPhysicalDeviceMirPresentationSupportKHR
            vkGetPhysicalDeviceMirPresentationSupportKHR;
#endif

#ifdef VK_USE_PLATFORM_ANDROID_KHR
        // VK_KHR_android_surface
        PFN_vkCreateAndroidSurfaceKHR vkCreateAndroidSurfaceKHR;
#endif

#ifdef VK_USE_PLATFORM_WIN32_KHR
        // VK_KHR_win32_surface
        PFN_vkCreateWin32SurfaceKHR vkCreateWin32SurfaceKHR;
        PFN_vkGetPhysicalDeviceWin32PresentationSupportKHR
            vkGetPhysicalDeviceWin32PresentationSupportKHR;
#endif

#ifdef USE_DEBUG_EXTENTIONS
#include <vulkan/vk_sdk_platform.h>
        // VK_EXT_debug_report
        PFN_vkCreateDebugReportCallbackEXT vkCreateDebugReportCallbackEXT;
        PFN_vkDestroyDebugReportCallbackEXT vkDestroyDebugReportCallbackEXT;
        PFN_vkDebugReportMessageEXT vkDebugReportMessageEXT;
#endif
    };
}
}
#endif
#endif
