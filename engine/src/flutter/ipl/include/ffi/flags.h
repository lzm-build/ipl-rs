#ifndef FLUTTER_IPL_INCLUDE_FFI_FLAGS_H_
#define FLUTTER_IPL_INCLUDE_FFI_FLAGS_H_

#include <stdbool.h>

typedef struct IplFlags {
  bool use_sdfs;
  bool top_left_default_framebuffer_origin;
} IplFlags;

#endif  // FLUTTER_IPL_INCLUDE_FFI_FLAGS_H_
