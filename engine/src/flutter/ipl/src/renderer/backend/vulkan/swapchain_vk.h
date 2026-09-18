#ifndef FLUTTER_IPL_SRC_RENDERER_BACKEND_VULKAN_SWAPCHAIN_VK_H_
#define FLUTTER_IPL_SRC_RENDERER_BACKEND_VULKAN_SWAPCHAIN_VK_H_

#include <cassert>
#include <cstdint>
#include <memory>

#include "impeller/renderer/backend/vulkan/swapchain/swapchain_vk.h"
#include "renderer/backend/vulkan/swapchain_vk.h"

namespace ipl {

static inline std::shared_ptr<impeller::SwapchainVK>* transmute(
    ipl_vk_swapchain_t* self) {
  assert(self != nullptr);
  assert(reinterpret_cast<intptr_t>(self) % alignof(ipl_vk_swapchain_t) == 0);
  return reinterpret_cast<std::shared_ptr<impeller::SwapchainVK>*>(self);
}

static inline const std::shared_ptr<impeller::SwapchainVK>* transmute(
    const ipl_vk_swapchain_t* self) {
  assert(self != nullptr);
  assert(reinterpret_cast<intptr_t>(self) % alignof(ipl_vk_swapchain_t) == 0);
  return reinterpret_cast<const std::shared_ptr<impeller::SwapchainVK>*>(self);
}

}  // namespace ipl

#endif  // FLUTTER_IPL_SRC_RENDERER_BACKEND_VULKAN_SWAPCHAIN_VK_H_
