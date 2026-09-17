#ifndef FLUTTER_IPL_SRC_CORE_TEXTURE_DESCRIPTOR_H_
#define FLUTTER_IPL_SRC_CORE_TEXTURE_DESCRIPTOR_H_

#include <cassert>
#include <cstdint>

#include "core/texture_descriptor.h"
#include "impeller/core/texture_descriptor.h"

namespace ipl {

static inline impeller::CompressionType transmute(ipl_compress_type_t self) {
#ifndef NDEBUG
  switch (self) {
    case IPL_COMPRESSION_TYPE_LOSSLESS:
    case IPL_COMPRESSION_TYPE_LOSSY:
      break;
    default:
      assert(false);
  }
#endif
  return static_cast<impeller::CompressionType>(self);
}

static inline ipl_compress_type_t transmute(impeller::CompressionType self) {
#ifndef NDEBUG
  switch (self) {
    case impeller::CompressionType::kLossless:
    case impeller::CompressionType::kLossy:
      break;
    default:
      assert(false);
  }
#endif
  return static_cast<ipl_compress_type_t>(self);
}

static inline impeller::TextureDescriptor* transmute(
    ipl_texture_descriptor_t* self) {
  assert(self != nullptr);
  assert(reinterpret_cast<intptr_t>(self) % alignof(ipl_texture_descriptor_t) ==
         0);
  return reinterpret_cast<impeller::TextureDescriptor*>(self);
}

static inline const impeller::TextureDescriptor* transmute(
    const ipl_texture_descriptor_t* self) {
  assert(self != nullptr);
  assert(reinterpret_cast<intptr_t>(self) % alignof(ipl_texture_descriptor_t) ==
         0);
  return reinterpret_cast<const impeller::TextureDescriptor*>(self);
}

static inline const ipl_texture_descriptor_t* transmute(
    const impeller::TextureDescriptor* self) {
  assert(self != nullptr);
  assert(reinterpret_cast<intptr_t>(self) % alignof(ipl_texture_descriptor_t) ==
         0);
  return reinterpret_cast<const ipl_texture_descriptor_t*>(self);
}

}  // namespace ipl

#endif  // FLUTTER_IPL_SRC_CORE_TEXTURE_DESCRIPTOR_H_
