#include <cassert>
#include <cstdint>
#include <memory>

#include "core/allocator.h"
#include "impeller/core/allocator.h"
#include "ipl/src/core/allocator.h"
#include "ipl/src/core/device_buffer.h"
#include "ipl/src/core/device_buffer_descriptor.h"
#include "ipl/src/core/formats.h"
#include "ipl/src/core/texture.h"
#include "ipl/src/core/texture_descriptor.h"

static_assert(sizeof(std::shared_ptr<impeller::Allocator>) ==
              sizeof(ipl_allocator_t));
static_assert(alignof(std::shared_ptr<impeller::Allocator>) ==
              alignof(ipl_allocator_t));

void ipl_allocator_drop(ipl_allocator_t* self) {
  std::destroy_at(ipl::transmute(self));
}

void ipl_allocator_clone(const ipl_allocator_t* self, ipl_allocator_t* out) {
  auto* allocator = ipl::transmute(self);
  assert(*allocator != nullptr);
  std::construct_at(ipl::transmute(out), *allocator);
}

bool ipl_allocator_create_buffer(const ipl_allocator_t* self,
                                 const ipl_device_buffer_descriptor_t* desc,
                                 ipl_device_buffer_t* out) {
  auto* allocator = ipl::transmute(self);
  assert(*allocator != nullptr);
  auto* device_buffer =
      std::construct_at(ipl::transmute(out),
                        allocator->get()->CreateBuffer(*ipl::transmute(desc)));
  return *device_buffer != nullptr;
}

bool ipl_allocator_create_texture(const ipl_allocator_t* self,
                                  const ipl_texture_descriptor_t* desc,
                                  bool threadsafe,
                                  ipl_texture_t* out) {
  auto* allocator = ipl::transmute(self);
  assert(*allocator != nullptr);
  auto* texture = std::construct_at(
      ipl::transmute(out),
      allocator->get()->CreateTexture(*ipl::transmute(desc), threadsafe));
  return *texture != nullptr;
}

uint16_t ipl_allocator_minimum_bytes_per_row(const ipl_allocator_t* self,
                                             ipl_pixel_format_t format) {
  auto* allocator = ipl::transmute(self);
  assert(*allocator != nullptr);
  return allocator->get()->MinimumBytesPerRow(transmute(format));
}

bool ipl_allocator_create_buffer_with_copy(const ipl_allocator_t* self,
                                           const uint8_t* buffer,
                                           size_t length,
                                           ipl_device_buffer_t* out) {
  auto* allocator = ipl::transmute(self);
  assert(*allocator != nullptr);
  assert(buffer != nullptr || length == 0);
  auto* device_buffer =
      std::construct_at(ipl::transmute(out),
                        allocator->get()->CreateBufferWithCopy(buffer, length));
  return *device_buffer != nullptr;
}