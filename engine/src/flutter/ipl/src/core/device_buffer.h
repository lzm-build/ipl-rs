#ifndef FLUTTER_IPL_SRC_CORE_DEVICE_BUFFER_H_
#define FLUTTER_IPL_SRC_CORE_DEVICE_BUFFER_H_

#include <cassert>
#include <cstdint>
#include <memory>

#include "core/device_buffer.h"
#include "impeller/core/device_buffer.h"

namespace ipl {

static inline std::shared_ptr<impeller::DeviceBuffer>* transmute(
    ipl_device_buffer_t* self) {
  assert(self != nullptr);
  assert(reinterpret_cast<intptr_t>(self) % alignof(ipl_device_buffer_t) == 0);
  return reinterpret_cast<std::shared_ptr<impeller::DeviceBuffer>*>(self);
}

static inline const std::shared_ptr<impeller::DeviceBuffer>* transmute(
    const ipl_device_buffer_t* self) {
  assert(self != nullptr);
  assert(reinterpret_cast<intptr_t>(self) % alignof(ipl_device_buffer_t) == 0);
  return reinterpret_cast<const std::shared_ptr<impeller::DeviceBuffer>*>(self);
}

static inline std::shared_ptr<const impeller::DeviceBuffer>* transmute(
    ipl_const_device_buffer_t* self) {
  assert(self != nullptr);
  assert(reinterpret_cast<intptr_t>(self) %
             alignof(ipl_const_device_buffer_t) ==
         0);
  return reinterpret_cast<std::shared_ptr<const impeller::DeviceBuffer>*>(self);
}

static inline const std::shared_ptr<const impeller::DeviceBuffer>* transmute(
    const ipl_const_device_buffer_t* self) {
  assert(self != nullptr);
  assert(reinterpret_cast<intptr_t>(self) %
             alignof(ipl_const_device_buffer_t) ==
         0);
  return reinterpret_cast<const std::shared_ptr<const impeller::DeviceBuffer>*>(
      self);
}

}  // namespace ipl

#endif  // FLUTTER_IPL_SRC_CORE_DEVICE_BUFFER_H_
