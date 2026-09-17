#ifndef FLUTTER_IPL_SRC_CORE_TEXTURE_H_
#define FLUTTER_IPL_SRC_CORE_TEXTURE_H_

#include <cassert>
#include <cstdint>
#include <memory>

#include "core/texture.h"
#include "impeller/core/texture.h"

namespace ipl {

static inline std::shared_ptr<impeller::Texture>* transmute(
    ipl_texture_t* self) {
  assert(self != nullptr);
  assert(reinterpret_cast<intptr_t>(self) % alignof(ipl_texture_t) == 0);
  return reinterpret_cast<std::shared_ptr<impeller::Texture>*>(self);
}

static inline const std::shared_ptr<impeller::Texture>* transmute(
    const ipl_texture_t* self) {
  assert(self != nullptr);
  assert(reinterpret_cast<intptr_t>(self) % alignof(ipl_texture_t) == 0);
  return reinterpret_cast<const std::shared_ptr<impeller::Texture>*>(self);
}

}  // namespace ipl

#endif  // FLUTTER_IPL_SRC_CORE_TEXTURE_H_
