#ifndef FLUTTER_IPL_SRC_CORE_DEVICE_BUFFER_DESCRIPTOR_H_
#define FLUTTER_IPL_SRC_CORE_DEVICE_BUFFER_DESCRIPTOR_H_

#include <cassert>
#include <cstdint>
#include "core/device_buffer_descriptor.h"
#include "impeller/core/device_buffer_descriptor.h"

namespace ipl {

static inline impeller::DeviceBufferDescriptor* transmute(
    ipl_device_buffer_descriptor_t* self) {
  assert(self != nullptr);
  assert(reinterpret_cast<intptr_t>(self) %
             alignof(ipl_device_buffer_descriptor_t) ==
         0);
  return reinterpret_cast<impeller::DeviceBufferDescriptor*>(self);
}

static inline const impeller::DeviceBufferDescriptor* transmute(
    const ipl_device_buffer_descriptor_t* self) {
  assert(self != nullptr);
  assert(reinterpret_cast<intptr_t>(self) %
             alignof(ipl_device_buffer_descriptor_t) ==
         0);
  return reinterpret_cast<const impeller::DeviceBufferDescriptor*>(self);
}

static inline const ipl_device_buffer_descriptor_t* transmute(
    const impeller::DeviceBufferDescriptor* self) {
  assert(self != nullptr);
  assert(reinterpret_cast<intptr_t>(self) %
             alignof(ipl_device_buffer_descriptor_t) ==
         0);
  return reinterpret_cast<const ipl_device_buffer_descriptor_t*>(self);
}

}  // namespace ipl

#endif  // FLUTTER_IPL_SRC_CORE_DEVICE_BUFFER_DESCRIPTOR_H_
