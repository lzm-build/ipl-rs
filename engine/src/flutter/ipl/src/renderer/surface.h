#ifndef FLUTTER_IPL_SRC_RENDERER_SURFACE_H_
#define FLUTTER_IPL_SRC_RENDERER_SURFACE_H_

#include <cassert>
#include <cstdint>
#include <memory>

#include "impeller/renderer/surface.h"
#include "renderer/surface.h"

namespace ipl {

static inline std::shared_ptr<impeller::Surface>* transmute(
    ipl_surface_t* self) {
  assert(self != nullptr);
  assert(reinterpret_cast<intptr_t>(self) % alignof(ipl_surface_t) == 0);
  return reinterpret_cast<std::shared_ptr<impeller::Surface>*>(self);
}

static inline const std::shared_ptr<impeller::Surface>* transmute(
    const ipl_surface_t* self) {
  assert(self != nullptr);
  assert(reinterpret_cast<intptr_t>(self) % alignof(ipl_surface_t) == 0);
  return reinterpret_cast<const std::shared_ptr<impeller::Surface>*>(self);
}

}  // namespace ipl

#endif  // FLUTTER_IPL_SRC_RENDERER_SURFACE_H_
