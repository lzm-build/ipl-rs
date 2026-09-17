#ifndef FLUTTER_IPL_SRC_CORE_ALLOCATOR_H_
#define FLUTTER_IPL_SRC_CORE_ALLOCATOR_H_

#include <cassert>
#include <memory>

#include "core/allocator.h"
#include "impeller/core/allocator.h"

namespace ipl {

static inline std::shared_ptr<impeller::Allocator>* transmute(
    ipl_allocator_t* self) {
  assert(self != nullptr);
  assert(reinterpret_cast<intptr_t>(self) % alignof(ipl_allocator_t) == 0);
  return reinterpret_cast<std::shared_ptr<impeller::Allocator>*>(self);
}

static inline const std::shared_ptr<impeller::Allocator>* transmute(
    const ipl_allocator_t* self) {
  assert(self != nullptr);
  assert(reinterpret_cast<intptr_t>(self) % alignof(ipl_allocator_t) == 0);
  return reinterpret_cast<const std::shared_ptr<impeller::Allocator>*>(self);
}

}  // namespace ipl

#endif  // FLUTTER_IPL_SRC_CORE_ALLOCATOR_H_
