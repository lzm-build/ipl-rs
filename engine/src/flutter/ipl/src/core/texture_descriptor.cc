#include <type_traits>

#include "core/texture_descriptor.h"
#include "impeller/core/texture_descriptor.h"

static_assert(std::is_same_v<std::underlying_type_t<impeller::CompressionType>,
                             std::underlying_type_t<ipl_compress_type_t>>);

constexpr bool operator==(impeller::CompressionType lhs,
                          ipl_compress_type_t rhs) {
  return static_cast<ipl_compress_type_t>(lhs) == rhs;
}

static_assert(impeller::CompressionType::kLossless ==
              IPL_COMPRESSION_TYPE_LOSSLESS);
static_assert(impeller::CompressionType::kLossy == IPL_COMPRESSION_TYPE_LOSSY);

static_assert(sizeof(impeller::TextureDescriptor) ==
              sizeof(ipl_texture_descriptor_t));
static_assert(alignof(impeller::TextureDescriptor) ==
              alignof(ipl_texture_descriptor_t));

static_assert(std::is_standard_layout_v<impeller::TextureDescriptor>);
static_assert(std::is_standard_layout_v<ipl_texture_descriptor_t>);

static_assert(offsetof(impeller::TextureDescriptor, storage_mode) ==
              offsetof(ipl_texture_descriptor_t, storage_mode));
static_assert(offsetof(impeller::TextureDescriptor, type) ==
              offsetof(ipl_texture_descriptor_t, type));
static_assert(offsetof(impeller::TextureDescriptor, format) ==
              offsetof(ipl_texture_descriptor_t, format));
static_assert(offsetof(impeller::TextureDescriptor, size) ==
              offsetof(ipl_texture_descriptor_t, size));
static_assert(offsetof(impeller::TextureDescriptor, mip_count) ==
              offsetof(ipl_texture_descriptor_t, mip_count));
static_assert(offsetof(impeller::TextureDescriptor, usage) ==
              offsetof(ipl_texture_descriptor_t, usage));
static_assert(offsetof(impeller::TextureDescriptor, sample_count) ==
              offsetof(ipl_texture_descriptor_t, sample_count));
static_assert(offsetof(impeller::TextureDescriptor, compression_type) ==
              offsetof(ipl_texture_descriptor_t, compression_type));
