#ifndef FLUTTER_IPL_INCLUDE_CORE_ALLOCATOR_H_
#define FLUTTER_IPL_INCLUDE_CORE_ALLOCATOR_H_

#include <stdalign.h>
#include <stdbool.h>
#include <stdint.h>

#include "core/device_buffer.h"
#include "core/device_buffer_descriptor.h"
#include "core/formats.h"
#include "core/texture.h"
#include "core/texture_descriptor.h"

#ifdef __cplusplus
extern "C" {
#endif

#if defined(__i386__) || defined(__arm__) || defined(_M_IX86)
#define IPL_ALLOCATOR_SIZE 8
#define IPL_ALLOCATOR_ALIGN 4
#else
#define IPL_ALLOCATOR_SIZE 16
#define IPL_ALLOCATOR_ALIGN 8
#endif

typedef struct {
  alignas(IPL_ALLOCATOR_ALIGN) char data[IPL_ALLOCATOR_SIZE];
} ipl_allocator_t;

void ipl_allocator_drop(ipl_allocator_t* self);

void ipl_allocator_clone(const ipl_allocator_t* self, ipl_allocator_t* out);

bool ipl_allocator_create_buffer(const ipl_allocator_t* self,
                                 const ipl_device_buffer_descriptor_t* desc,
                                 ipl_device_buffer_t* out);

bool ipl_allocator_create_texture(const ipl_allocator_t* self,
                                  const ipl_texture_descriptor_t* desc,
                                  bool threadsafe,
                                  ipl_texture_t* out);

uint16_t ipl_allocator_minimum_bytes_per_row(const ipl_allocator_t* self,
                                             ipl_pixel_format_t format);

bool ipl_allocator_create_buffer_with_copy(const ipl_allocator_t* self,
                                           const uint8_t* buffer,
                                           size_t length,
                                           ipl_device_buffer_t* out);

#ifdef __cplusplus
}
#endif

#endif  // FLUTTER_IPL_INCLUDE_CORE_ALLOCATOR_H_
