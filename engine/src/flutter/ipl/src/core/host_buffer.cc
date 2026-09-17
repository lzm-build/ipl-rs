#include <memory>

#include "core/host_buffer.h"
#include "impeller/core/host_buffer.h"
#include "ipl/src/core/buffer_view.h"
#include "ipl/src/core/host_buffer.h"

static_assert(sizeof(std::shared_ptr<impeller::HostBuffer>) ==
              sizeof(ipl_host_buffer_t));
static_assert(alignof(std::shared_ptr<impeller::HostBuffer>) ==
              alignof(ipl_host_buffer_t));

void ipl_host_buffer_drop(ipl_host_buffer_t* self) {
  std::destroy_at(ipl::transmute(self));
}

bool ipl_host_buffer_emplace(const ipl_host_buffer_t* self,
                             const void* buffer,
                             size_t length,
                             size_t align,
                             ipl_buffer_view_t* out) {
  auto* buffer_view = std::construct_at(
      ipl::transmute(out),
      ipl::transmute(self)->get()->Emplace(buffer, length, align));
  return static_cast<bool>(*buffer_view);
}

size_t ipl_host_buffer_get_minimum_uniform_alignment(
    const ipl_host_buffer_t* self) {
  return ipl::transmute(self)->get()->GetMinimumUniformAlignment();
}

void ipl_host_buffer_reset(const ipl_host_buffer_t* self) {
  ipl::transmute(self)->get()->Reset();
}
