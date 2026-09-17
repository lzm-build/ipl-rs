#ifndef FLUTTER_IPL_INCLUDE_RENDERER_BACKEND_VULKAN_CONTEXT_VK_H_
#define FLUTTER_IPL_INCLUDE_RENDERER_BACKEND_VULKAN_CONTEXT_VK_H_

#include <stdalign.h>
#include <stdbool.h>
#include <stdint.h>

#include "base/flags.h"
#include "base/mapping_list.h"
#include "base/string_list.h"
#include "core/allocator.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct VkInstance_T* VkInstance;
typedef struct VkPhysicalDevice_T* VkPhysicalDevice;
typedef struct VkDevice_T* VkDevice;
typedef struct VkQueue_T* VkQueue;

#if defined(__i386__) || defined(__arm__) || defined(_M_IX86)
#define IPL_VK_CONTEXT_EMBEDDER_DATA_SIZE 44
#define IPL_VK_CONTEXT_EMBEDDER_DATA_ALIGN 4
#else
#define IPL_VK_CONTEXT_EMBEDDER_DATA_SIZE 88
#define IPL_VK_CONTEXT_EMBEDDER_DATA_ALIGN 8
#endif

typedef struct {
  alignas(IPL_VK_CONTEXT_EMBEDDER_DATA_ALIGN) char data
      [IPL_VK_CONTEXT_EMBEDDER_DATA_SIZE];
} ipl_vk_context_embedder_data_t;

void ipl_vk_context_embedder_data_new(VkInstance instance,
                                      VkPhysicalDevice physical_device,
                                      VkDevice device,
                                      uint32_t queue_family_index,
                                      VkQueue queue,
                                      ipl_string_list_t* instance_extensions,
                                      ipl_string_list_t* device_extensions,
                                      ipl_vk_context_embedder_data_t* out);

void ipl_vk_context_embedder_data_drop(ipl_vk_context_embedder_data_t* self);

#if defined(__i386__) || defined(__arm__) || defined(_M_IX86)
#define IPL_VK_CONTEXT_SETTINGS_SIZE 76
#define IPL_VK_CONTEXT_SETTINGS_ALIGN 4
#else
#define IPL_VK_CONTEXT_SETTINGS_SIZE 144
#define IPL_VK_CONTEXT_SETTINGS_ALIGN 8
#endif

typedef struct {
  alignas(
      IPL_VK_CONTEXT_SETTINGS_ALIGN) char data[IPL_VK_CONTEXT_SETTINGS_SIZE];
} ipl_vk_context_settings_t;

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
                                 ipl_vk_context_settings_t* out);

void ipl_vk_context_settings_drop(ipl_vk_context_settings_t* self);

#if defined(__i386__) || defined(__arm__) || defined(_M_IX86)
#define IPL_VK_CONTEXT_SIZE 8
#define IPL_VK_CONTEXT_ALIGN 4
#else
#define IPL_VK_CONTEXT_SIZE 16
#define IPL_VK_CONTEXT_ALIGN 8
#endif

typedef struct {
  alignas(IPL_VK_CONTEXT_ALIGN) char data[IPL_VK_CONTEXT_SIZE];
} ipl_vk_context_t;

bool ipl_vk_context_new(ipl_vk_context_settings_t* settings,
                        ipl_vk_context_t* out);

void ipl_vk_context_drop(ipl_vk_context_t* self);

void ipl_vk_context_get_resource_allocator(const ipl_vk_context_t* self,
                                           ipl_allocator_t* out);

void ipl_vk_context_shutdown(const ipl_vk_context_t* self);

VkInstance ipl_vk_context_get_instance(const ipl_vk_context_t* self);

VkDevice ipl_vk_context_get_device(const ipl_vk_context_t* self);

void ipl_vk_context_initialize_commonly_used_shaders_if_needed(
    const ipl_vk_context_t* self);

void ipl_vk_context_dispose_thread_local_cached_resources(
    const ipl_vk_context_t* self);

#ifdef __cplusplus
}
#endif

#endif  // FLUTTER_IPL_INCLUDE_RENDERER_BACKEND_VULKAN_CONTEXT_VK_H_
