#ifndef FLUTTER_IPL_INCLUDE_CORE_DEVICE_BUFFER_DESCRIPTOR_H_
#define FLUTTER_IPL_INCLUDE_CORE_DEVICE_BUFFER_DESCRIPTOR_H_

#include <stdalign.h>
#include <stdbool.h>
#include <stddef.h>

#include "core/formats.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
  ipl_storage_mode_t storage_mode;
  size_t size;
  bool readback;
} ipl_device_buffer_descriptor_t;

#ifdef __cplusplus
}
#endif

#endif  // FLUTTER_IPL_INCLUDE_CORE_DEVICE_BUFFER_DESCRIPTOR_H_
