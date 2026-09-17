#include <cassert>
#include <cstddef>
#include <memory>
#include <utility>

#include "fml/file.h"
#include "fml/paths.h"
#include "impeller/renderer/backend/vulkan/context_vk.h"
#include "ipl/src/base/flags.h"
#include "ipl/src/base/mapping_list.h"
#include "ipl/src/base/string_list.h"
#include "ipl/src/core/allocator.h"
#include "ipl/src/renderer/backend/vulkan/context_vk.h"
#include "renderer/backend/vulkan/context_vk.h"
#include "vulkan/vulkan_core.h"

static_assert(sizeof(impeller::ContextVK::EmbedderData) ==
              sizeof(ipl_vk_context_embedder_data_t));
static_assert(alignof(impeller::ContextVK::EmbedderData) ==
              alignof(ipl_vk_context_embedder_data_t));

void ipl_vk_context_embedder_data_new(VkInstance instance,
                                      VkPhysicalDevice physical_device,
                                      VkDevice device,
                                      uint32_t queue_family_index,
                                      VkQueue queue,
                                      ipl_string_list_t* instance_extensions,
                                      ipl_string_list_t* device_extensions,
                                      ipl_vk_context_embedder_data_t* out) {
  assert(instance != nullptr);
  assert(physical_device != nullptr);
  assert(device != nullptr);
  assert(queue != nullptr);
  std::construct_at(ipl::transmute(out), instance, physical_device, device,
                    queue_family_index, queue,
                    std::move(*ipl::transmute(instance_extensions)),
                    std::move(*ipl::transmute(device_extensions)));
}

void ipl_vk_context_embedder_data_drop(ipl_vk_context_embedder_data_t* self) {
  std::destroy_at(ipl::transmute(self));
}

static_assert(sizeof(impeller::ContextVK::Settings) ==
              sizeof(ipl_vk_context_settings_t));
static_assert(alignof(impeller::ContextVK::Settings) ==
              alignof(ipl_vk_context_settings_t));

void ipl_vk_context_settings_new(void* (*proc_address_callback)(VkInstance,
                                                                const char*),
                                 ipl_mapping_list_t* shader_libraries_data,
                                 const char* cache_directory,
                                 bool enable_validation,
                                 bool enable_gpu_tracing,
                                 bool enable_surface_control,
                                 bool fatal_missing_validations,
                                 const ipl_flags_t* flags,
                                 ipl_vk_context_embedder_data_t* embedder_data,
                                 ipl_vk_context_settings_t* out) {
  assert(proc_address_callback != nullptr);

  auto* settings = std::construct_at(ipl::transmute(out));
  settings->proc_address_callback =
      reinterpret_cast<PFN_vkGetInstanceProcAddr>(proc_address_callback);
  settings->shader_libraries_data =
      std::move(*ipl::transmute(shader_libraries_data));
  settings->cache_directory =
      cache_directory == nullptr
          ? fml::paths::GetCachesDirectory()
          : fml::OpenDirectory(cache_directory, false,
                               fml::FilePermission::kRead);
  settings->enable_validation = enable_validation;
  settings->enable_gpu_tracing = enable_gpu_tracing;
  settings->enable_surface_control = enable_surface_control;
  settings->fatal_missing_validations = fatal_missing_validations;
  settings->flags = *ipl::transmute(flags);
  if (embedder_data != nullptr) {
    settings->embedder_data.emplace(std::move(*ipl::transmute(embedder_data)));
  }
}

void ipl_vk_context_settings_drop(ipl_vk_context_settings_t* self) {
  std::destroy_at(ipl::transmute(self));
}

static_assert(sizeof(std::shared_ptr<impeller::ContextVK>) ==
              sizeof(ipl_vk_context_t));
static_assert(alignof(std::shared_ptr<impeller::ContextVK>) ==
              alignof(ipl_vk_context_t));

bool ipl_vk_context_new(ipl_vk_context_settings_t* settings,
                        ipl_vk_context_t* out) {
  auto* ctx_vk = std::construct_at(
      ipl::transmute(out),
      impeller::ContextVK::Create(std::move(*ipl::transmute(settings))));
  return *ctx_vk != nullptr;
}

void ipl_vk_context_drop(ipl_vk_context_t* self) {
  std::destroy_at(ipl::transmute(self));
}

void ipl_vk_context_get_resource_allocator(const ipl_vk_context_t* self,
                                           ipl_allocator_t* out) {
  std::construct_at(ipl::transmute(out),
                    ipl::transmute(self)->get()->GetResourceAllocator());
}

void ipl_vk_context_shutdown(const ipl_vk_context_t* self) {
  ipl::transmute(self)->get()->Shutdown();
}

VkInstance ipl_vk_context_get_instance(const ipl_vk_context_t* self) {
  return ipl::transmute(ipl::transmute(self)->get()->GetInstance());
}

VkDevice ipl_vk_context_get_device(const ipl_vk_context_t* self) {
  return ipl::transmute(ipl::transmute(self)->get()->GetDevice());
}

void ipl_vk_context_initialize_commonly_used_shaders_if_needed(
    const ipl_vk_context_t* self) {
  ipl::transmute(self)->get()->InitializeCommonlyUsedShadersIfNeeded();
}

void ipl_vk_context_dispose_thread_local_cached_resources(
    const ipl_vk_context_t* self) {
  ipl::transmute(self)->get()->DisposeThreadLocalCachedResources();
}
