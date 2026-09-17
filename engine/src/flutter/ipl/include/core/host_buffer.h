#ifndef FLUTTER_IPL_INCLUDE_CORE_HOST_BUFFER_H_
#define FLUTTER_IPL_INCLUDE_CORE_HOST_BUFFER_H_

#include <stdalign.h>
#include <stddef.h>

#include "core/buffer_view.h"

#ifdef __cplusplus
extern "C" {
#endif

#if defined(__i386__) || defined(__arm__) || defined(_M_IX86)
#define IPL_HOST_BUFFER_SIZE 8
#define IPL_HOST_BUFFER_ALIGN 4
#else
#define IPL_HOST_BUFFER_SIZE 16
#define IPL_HOST_BUFFER_ALIGN 8
#endif

typedef struct {
  alignas(IPL_HOST_BUFFER_ALIGN) char data[IPL_HOST_BUFFER_SIZE];
} ipl_host_buffer_t;

void ipl_host_buffer_drop(ipl_host_buffer_t* self);

bool ipl_host_buffer_emplace(const ipl_host_buffer_t* self,
                             const void* buffer,
                             size_t length,
                             size_t align,
                             ipl_buffer_view_t* out);

size_t ipl_host_buffer_get_minimum_uniform_alignment(
    const ipl_host_buffer_t* self);

void ipl_host_buffer_reset(const ipl_host_buffer_t* self);

#ifdef __cplusplus
}
#endif

#endif  // FLUTTER_IPL_INCLUDE_CORE_HOST_BUFFER_H_
