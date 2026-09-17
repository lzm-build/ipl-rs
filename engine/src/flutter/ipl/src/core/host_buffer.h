#ifndef FLUTTER_IPL_SRC_CORE_HOST_BUFFER_H_
#define FLUTTER_IPL_SRC_CORE_HOST_BUFFER_H_

#include <cassert>
#include <cstdint>
#include <memory>

#include "core/host_buffer.h"
#include "impeller/core/host_buffer.h"

namespace ipl {

static inline std::shared_ptr<impeller::HostBuffer>* transmute(
    ipl_host_buffer_t* self) {
  assert(self != nullptr);
  assert(reinterpret_cast<intptr_t>(self) % alignof(ipl_host_buffer_t) == 0);
  return reinterpret_cast<std::shared_ptr<impeller::HostBuffer>*>(self);
}

static inline const std::shared_ptr<impeller::HostBuffer>* transmute(
    const ipl_host_buffer_t* self) {
  assert(self != nullptr);
  assert(reinterpret_cast<intptr_t>(self) % alignof(ipl_host_buffer_t) == 0);
  return reinterpret_cast<const std::shared_ptr<impeller::HostBuffer>*>(self);
}

}  // namespace ipl

#endif  // FLUTTER_IPL_SRC_CORE_HOST_BUFFER_H_
