#ifndef FLUTTER_IPL_INCLUDE_CORE_TEXTURE_H_
#define FLUTTER_IPL_INCLUDE_CORE_TEXTURE_H_

#include <stdalign.h>
#include <stdbool.h>
#include <stddef.h>

#include "core/texture_descriptor.h"
#include "geometry/size.h"

#ifdef __cplusplus
extern "C" {
#endif

#if defined(__i386__) || defined(__arm__) || defined(_M_IX86)
#define IPL_TEXTURE_SIZE 8
#define IPL_TEXTURE_ALIGN 4
#else
#define IPL_TEXTURE_SIZE 16
#define IPL_TEXTURE_ALIGN 8
#endif

typedef struct {
  alignas(IPL_TEXTURE_ALIGN) char data[IPL_TEXTURE_SIZE];
} ipl_texture_t;

void ipl_texture_drop(ipl_texture_t* self);

void ipl_texture_clone(const ipl_texture_t* self, ipl_texture_t* out);

void ipl_texture_set_label(const ipl_texture_t* self,
                           const char* ptr,
                           size_t len);

void ipl_texture_get_size(const ipl_texture_t* self, ipl_isize_t* out);

bool ipl_texture_is_opaque(const ipl_texture_t* self);

size_t ipl_texture_get_mip_count(const ipl_texture_t* self);

const ipl_texture_descriptor_t* ipl_texture_get_texture_descriptor(
    const ipl_texture_t* self);

bool ipl_texture_needs_mipmap_generation(const ipl_texture_t* self);

#ifdef __cplusplus
}
#endif

#endif  // FLUTTER_IPL_INCLUDE_CORE_TEXTURE_H_
