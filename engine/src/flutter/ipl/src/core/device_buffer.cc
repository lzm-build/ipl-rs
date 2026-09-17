#include <cassert>
#include <cstddef>
#include <memory>
#include <string_view>

#include "core/device_buffer.h"
#include "impeller/core/device_buffer.h"
#include "ipl/src/core/device_buffer.h"
#include "ipl/src/core/device_buffer_descriptor.h"

static_assert(sizeof(std::shared_ptr<impeller::DeviceBuffer>) ==
              sizeof(ipl_device_buffer_t));
static_assert(alignof(std::shared_ptr<impeller::DeviceBuffer>) ==
              alignof(ipl_device_buffer_t));

void ipl_device_buffer_drop(ipl_device_buffer_t* self) {
  std::destroy_at(ipl::transmute(self));
}

void ipl_device_buffer_clone(const ipl_device_buffer_t* self,
                             ipl_device_buffer_t* out) {
  assert(self != out);
  auto* device_buffer = ipl::transmute(self);
  assert(*device_buffer != nullptr);
  std::construct_at(ipl::transmute(out), *device_buffer);
}

bool ipl_device_buffer_copy_host_buffer(const ipl_device_buffer_t* self,
                                        const uint8_t* source,
                                        size_t source_offset,
                                        size_t source_length,
                                        size_t offset) {
  auto* device_buffer = ipl::transmute(self);
  assert(*device_buffer != nullptr);
  return device_buffer->get()->CopyHostBuffer(
      source, impeller::Range{source_offset, source_length}, offset);
}

bool ipl_device_buffer_set_label(const ipl_device_buffer_t* self,
                                 const char* ptr,
                                 size_t len) {
  assert(ptr != nullptr);
  auto* device_buffer = ipl::transmute(self);
  assert(*device_buffer != nullptr);
  return device_buffer->get()->SetLabel(std::string_view{ptr, len});
}

const ipl_device_buffer_descriptor_t*
ipl_device_buffer_get_device_buffer_descriptor(
    const ipl_device_buffer_t* self) {
  auto* device_buffer = ipl::transmute(self);
  assert(*device_buffer != nullptr);
  return ipl::transmute(&device_buffer->get()->GetDeviceBufferDescriptor());
}

uint8_t* ipl_device_buffer_on_get_contents(const ipl_device_buffer_t* self) {
  auto* device_buffer = ipl::transmute(self);
  assert(*device_buffer != nullptr);
  return device_buffer->get()->OnGetContents();
}

void ipl_device_buffer_flush(const ipl_device_buffer_t* self,
                             size_t offset,
                             size_t length) {
  auto* device_buffer = ipl::transmute(self);
  assert(*device_buffer != nullptr);
  device_buffer->get()->Flush(impeller::Range{offset, length});
}

void ipl_device_buffer_invalidate(const ipl_device_buffer_t* self,
                                  size_t offset,
                                  size_t length) {
  auto* device_buffer = ipl::transmute(self);
  assert(*device_buffer != nullptr);
  device_buffer->get()->Invalidate(impeller::Range{offset, length});
}

static_assert(sizeof(std::shared_ptr<const impeller::DeviceBuffer>) ==
              IPL_CONST_DEVICE_BUFFER_SIZE);
static_assert(alignof(std::shared_ptr<const impeller::DeviceBuffer>) ==
              IPL_CONST_DEVICE_BUFFER_ALGIN);

void ipl_const_device_buffer_drop(ipl_const_device_buffer_t* self) {
  std::destroy_at(ipl::transmute(self));
}

void ipl_const_device_buffer_clone(const ipl_const_device_buffer_t* self,
                                   ipl_const_device_buffer_t* out) {
  assert(self != out);
  auto* device_buffer = ipl::transmute(self);
  assert(*device_buffer != nullptr);
  std::construct_at(ipl::transmute(out), *device_buffer);
}

const ipl_device_buffer_descriptor_t*
ipl_const_device_buffer_get_device_buffer_descriptor(
    const ipl_const_device_buffer_t* self) {
  auto* device_buffer = ipl::transmute(self);
  assert(*device_buffer != nullptr);
  return ipl::transmute(&device_buffer->get()->GetDeviceBufferDescriptor());
}

uint8_t* ipl_const_device_buffer_on_get_contents(
    const ipl_const_device_buffer_t* self) {
  auto* device_buffer = ipl::transmute(self);
  assert(*device_buffer != nullptr);
  return device_buffer->get()->OnGetContents();
}

void ipl_const_device_buffer_flush(const ipl_const_device_buffer_t* self,
                                   size_t offset,
                                   size_t length) {
  auto* device_buffer = ipl::transmute(self);
  assert(*device_buffer != nullptr);
  device_buffer->get()->Flush(impeller::Range{offset, length});
}

void ipl_const_device_buffer_invalidate(const ipl_const_device_buffer_t* self,
                                        size_t offset,
                                        size_t length) {
  auto* device_buffer = ipl::transmute(self);
  assert(*device_buffer != nullptr);
  device_buffer->get()->Invalidate(impeller::Range{offset, length});
}

void ipl_device_buffer_into_const_device_buffer(
    ipl_device_buffer_t* self,
    ipl_const_device_buffer_t* out) {
  auto* device_buffer = ipl::transmute(self);
  assert(*device_buffer != nullptr);
  std::construct_at(ipl::transmute(out), std::move(*device_buffer));
}
