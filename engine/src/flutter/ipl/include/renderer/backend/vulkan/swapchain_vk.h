#ifndef FLUTTER_IPL_INCLUDE_RENDERER_BACKEND_VULKAN_SWAPCHAIN_VK_H_
#define FLUTTER_IPL_INCLUDE_RENDERER_BACKEND_VULKAN_SWAPCHAIN_VK_H_

#include <stdalign.h>
#include <stdbool.h>

#include "geometry/size.h"
#include "renderer/context.h"
#include "renderer/surface.h"

#ifdef __cplusplus
extern "C" {
#endif

#if defined(__i386__) || defined(__arm__) || defined(_M_IX86)
#define IPL_VK_SWAPCHAIN_SIZE 8
#define IPL_VK_SWAPCHAIN_ALIGN 4
#else
#define IPL_VK_SWAPCHAIN_SIZE 16
#define IPL_VK_SWAPCHAIN_ALIGN 8
#endif

typedef struct {
  alignas(IPL_VK_SWAPCHAIN_ALIGN) char data[IPL_VK_SWAPCHAIN_SIZE];
} ipl_vk_swapchain_t;

#if defined(__i386__) || defined(__arm__) || defined(_M_IX86)
typedef uint64_t VkSurfaceKHR;
#else
typedef struct VkSurfaceKHR_T* VkSurfaceKHR;
#endif

bool ipl_vk_swapchain_new(const ipl_context_t* context,
                          VkSurfaceKHR surface,
                          const ipl_isize_t* size,
                          bool enable_msaa,
                          ipl_vk_swapchain_t* out);

void ipl_vk_swapchain_drop(ipl_vk_swapchain_t* self);

void ipl_vk_swapchain_clone(const ipl_vk_swapchain_t* self,
                            ipl_vk_swapchain_t* out);

bool ipl_vk_swapchain_acquire_next_drawable(const ipl_vk_swapchain_t* self,
                                            ipl_surface_t* out);

void ipl_vk_swapchain_update_surface_size(const ipl_vk_swapchain_t* self,
                                          const ipl_isize_t* size);

#ifdef __cplusplus
}
#endif

#endif  // FLUTTER_IPL_INCLUDE_RENDERER_BACKEND_VULKAN_SWAPCHAIN_VK_H_
