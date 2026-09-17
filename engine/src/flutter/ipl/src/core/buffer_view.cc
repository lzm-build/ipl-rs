#include <memory>

#include "core/buffer_view.h"
#include "impeller/core/buffer_view.h"
#include "ipl/src/core/buffer_view.h"
#include "ipl/src/core/device_buffer.h"

static_assert(sizeof(impeller::BufferView) == sizeof(ipl_buffer_view_t));
static_assert(alignof(impeller::BufferView) == alignof(ipl_buffer_view_t));

void ipl_buffer_view_drop(ipl_buffer_view_t* self) {
  std::destroy_at(ipl::transmute(self));
}

bool ipl_buffer_view_take_buffer(ipl_buffer_view_t* self,
                                 ipl_const_device_buffer_t* out) {
  auto* device_buffer = std::construct_at(ipl::transmute(out),
                                          ipl::transmute(self)->TakeBuffer());
  return *device_buffer != nullptr;
}
