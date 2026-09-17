#ifndef FLUTTER_IPL_SRC_CORE_BUFFER_VIEW_H_
#define FLUTTER_IPL_SRC_CORE_BUFFER_VIEW_H_

#include <cassert>
#include <cstdint>

#include "core/buffer_view.h"
#include "impeller/core/buffer_view.h"

namespace ipl {

static inline impeller::BufferView* transmute(ipl_buffer_view_t* self) {
  assert(self != nullptr);
  assert(reinterpret_cast<intptr_t>(self) % alignof(ipl_buffer_view_t) == 0);
  return reinterpret_cast<impeller::BufferView*>(self);
}

static inline const impeller::BufferView* transmute(
    const ipl_buffer_view_t* self) {
  assert(self != nullptr);
  assert(reinterpret_cast<intptr_t>(self) % alignof(ipl_buffer_view_t) == 0);
  return reinterpret_cast<const impeller::BufferView*>(self);
}

}  // namespace ipl

#endif  // FLUTTER_IPL_SRC_CORE_BUFFER_VIEW_H_
