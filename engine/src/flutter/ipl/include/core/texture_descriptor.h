#ifndef FLUTTER_IPL_INCLUDE_CORE_TEXTURE_DESCRIPTOR_H_
#define FLUTTER_IPL_INCLUDE_CORE_TEXTURE_DESCRIPTOR_H_

#include <stdalign.h>
#include <stddef.h>

#include "core/formats.h"
#include "geometry/size.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum : int {
  IPL_COMPRESSION_TYPE_LOSSLESS = 0,
  IPL_COMPRESSION_TYPE_LOSSY = 1,
} ipl_compress_type_t;

#if defined(__i386__) || defined(__arm__) || defined(_M_IX86)
#define IPL_TEXTURE_DESCRIPTOR_SIZE 48
#define IPL_TEXTURE_DESCRIPTOR_ALIGN 8
#else
#define IPL_TEXTURE_DESCRIPTOR_SIZE 56
#define IPL_TEXTURE_DESCRIPTOR_ALIGN 8
#endif

typedef struct {
  ipl_storage_mode_t storage_mode;
  ipl_texture_type_t type;
  ipl_pixel_format_t format;
  ipl_isize_t size;
  size_t mip_count;
  ipl_texture_usage_t usage;
  ipl_sample_count_t sample_count;
  ipl_compress_type_t compression_type;
} ipl_texture_descriptor_t;

#ifdef __cplusplus
}
#endif

#endif  // FLUTTER_IPL_INCLUDE_CORE_TEXTURE_DESCRIPTOR_H_
