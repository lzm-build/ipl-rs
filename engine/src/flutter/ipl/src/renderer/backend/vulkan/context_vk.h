#ifndef FLUTTER_IPL_SRC_RENDERER_BACKEND_VULKAN_CONTEXT_VK_H_
#define FLUTTER_IPL_SRC_RENDERER_BACKEND_VULKAN_CONTEXT_VK_H_

#include <cassert>
#include <cstdint>
#include <memory>

#include "impeller/renderer/backend/vulkan/context_vk.h"
#include "renderer/backend/vulkan/context_vk.h"
#include "vulkan/vulkan.hpp"

namespace ipl {

static inline VkInstance transmute(impeller::vk::Instance self) {
  return static_cast<VkInstance>(self);
}

static inline VkDevice transmute(impeller::vk::Device self) {
  return static_cast<VkDevice>(self);
}

static inline impeller::ContextVK::EmbedderData* transmute(
    ipl_vk_context_embedder_data_t* self) {
  assert(self != nullptr);
  assert(reinterpret_cast<intptr_t>(self) %
             alignof(ipl_vk_context_embedder_data_t) ==
         0);
  return reinterpret_cast<impeller::ContextVK::EmbedderData*>(self);
}

static inline impeller::ContextVK::Settings* transmute(
    ipl_vk_context_settings_t* self) {
  assert(self != nullptr);
  assert(reinterpret_cast<intptr_t>(self) %
             alignof(ipl_vk_context_settings_t) ==
         0);
  return reinterpret_cast<impeller::ContextVK::Settings*>(self);
}

static inline std::shared_ptr<impeller::ContextVK>* transmute(
    ipl_vk_context_t* self) {
  assert(self != nullptr);
  assert(reinterpret_cast<intptr_t>(self) % alignof(ipl_vk_context_t) == 0);
  return reinterpret_cast<std::shared_ptr<impeller::ContextVK>*>(self);
}

static inline const std::shared_ptr<impeller::ContextVK>* transmute(
    const ipl_vk_context_t* self) {
  assert(self != nullptr);
  assert(reinterpret_cast<intptr_t>(self) % alignof(ipl_vk_context_t) == 0);
  return reinterpret_cast<const std::shared_ptr<impeller::ContextVK>*>(self);
}

}  // namespace ipl

#endif  // FLUTTER_IPL_SRC_RENDERER_BACKEND_VULKAN_CONTEXT_VK_H_
