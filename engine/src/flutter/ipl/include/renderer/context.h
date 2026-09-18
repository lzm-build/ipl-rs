#ifndef FLUTTER_IPL_INCLUDE_RENDERER_CONTEXT_H_
#define FLUTTER_IPL_INCLUDE_RENDERER_CONTEXT_H_

#include <stdalign.h>

#include "base/flags.h"
#include "core/allocator.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum : int {
  IPL_CONTEXT_BACKEND_TYPE_METAL = 0,
  IPL_CONTEXT_BACKEND_TYPE_OPENGLES = 1,
  IPL_CONTEXT_BACKEND_TYPE_VULKAN = 2,
} ipl_context_backend_type_t;

#if defined(__i386__) || defined(__arm__) || defined(_M_IX86)
#define IPL_CONTEXT_SIZE 8
#define IPL_CONTEXT_ALIGN 4
#else
#define IPL_CONTEXT_SIZE 16
#define IPL_CONTEXT_ALIGN 8
#endif

typedef struct {
  alignas(IPL_CONTEXT_ALIGN) char data[IPL_CONTEXT_SIZE];
} ipl_context_t;

void ipl_context_drop(ipl_context_t* self);

ipl_context_backend_type_t ipl_context_get_backend_type(
    const ipl_context_t* self);

void ipl_context_get_resource_allocator(const ipl_context_t* self,
                                        ipl_allocator_t* out);

void ipl_context_shutdown(const ipl_context_t* self);

void ipl_context_initialize_commonly_used_shaders_if_needed(
    const ipl_context_t* self);

void ipl_context_dispose_thread_local_cached_resources(
    const ipl_context_t* self);

const ipl_flags_t* ipl_context_get_flags(const ipl_context_t* self);

#ifdef __cplusplus
}
#endif

#endif  // FLUTTER_IPL_INCLUDE_RENDERER_CONTEXT_H_
