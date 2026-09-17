#ifndef FLUTTER_IPL_SRC_CORE_FORMATS_H_
#define FLUTTER_IPL_SRC_CORE_FORMATS_H_

#include <cassert>

#include "core/formats.h"
#include "impeller/core/formats.h"

static inline impeller::WindingOrder transmute(
    ipl_winding_order_t winding_order) {
#ifndef NDEBUG
  switch (winding_order) {
    case IPL_WINDING_ORDER_CLOCKWISE:
    case IPL_WINDING_ORDER_COUNTER_CLOCKWISE:
      break;
    default:
      assert(false && "Unhandled ipl_winding_order_t value.");
  }
#endif
  return static_cast<impeller::WindingOrder>(winding_order);
}

static inline ipl_winding_order_t transmute(
    impeller::WindingOrder winding_order) {
#ifndef NDEBUG
  switch (winding_order) {
    case impeller::WindingOrder::kClockwise:
    case impeller::WindingOrder::kCounterClockwise:
      break;
    default:
      assert(false && "Unhandled impeller::WindingOrder value.");
  }
#endif
  return static_cast<ipl_winding_order_t>(winding_order);
}

static inline impeller::StorageMode transmute(ipl_storage_mode_t storage_mode) {
#ifndef NDEBUG
  switch (storage_mode) {
    case IPL_STORAGE_MODE_HOST_VISIBLE:
    case IPL_STORAGE_MODE_DEVICE_PRIVATE:
    case IPL_STORAGE_MODE_DEVICE_TRANSIENT:
      break;
    default:
      assert(false && "Unhandled ipl_storage_mode_t value.");
  }
#endif
  return static_cast<impeller::StorageMode>(storage_mode);
}

static inline ipl_storage_mode_t transmute(impeller::StorageMode storage_mode) {
#ifndef NDEBUG
  switch (storage_mode) {
    case impeller::StorageMode::kHostVisible:
    case impeller::StorageMode::kDevicePrivate:
    case impeller::StorageMode::kDeviceTransient:
      break;
    default:
      assert(false && "Unhandled impeller::StorageMode value.");
  }
#endif
  return static_cast<ipl_storage_mode_t>(storage_mode);
}

static inline impeller::PixelFormat transmute(ipl_pixel_format_t pixel_format) {
#ifndef NDEBUG
  switch (pixel_format) {
    case IPL_PIXEL_FORMAT_UNKNOWN:
    case IPL_PIXEL_FORMAT_A8_UNORM_INT:
    case IPL_PIXEL_FORMAT_R8_UNORM_INT:
    case IPL_PIXEL_FORMAT_R8_G8_UNORM_INT:
    case IPL_PIXEL_FORMAT_R8_G8_B8_A8_UNORM_INT:
    case IPL_PIXEL_FORMAT_R8_G8_B8_A8_UNORM_INT_SRGB:
    case IPL_PIXEL_FORMAT_B8_G8_R8_A8_UNORM_INT:
    case IPL_PIXEL_FORMAT_B8_G8_R8_A8_UNORM_INT_SRGB:
    case IPL_PIXEL_FORMAT_R32_G32_B32_A32_FLOAT:
    case IPL_PIXEL_FORMAT_R16_G16_B16_A16_FLOAT:
    case IPL_PIXEL_FORMAT_B10_G10_R10_XR:
    case IPL_PIXEL_FORMAT_B10_G10_R10_XR_SRGB:
    case IPL_PIXEL_FORMAT_B10_G10_R10_A10_XR:
    case IPL_PIXEL_FORMAT_R32_FLOAT:
    case IPL_PIXEL_FORMAT_S8_UINT:
    case IPL_PIXEL_FORMAT_D24_UNORM_S8_UINT:
    case IPL_PIXEL_FORMAT_D32_FLOAT_S8_UINT:
    case IPL_PIXEL_FORMAT_BC1_RGBA_UNORM_INT:
    case IPL_PIXEL_FORMAT_BC1_RGBA_UNORM_INT_SRGB:
    case IPL_PIXEL_FORMAT_BC3_RGBA_UNORM_INT:
    case IPL_PIXEL_FORMAT_BC3_RGBA_UNORM_INT_SRGB:
    case IPL_PIXEL_FORMAT_BC5_RG_UNORM_INT:
    case IPL_PIXEL_FORMAT_BC7_RGBA_UNORM_INT:
    case IPL_PIXEL_FORMAT_BC7_RGBA_UNORM_INT_SRGB:
    case IPL_PIXEL_FORMAT_ETC2_RGB8_UNORM_INT:
    case IPL_PIXEL_FORMAT_ETC2_RGB8_UNORM_INT_SRGB:
    case IPL_PIXEL_FORMAT_ETC2_RGBA8_UNORM_INT:
    case IPL_PIXEL_FORMAT_ETC2_RGBA8_UNORM_INT_SRGB:
    case IPL_PIXEL_FORMAT_ASTC_4X4_LDR:
    case IPL_PIXEL_FORMAT_ASTC_4X4_LDR_SRGB:
    case IPL_PIXEL_FORMAT_ASTC_8X8_LDR:
    case IPL_PIXEL_FORMAT_ASTC_8X8_LDR_SRGB:
    case IPL_PIXEL_FORMAT_ASTC_4X4_HDR:
    case IPL_PIXEL_FORMAT_ASTC_8X8_HDR:
      break;
    default:
      assert(false && "Unhandled ipl_pixel_format_t value.");
  }
#endif
  return static_cast<impeller::PixelFormat>(pixel_format);
}

static inline ipl_pixel_format_t transmute(impeller::PixelFormat pixel_format) {
#ifndef NDEBUG
  switch (pixel_format) {
    case impeller::PixelFormat::kUnknown:
    case impeller::PixelFormat::kA8UNormInt:
    case impeller::PixelFormat::kR8UNormInt:
    case impeller::PixelFormat::kR8G8UNormInt:
    case impeller::PixelFormat::kR8G8B8A8UNormInt:
    case impeller::PixelFormat::kR8G8B8A8UNormIntSRGB:
    case impeller::PixelFormat::kB8G8R8A8UNormInt:
    case impeller::PixelFormat::kB8G8R8A8UNormIntSRGB:
    case impeller::PixelFormat::kR32G32B32A32Float:
    case impeller::PixelFormat::kR16G16B16A16Float:
    case impeller::PixelFormat::kB10G10R10XR:
    case impeller::PixelFormat::kB10G10R10XRSRGB:
    case impeller::PixelFormat::kB10G10R10A10XR:
    case impeller::PixelFormat::kR32Float:
    case impeller::PixelFormat::kS8UInt:
    case impeller::PixelFormat::kD24UnormS8Uint:
    case impeller::PixelFormat::kD32FloatS8UInt:
    case impeller::PixelFormat::kBC1RGBAUNormInt:
    case impeller::PixelFormat::kBC1RGBAUNormIntSRGB:
    case impeller::PixelFormat::kBC3RGBAUNormInt:
    case impeller::PixelFormat::kBC3RGBAUNormIntSRGB:
    case impeller::PixelFormat::kBC5RGUNormInt:
    case impeller::PixelFormat::kBC7RGBAUNormInt:
    case impeller::PixelFormat::kBC7RGBAUNormIntSRGB:
    case impeller::PixelFormat::kETC2RGB8UNormInt:
    case impeller::PixelFormat::kETC2RGB8UNormIntSRGB:
    case impeller::PixelFormat::kETC2RGBA8UNormInt:
    case impeller::PixelFormat::kETC2RGBA8UNormIntSRGB:
    case impeller::PixelFormat::kASTC4x4LDR:
    case impeller::PixelFormat::kASTC4x4LDRSRGB:
    case impeller::PixelFormat::kASTC8x8LDR:
    case impeller::PixelFormat::kASTC8x8LDRSRGB:
    case impeller::PixelFormat::kASTC4x4HDR:
    case impeller::PixelFormat::kASTC8x8HDR:
      break;
    default:
      assert(false && "Unhandled impeller::PixelFormat value.");
  }
#endif
  return static_cast<ipl_pixel_format_t>(pixel_format);
}

static inline impeller::BlendFactor transmute(ipl_blend_factor_t blend_factor) {
#ifndef NDEBUG
  switch (blend_factor) {
    case IPL_BLEND_FACTOR_ZERO:
    case IPL_BLEND_FACTOR_ONE:
    case IPL_BLEND_FACTOR_SOURCE_COLOR:
    case IPL_BLEND_FACTOR_ONE_MINUS_SOURCE_COLOR:
    case IPL_BLEND_FACTOR_SOURCE_ALPHA:
    case IPL_BLEND_FACTOR_ONE_MINUS_SOURCE_ALPHA:
    case IPL_BLEND_FACTOR_DESTINATION_COLOR:
    case IPL_BLEND_FACTOR_ONE_MINUS_DESTINATION_COLOR:
    case IPL_BLEND_FACTOR_DESTINATION_ALPHA:
    case IPL_BLEND_FACTOR_ONE_MINUS_DESTINATION_ALPHA:
    case IPL_BLEND_FACTOR_SOURCE_ALPHA_SATURATED:
    case IPL_BLEND_FACTOR_BLEND_COLOR:
    case IPL_BLEND_FACTOR_ONE_MINUS_BLEND_COLOR:
    case IPL_BLEND_FACTOR_BLEND_ALPHA:
    case IPL_BLEND_FACTOR_ONE_MINUS_BLEND_ALPHA:
      break;
    default:
      assert(false && "Unhandled ipl_blend_factor_t value.");
  }
#endif
  return static_cast<impeller::BlendFactor>(blend_factor);
}

static inline ipl_blend_factor_t transmute(impeller::BlendFactor blend_factor) {
#ifndef NDEBUG
  switch (blend_factor) {
    case impeller::BlendFactor::kZero:
    case impeller::BlendFactor::kOne:
    case impeller::BlendFactor::kSourceColor:
    case impeller::BlendFactor::kOneMinusSourceColor:
    case impeller::BlendFactor::kSourceAlpha:
    case impeller::BlendFactor::kOneMinusSourceAlpha:
    case impeller::BlendFactor::kDestinationColor:
    case impeller::BlendFactor::kOneMinusDestinationColor:
    case impeller::BlendFactor::kDestinationAlpha:
    case impeller::BlendFactor::kOneMinusDestinationAlpha:
    case impeller::BlendFactor::kSourceAlphaSaturated:
    case impeller::BlendFactor::kBlendColor:
    case impeller::BlendFactor::kOneMinusBlendColor:
    case impeller::BlendFactor::kBlendAlpha:
    case impeller::BlendFactor::kOneMinusBlendAlpha:
      break;
    default:
      assert(false && "Unhandled impeller::BlendFactor value.");
  }
#endif
  return static_cast<ipl_blend_factor_t>(blend_factor);
}

static inline impeller::BlendOperation transmute(
    ipl_blend_operation_t blend_operation) {
#ifndef NDEBUG
  switch (blend_operation) {
    case IPL_BLEND_OPERATION_ADD:
    case IPL_BLEND_OPERATION_SUBTRACT:
    case IPL_BLEND_OPERATION_REVERSE_SUBTRACT:
      break;
    default:
      assert(false && "Unhandled ipl_blend_operation_t value.");
  }
#endif
  return static_cast<impeller::BlendOperation>(blend_operation);
}

static inline ipl_blend_operation_t transmute(
    impeller::BlendOperation blend_operation) {
#ifndef NDEBUG
  switch (blend_operation) {
    case impeller::BlendOperation::kAdd:
    case impeller::BlendOperation::kSubtract:
    case impeller::BlendOperation::kReverseSubtract:
      break;
    default:
      assert(false && "Unhandled impeller::BlendOperation value.");
  }
#endif
  return static_cast<ipl_blend_operation_t>(blend_operation);
}

static inline impeller::LoadAction transmute(ipl_load_action_t load_action) {
#ifndef NDEBUG
  switch (load_action) {
    case IPL_LOAD_ACTION_DONT_CARE:
    case IPL_LOAD_ACTION_LOAD:
    case IPL_LOAD_ACTION_CLEAR:
      break;
    default:
      assert(false && "Unhandled ipl_load_action_t value.");
  }
#endif
  return static_cast<impeller::LoadAction>(load_action);
}

static inline ipl_load_action_t transmute(impeller::LoadAction load_action) {
#ifndef NDEBUG
  switch (load_action) {
    case impeller::LoadAction::kDontCare:
    case impeller::LoadAction::kLoad:
    case impeller::LoadAction::kClear:
      break;
    default:
      assert(false && "Unhandled impeller::LoadAction value.");
  }
#endif
  return static_cast<ipl_load_action_t>(load_action);
}

static inline impeller::StoreAction transmute(ipl_store_action_t store_action) {
#ifndef NDEBUG
  switch (store_action) {
    case IPL_STORE_ACTION_DONT_CARE:
    case IPL_STORE_ACTION_STORE:
    case IPL_STORE_ACTION_MULTISAMPLE_RESOLVE:
    case IPL_STORE_ACTION_STORE_AND_MULTISAMPLE_RESOLVE:
      break;
    default:
      assert(false && "Unhandled ipl_store_action_t value.");
  }
#endif
  return static_cast<impeller::StoreAction>(store_action);
}

static inline ipl_store_action_t transmute(impeller::StoreAction store_action) {
#ifndef NDEBUG
  switch (store_action) {
    case impeller::StoreAction::kDontCare:
    case impeller::StoreAction::kStore:
    case impeller::StoreAction::kMultisampleResolve:
    case impeller::StoreAction::kStoreAndMultisampleResolve:
      break;
    default:
      assert(false && "Unhandled impeller::StoreAction value.");
  }
#endif
  return static_cast<ipl_store_action_t>(store_action);
}

static inline impeller::TextureType transmute(ipl_texture_type_t texture_type) {
#ifndef NDEBUG
  switch (texture_type) {
    case IPL_TEXTURE_TYPE_2D:
    case IPL_TEXTURE_TYPE_2D_MULTISAMPLE:
    case IPL_TEXTURE_TYPE_CUBE:
    case IPL_TEXTURE_TYPE_EXTERNAL_OES:
      break;
    default:
      assert(false && "Unhandled ipl_texture_type_t value.");
  }
#endif
  return static_cast<impeller::TextureType>(texture_type);
}

static inline ipl_texture_type_t transmute(impeller::TextureType texture_type) {
#ifndef NDEBUG
  switch (texture_type) {
    case impeller::TextureType::kTexture2D:
    case impeller::TextureType::kTexture2DMultisample:
    case impeller::TextureType::kTextureCube:
    case impeller::TextureType::kTextureExternalOES:
      break;
    default:
      assert(false && "Unhandled impeller::TextureType value.");
  }
#endif
  return static_cast<ipl_texture_type_t>(texture_type);
}

static inline impeller::SampleCount transmute(ipl_sample_count_t sample_count) {
#ifndef NDEBUG
  switch (sample_count) {
    case IPL_SAMPLE_COUNT_1:
    case IPL_SAMPLE_COUNT_4:
      break;
    default:
      assert(false && "Unhandled ipl_sample_count_t value.");
  }
#endif
  return static_cast<impeller::SampleCount>(sample_count);
}

static inline ipl_sample_count_t transmute(impeller::SampleCount sample_count) {
#ifndef NDEBUG
  switch (sample_count) {
    case impeller::SampleCount::kCount1:
    case impeller::SampleCount::kCount4:
      break;
    default:
      assert(false && "Unhandled impeller::SampleCount value.");
  }
#endif
  return static_cast<ipl_sample_count_t>(sample_count);
}

static inline impeller::TextureUsage transmute(
    ipl_texture_usage_t texture_usage) {
#ifndef NDEBUG
  switch (texture_usage) {
    case IPL_TEXTURE_USAGE_UNKNOWN:
    case IPL_TEXTURE_USAGE_SHADER_READ:
    case IPL_TEXTURE_USAGE_SHADER_WRITE:
    case IPL_TEXTURE_USAGE_RENDER_TARGET:
      break;
    default:
      assert(false && "Unhandled ipl_texture_usage_t value.");
  }
#endif
  return static_cast<impeller::TextureUsage>(texture_usage);
}

static inline ipl_texture_usage_t transmute(
    impeller::TextureUsage texture_usage) {
#ifndef NDEBUG
  switch (texture_usage) {
    case impeller::TextureUsage::kUnknown:
    case impeller::TextureUsage::kShaderRead:
    case impeller::TextureUsage::kShaderWrite:
    case impeller::TextureUsage::kRenderTarget:
      break;
    default:
      assert(false && "Unhandled impeller::TextureUsage value.");
  }
#endif
  return static_cast<ipl_texture_usage_t>(texture_usage);
}

static inline impeller::CullMode transmute(ipl_cull_mode_t cull_mode) {
#ifndef NDEBUG
  switch (cull_mode) {
    case IPL_CULL_MODE_NONE:
    case IPL_CULL_MODE_FRONT_FACE:
    case IPL_CULL_MODE_BACK_FACE:
      break;
    default:
      assert(false && "Unhandled ipl_cull_mode_t value.");
  }
#endif
  return static_cast<impeller::CullMode>(cull_mode);
}

static inline ipl_cull_mode_t transmute(impeller::CullMode cull_mode) {
#ifndef NDEBUG
  switch (cull_mode) {
    case impeller::CullMode::kNone:
    case impeller::CullMode::kFrontFace:
    case impeller::CullMode::kBackFace:
      break;
    default:
      assert(false && "Unhandled impeller::CullMode value.");
  }
#endif
  return static_cast<ipl_cull_mode_t>(cull_mode);
}

static inline impeller::IndexType transmute(ipl_index_type_t index_type) {
#ifndef NDEBUG
  switch (index_type) {
    case IPL_INDEX_TYPE_UNKNOWN:
    case IPL_INDEX_TYPE_16BIT:
    case IPL_INDEX_TYPE_32BIT:
    case IPL_INDEX_TYPE_NONE:
      break;
    default:
      assert(false && "Unhandled ipl_index_type_t value.");
  }
#endif
  return static_cast<impeller::IndexType>(index_type);
}

static inline ipl_index_type_t transmute(impeller::IndexType index_type) {
#ifndef NDEBUG
  switch (index_type) {
    case impeller::IndexType::kUnknown:
    case impeller::IndexType::k16bit:
    case impeller::IndexType::k32bit:
    case impeller::IndexType::kNone:
      break;
    default:
      assert(false && "Unhandled impeller::IndexType value.");
  }
#endif
  return static_cast<ipl_index_type_t>(index_type);
}

static inline impeller::PrimitiveType transmute(
    ipl_primitive_type_t primitive_type) {
#ifndef NDEBUG
  switch (primitive_type) {
    case IPL_PRIMITIVE_TYPE_TRIANGLE:
    case IPL_PRIMITIVE_TYPE_TRIANGLE_STRIP:
    case IPL_PRIMITIVE_TYPE_LINE:
    case IPL_PRIMITIVE_TYPE_LINE_STRIP:
    case IPL_PRIMITIVE_TYPE_POINT:
    case IPL_PRIMITIVE_TYPE_TRIANGLE_FAN:
      break;
    default:
      assert(false && "Unhandled ipl_primitive_type_t value.");
  }
#endif
  return static_cast<impeller::PrimitiveType>(primitive_type);
}

static inline ipl_primitive_type_t transmute(
    impeller::PrimitiveType primitive_type) {
#ifndef NDEBUG
  switch (primitive_type) {
    case impeller::PrimitiveType::kTriangle:
    case impeller::PrimitiveType::kTriangleStrip:
    case impeller::PrimitiveType::kLine:
    case impeller::PrimitiveType::kLineStrip:
    case impeller::PrimitiveType::kPoint:
    case impeller::PrimitiveType::kTriangleFan:
      break;
    default:
      assert(false && "Unhandled impeller::PrimitiveType value.");
  }
#endif
  return static_cast<ipl_primitive_type_t>(primitive_type);
}

static inline impeller::PolygonMode transmute(ipl_polygon_mode_t polygon_mode) {
#ifndef NDEBUG
  switch (polygon_mode) {
    case IPL_POLYGON_MODE_FILL:
    case IPL_POLYGON_MODE_LINE:
      break;
    default:
      assert(false && "Unhandled ipl_polygon_mode_t value.");
  }
#endif
  return static_cast<impeller::PolygonMode>(polygon_mode);
}

static inline ipl_polygon_mode_t transmute(impeller::PolygonMode polygon_mode) {
#ifndef NDEBUG
  switch (polygon_mode) {
    case impeller::PolygonMode::kFill:
    case impeller::PolygonMode::kLine:
      break;
    default:
      assert(false && "Unhandled impeller::PolygonMode value.");
  }
#endif
  return static_cast<ipl_polygon_mode_t>(polygon_mode);
}

#endif  // FLUTTER_IPL_SRC_CORE_FORMATS_H_
