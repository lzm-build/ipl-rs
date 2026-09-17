#ifndef FLUTTER_IPL_SRC_GEOMETRY_SIZE_H_
#define FLUTTER_IPL_SRC_GEOMETRY_SIZE_H_

#include <cassert>
#include <cstdint>
#include "geometry/size.h"
#include "impeller/geometry/size.h"

namespace ipl {
static inline impeller::ISize* transmute(ipl_isize_t* self) {
  assert(self != nullptr);
  assert(reinterpret_cast<intptr_t>(self) % alignof(ipl_isize_t) == 0);
  return reinterpret_cast<impeller::ISize*>(self);
}

static inline const impeller::ISize* transmute(const ipl_isize_t* self) {
  assert(self != nullptr);
  assert(reinterpret_cast<intptr_t>(self) % alignof(ipl_isize_t) == 0);
  return reinterpret_cast<const impeller::ISize*>(self);
}
}  // namespace ipl

#endif  // FLUTTER_IPL_SRC_GEOMETRY_SIZE_H_
