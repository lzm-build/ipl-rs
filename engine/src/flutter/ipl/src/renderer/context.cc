#include <memory>
#include <type_traits>

#include "impeller/renderer/context.h"
#include "ipl/src/base/flags.h"
#include "ipl/src/core/allocator.h"
#include "ipl/src/renderer/context.h"
#include "renderer/context.h"

static_assert(
    std::is_same_v<std::underlying_type_t<impeller::Context::BackendType>,
                   std::underlying_type_t<ipl_context_backend_type_t>>);

constexpr bool operator==(impeller::Context::BackendType lhs,
                          ipl_context_backend_type_t rhs) {
  return static_cast<ipl_context_backend_type_t>(lhs) == rhs;
}

static_assert(impeller::Context::BackendType::kMetal ==
              IPL_CONTEXT_BACKEND_TYPE_METAL);
static_assert(impeller::Context::BackendType::kOpenGLES ==
              IPL_CONTEXT_BACKEND_TYPE_OPENGLES);
static_assert(impeller::Context::BackendType::kVulkan ==
              IPL_CONTEXT_BACKEND_TYPE_VULKAN);

void ipl_context_drop(ipl_context_t* self) {
  std::destroy_at(ipl::transmute(self));
}

ipl_context_backend_type_t ipl_context_get_backend_type(
    const ipl_context_t* self) {
  return ipl::transmute(ipl::transmute(self)->get()->GetBackendType());
}

void ipl_context_get_resource_allocator(const ipl_context_t* self,
                                        ipl_allocator_t* out) {
  std::construct_at(ipl::transmute(out),
                    ipl::transmute(self)->get()->GetResourceAllocator());
}

void ipl_context_shutdown(const ipl_context_t* self) {
  ipl::transmute(self)->get()->Shutdown();
}

void ipl_context_initialize_commonly_used_shaders_if_needed(
    const ipl_context_t* self) {
  ipl::transmute(self)->get()->InitializeCommonlyUsedShadersIfNeeded();
}

void ipl_context_dispose_thread_local_cached_resources(
    const ipl_context_t* self) {
  ipl::transmute(self)->get()->DisposeThreadLocalCachedResources();
}

const ipl_flags_t* ipl_context_get_flags(const ipl_context_t* self) {
  return ipl::transmute(&ipl::transmute(self)->get()->GetFlags());
}
