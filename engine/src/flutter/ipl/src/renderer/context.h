#ifndef FLUTTER_IPL_SRC_RENDERER_CONTEXT_H_
#define FLUTTER_IPL_SRC_RENDERER_CONTEXT_H_

#include <cassert>
#include <cstdint>
#include <memory>

#include "impeller/renderer/context.h"
#include "renderer/context.h"

namespace ipl {

static inline ipl_context_backend_type_t transmute(
    impeller::Context::BackendType self) {
#ifndef NDEBUG
  switch (self) {
    case impeller::Context::BackendType::kMetal:
    case impeller::Context::BackendType::kOpenGLES:
    case impeller::Context::BackendType::kVulkan:
      break;
    default:
      assert(false);
  }
#endif
  return static_cast<ipl_context_backend_type_t>(self);
}

static inline std::shared_ptr<impeller::Context>* transmute(
    ipl_context_t* self) {
  assert(self != nullptr);
  assert(reinterpret_cast<intptr_t>(self) % alignof(ipl_context_t) == 0);
  return reinterpret_cast<std::shared_ptr<impeller::Context>*>(self);
}

static inline const std::shared_ptr<impeller::Context>* transmute(
    const ipl_context_t* self) {
  assert(self != nullptr);
  assert(reinterpret_cast<intptr_t>(self) % alignof(ipl_context_t) == 0);
  return reinterpret_cast<const std::shared_ptr<impeller::Context>*>(self);
}

}  // namespace ipl

#endif  // FLUTTER_IPL_SRC_RENDERER_CONTEXT_H_
