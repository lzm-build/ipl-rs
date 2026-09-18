#include <cassert>
#include <cstddef>
#include <memory>
#include <utility>

#include "impeller/renderer/backend/vulkan/context_vk.h"
#include "impeller/renderer/backend/vulkan/swapchain/swapchain_vk.h"
#include "impeller/renderer/context.h"
#include "ipl/src/geometry/size.h"
#include "ipl/src/renderer/backend/vulkan/swapchain_vk.h"
#include "ipl/src/renderer/context.h"
#include "ipl/src/renderer/surface.h"
#include "renderer/backend/vulkan/swapchain_vk.h"
#include "renderer/context.h"
#include "vulkan/vulkan.hpp"

static_assert(sizeof(std::shared_ptr<impeller::SwapchainVK>) ==
              sizeof(ipl_vk_swapchain_t));
static_assert(alignof(std::shared_ptr<impeller::SwapchainVK>) ==
              alignof(ipl_vk_swapchain_t));

bool ipl_vk_swapchain_new(const ipl_context_t* context,
                          VkSurfaceKHR surface,
                          const ipl_isize_t* size,
                          bool enable_msaa,
                          ipl_vk_swapchain_t* out) {
  const auto& context_sp = *ipl::transmute(context);
  assert(context_sp != nullptr);
  assert(context_sp->GetBackendType() ==
         impeller::Context::BackendType::kVulkan);
  auto unique_surface_khr = impeller::vk::UniqueSurfaceKHR(
      impeller::vk::SurfaceKHR{surface},
      impeller::ContextVK::Cast(*context_sp).GetInstance());
  auto* swapchain_vk = std::construct_at(
      ipl::transmute(out),
      impeller::SwapchainVK::Create(context_sp, std::move(unique_surface_khr),
                                    *ipl::transmute(size), enable_msaa));
  return *swapchain_vk != nullptr;
}

void ipl_vk_swapchain_drop(ipl_vk_swapchain_t* self) {
  std::destroy_at(ipl::transmute(self));
}

void ipl_vk_swapchain_clone(const ipl_vk_swapchain_t* self,
                            ipl_vk_swapchain_t* out) {
  std::construct_at(ipl::transmute(out), *ipl::transmute(self));
}

bool ipl_vk_swapchain_acquire_next_drawable(const ipl_vk_swapchain_t* self,
                                            ipl_surface_t* out) {
  auto* surface = std::construct_at(
      ipl::transmute(out), ipl::transmute(self)->get()->AcquireNextDrawable());
  return *surface != nullptr;
}

void ipl_vk_swapchain_update_surface_size(const ipl_vk_swapchain_t* self,
                                          const ipl_isize_t* size) {
  ipl::transmute(self)->get()->UpdateSurfaceSize(*ipl::transmute(size));
}