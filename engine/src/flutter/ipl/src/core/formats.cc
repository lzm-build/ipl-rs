#include <type_traits>

#include "core/formats.h"
#include "impeller/core/formats.h"

static_assert(std::is_same_v<std::underlying_type_t<impeller::WindingOrder>,
                             std::underlying_type_t<ipl_winding_order_t>>);

constexpr bool operator==(impeller::WindingOrder lhs, ipl_winding_order_t rhs) {
  return static_cast<ipl_winding_order_t>(lhs) == rhs;
}

static_assert(impeller::WindingOrder::kClockwise ==
              IPL_WINDING_ORDER_CLOCKWISE);
static_assert(impeller::WindingOrder::kCounterClockwise ==
              IPL_WINDING_ORDER_COUNTER_CLOCKWISE);

static_assert(std::is_same_v<std::underlying_type_t<impeller::StorageMode>,
                             std::underlying_type_t<ipl_storage_mode_t>>);

constexpr bool operator==(impeller::StorageMode lhs, ipl_storage_mode_t rhs) {
  return static_cast<ipl_storage_mode_t>(lhs) == rhs;
}

static_assert(impeller::StorageMode::kHostVisible ==
              IPL_STORAGE_MODE_HOST_VISIBLE);
static_assert(impeller::StorageMode::kDevicePrivate ==
              IPL_STORAGE_MODE_DEVICE_PRIVATE);
static_assert(impeller::StorageMode::kDeviceTransient ==
              IPL_STORAGE_MODE_DEVICE_TRANSIENT);

static_assert(std::is_same_v<std::underlying_type_t<impeller::PixelFormat>,
                             std::underlying_type_t<ipl_pixel_format_t>>);

constexpr bool operator==(impeller::PixelFormat lhs, ipl_pixel_format_t rhs) {
  return static_cast<ipl_pixel_format_t>(lhs) == rhs;
}

static_assert(impeller::PixelFormat::kUnknown == IPL_PIXEL_FORMAT_UNKNOWN);
static_assert(impeller::PixelFormat::kA8UNormInt ==
              IPL_PIXEL_FORMAT_A8_UNORM_INT);
static_assert(impeller::PixelFormat::kR8UNormInt ==
              IPL_PIXEL_FORMAT_R8_UNORM_INT);
static_assert(impeller::PixelFormat::kR8G8UNormInt ==
              IPL_PIXEL_FORMAT_R8_G8_UNORM_INT);
static_assert(impeller::PixelFormat::kR8G8B8A8UNormInt ==
              IPL_PIXEL_FORMAT_R8_G8_B8_A8_UNORM_INT);
static_assert(impeller::PixelFormat::kR8G8B8A8UNormIntSRGB ==
              IPL_PIXEL_FORMAT_R8_G8_B8_A8_UNORM_INT_SRGB);
static_assert(impeller::PixelFormat::kB8G8R8A8UNormInt ==
              IPL_PIXEL_FORMAT_B8_G8_R8_A8_UNORM_INT);
static_assert(impeller::PixelFormat::kB8G8R8A8UNormIntSRGB ==
              IPL_PIXEL_FORMAT_B8_G8_R8_A8_UNORM_INT_SRGB);
static_assert(impeller::PixelFormat::kR32G32B32A32Float ==
              IPL_PIXEL_FORMAT_R32_G32_B32_A32_FLOAT);
static_assert(impeller::PixelFormat::kR16G16B16A16Float ==
              IPL_PIXEL_FORMAT_R16_G16_B16_A16_FLOAT);
static_assert(impeller::PixelFormat::kB10G10R10XR ==
              IPL_PIXEL_FORMAT_B10_G10_R10_XR);
static_assert(impeller::PixelFormat::kB10G10R10XRSRGB ==
              IPL_PIXEL_FORMAT_B10_G10_R10_XR_SRGB);
static_assert(impeller::PixelFormat::kB10G10R10A10XR ==
              IPL_PIXEL_FORMAT_B10_G10_R10_A10_XR);
static_assert(impeller::PixelFormat::kR32Float == IPL_PIXEL_FORMAT_R32_FLOAT);
static_assert(impeller::PixelFormat::kS8UInt == IPL_PIXEL_FORMAT_S8_UINT);
static_assert(impeller::PixelFormat::kD24UnormS8Uint ==
              IPL_PIXEL_FORMAT_D24_UNORM_S8_UINT);
static_assert(impeller::PixelFormat::kD32FloatS8UInt ==
              IPL_PIXEL_FORMAT_D32_FLOAT_S8_UINT);
static_assert(impeller::PixelFormat::kBC1RGBAUNormInt ==
              IPL_PIXEL_FORMAT_BC1_RGBA_UNORM_INT);
static_assert(impeller::PixelFormat::kBC1RGBAUNormIntSRGB ==
              IPL_PIXEL_FORMAT_BC1_RGBA_UNORM_INT_SRGB);
static_assert(impeller::PixelFormat::kBC3RGBAUNormInt ==
              IPL_PIXEL_FORMAT_BC3_RGBA_UNORM_INT);
static_assert(impeller::PixelFormat::kBC3RGBAUNormIntSRGB ==
              IPL_PIXEL_FORMAT_BC3_RGBA_UNORM_INT_SRGB);
static_assert(impeller::PixelFormat::kBC5RGUNormInt ==
              IPL_PIXEL_FORMAT_BC5_RG_UNORM_INT);
static_assert(impeller::PixelFormat::kBC7RGBAUNormInt ==
              IPL_PIXEL_FORMAT_BC7_RGBA_UNORM_INT);
static_assert(impeller::PixelFormat::kBC7RGBAUNormIntSRGB ==
              IPL_PIXEL_FORMAT_BC7_RGBA_UNORM_INT_SRGB);
static_assert(impeller::PixelFormat::kETC2RGB8UNormInt ==
              IPL_PIXEL_FORMAT_ETC2_RGB8_UNORM_INT);
static_assert(impeller::PixelFormat::kETC2RGB8UNormIntSRGB ==
              IPL_PIXEL_FORMAT_ETC2_RGB8_UNORM_INT_SRGB);
static_assert(impeller::PixelFormat::kETC2RGBA8UNormInt ==
              IPL_PIXEL_FORMAT_ETC2_RGBA8_UNORM_INT);
static_assert(impeller::PixelFormat::kETC2RGBA8UNormIntSRGB ==
              IPL_PIXEL_FORMAT_ETC2_RGBA8_UNORM_INT_SRGB);
static_assert(impeller::PixelFormat::kASTC4x4LDR ==
              IPL_PIXEL_FORMAT_ASTC_4X4_LDR);
static_assert(impeller::PixelFormat::kASTC4x4LDRSRGB ==
              IPL_PIXEL_FORMAT_ASTC_4X4_LDR_SRGB);
static_assert(impeller::PixelFormat::kASTC8x8LDR ==
              IPL_PIXEL_FORMAT_ASTC_8X8_LDR);
static_assert(impeller::PixelFormat::kASTC8x8LDRSRGB ==
              IPL_PIXEL_FORMAT_ASTC_8X8_LDR_SRGB);
static_assert(impeller::PixelFormat::kASTC4x4HDR ==
              IPL_PIXEL_FORMAT_ASTC_4X4_HDR);
static_assert(impeller::PixelFormat::kASTC8x8HDR ==
              IPL_PIXEL_FORMAT_ASTC_8X8_HDR);

static_assert(std::is_same_v<std::underlying_type_t<impeller::BlendFactor>,
                             std::underlying_type_t<ipl_blend_factor_t>>);

constexpr bool operator==(impeller::BlendFactor lhs, ipl_blend_factor_t rhs) {
  return static_cast<ipl_blend_factor_t>(lhs) == rhs;
}

static_assert(impeller::BlendFactor::kZero == IPL_BLEND_FACTOR_ZERO);
static_assert(impeller::BlendFactor::kOne == IPL_BLEND_FACTOR_ONE);
static_assert(impeller::BlendFactor::kSourceColor ==
              IPL_BLEND_FACTOR_SOURCE_COLOR);
static_assert(impeller::BlendFactor::kOneMinusSourceColor ==
              IPL_BLEND_FACTOR_ONE_MINUS_SOURCE_COLOR);
static_assert(impeller::BlendFactor::kSourceAlpha ==
              IPL_BLEND_FACTOR_SOURCE_ALPHA);
static_assert(impeller::BlendFactor::kOneMinusSourceAlpha ==
              IPL_BLEND_FACTOR_ONE_MINUS_SOURCE_ALPHA);
static_assert(impeller::BlendFactor::kDestinationColor ==
              IPL_BLEND_FACTOR_DESTINATION_COLOR);
static_assert(impeller::BlendFactor::kOneMinusDestinationColor ==
              IPL_BLEND_FACTOR_ONE_MINUS_DESTINATION_COLOR);
static_assert(impeller::BlendFactor::kDestinationAlpha ==
              IPL_BLEND_FACTOR_DESTINATION_ALPHA);
static_assert(impeller::BlendFactor::kOneMinusDestinationAlpha ==
              IPL_BLEND_FACTOR_ONE_MINUS_DESTINATION_ALPHA);
static_assert(impeller::BlendFactor::kSourceAlphaSaturated ==
              IPL_BLEND_FACTOR_SOURCE_ALPHA_SATURATED);
static_assert(impeller::BlendFactor::kBlendColor ==
              IPL_BLEND_FACTOR_BLEND_COLOR);
static_assert(impeller::BlendFactor::kOneMinusBlendColor ==
              IPL_BLEND_FACTOR_ONE_MINUS_BLEND_COLOR);
static_assert(impeller::BlendFactor::kBlendAlpha ==
              IPL_BLEND_FACTOR_BLEND_ALPHA);
static_assert(impeller::BlendFactor::kOneMinusBlendAlpha ==
              IPL_BLEND_FACTOR_ONE_MINUS_BLEND_ALPHA);

static_assert(std::is_same_v<std::underlying_type_t<impeller::BlendOperation>,
                             std::underlying_type_t<ipl_blend_operation_t>>);

constexpr bool operator==(impeller::BlendOperation lhs,
                          ipl_blend_operation_t rhs) {
  return static_cast<ipl_blend_operation_t>(lhs) == rhs;
}

static_assert(impeller::BlendOperation::kAdd == IPL_BLEND_OPERATION_ADD);
static_assert(impeller::BlendOperation::kSubtract ==
              IPL_BLEND_OPERATION_SUBTRACT);
static_assert(impeller::BlendOperation::kReverseSubtract ==
              IPL_BLEND_OPERATION_REVERSE_SUBTRACT);

static_assert(std::is_same_v<std::underlying_type_t<impeller::LoadAction>,
                             std::underlying_type_t<ipl_load_action_t>>);

constexpr bool operator==(impeller::LoadAction lhs, ipl_load_action_t rhs) {
  return static_cast<ipl_load_action_t>(lhs) == rhs;
}

static_assert(impeller::LoadAction::kDontCare == IPL_LOAD_ACTION_DONT_CARE);
static_assert(impeller::LoadAction::kLoad == IPL_LOAD_ACTION_LOAD);
static_assert(impeller::LoadAction::kClear == IPL_LOAD_ACTION_CLEAR);

static_assert(std::is_same_v<std::underlying_type_t<impeller::StoreAction>,
                             std::underlying_type_t<ipl_store_action_t>>);

constexpr bool operator==(impeller::StoreAction lhs, ipl_store_action_t rhs) {
  return static_cast<ipl_store_action_t>(lhs) == rhs;
}

static_assert(impeller::StoreAction::kDontCare == IPL_STORE_ACTION_DONT_CARE);
static_assert(impeller::StoreAction::kStore == IPL_STORE_ACTION_STORE);
static_assert(impeller::StoreAction::kMultisampleResolve ==
              IPL_STORE_ACTION_MULTISAMPLE_RESOLVE);
static_assert(impeller::StoreAction::kStoreAndMultisampleResolve ==
              IPL_STORE_ACTION_STORE_AND_MULTISAMPLE_RESOLVE);

static_assert(std::is_same_v<std::underlying_type_t<impeller::TextureType>,
                             std::underlying_type_t<ipl_texture_type_t>>);

constexpr bool operator==(impeller::TextureType lhs, ipl_texture_type_t rhs) {
  return static_cast<ipl_texture_type_t>(lhs) == rhs;
}

static_assert(impeller::TextureType::kTexture2D == IPL_TEXTURE_TYPE_2D);
static_assert(impeller::TextureType::kTexture2DMultisample ==
              IPL_TEXTURE_TYPE_2D_MULTISAMPLE);
static_assert(impeller::TextureType::kTextureCube == IPL_TEXTURE_TYPE_CUBE);
static_assert(impeller::TextureType::kTextureExternalOES ==
              IPL_TEXTURE_TYPE_EXTERNAL_OES);

static_assert(std::is_same_v<std::underlying_type_t<impeller::SampleCount>,
                             std::underlying_type_t<ipl_sample_count_t>>);

constexpr bool operator==(impeller::SampleCount lhs, ipl_sample_count_t rhs) {
  return static_cast<ipl_sample_count_t>(lhs) == rhs;
}

static_assert(impeller::SampleCount::kCount1 == IPL_SAMPLE_COUNT_1);
static_assert(impeller::SampleCount::kCount4 == IPL_SAMPLE_COUNT_4);

static_assert(std::is_same_v<std::underlying_type_t<impeller::TextureUsage>,
                             std::underlying_type_t<ipl_texture_usage_t>>);

constexpr bool operator==(impeller::TextureUsage lhs, ipl_texture_usage_t rhs) {
  return static_cast<ipl_texture_usage_t>(lhs) == rhs;
}

static_assert(impeller::TextureUsage::kUnknown == IPL_TEXTURE_USAGE_UNKNOWN);
static_assert(impeller::TextureUsage::kShaderRead ==
              IPL_TEXTURE_USAGE_SHADER_READ);
static_assert(impeller::TextureUsage::kShaderWrite ==
              IPL_TEXTURE_USAGE_SHADER_WRITE);
static_assert(impeller::TextureUsage::kRenderTarget ==
              IPL_TEXTURE_USAGE_RENDER_TARGET);

static_assert(std::is_same_v<std::underlying_type_t<impeller::CullMode>,
                             std::underlying_type_t<ipl_cull_mode_t>>);

constexpr bool operator==(impeller::CullMode lhs, ipl_cull_mode_t rhs) {
  return static_cast<ipl_cull_mode_t>(lhs) == rhs;
}

static_assert(impeller::CullMode::kNone == IPL_CULL_MODE_NONE);
static_assert(impeller::CullMode::kFrontFace == IPL_CULL_MODE_FRONT_FACE);
static_assert(impeller::CullMode::kBackFace == IPL_CULL_MODE_BACK_FACE);

static_assert(std::is_same_v<std::underlying_type_t<impeller::IndexType>,
                             std::underlying_type_t<ipl_index_type_t>>);

constexpr bool operator==(impeller::IndexType lhs, ipl_index_type_t rhs) {
  return static_cast<ipl_index_type_t>(lhs) == rhs;
}

static_assert(impeller::IndexType::kUnknown == IPL_INDEX_TYPE_UNKNOWN);
static_assert(impeller::IndexType::k16bit == IPL_INDEX_TYPE_16BIT);
static_assert(impeller::IndexType::k32bit == IPL_INDEX_TYPE_32BIT);
static_assert(impeller::IndexType::kNone == IPL_INDEX_TYPE_NONE);

static_assert(std::is_same_v<std::underlying_type_t<impeller::PrimitiveType>,
                             std::underlying_type_t<ipl_primitive_type_t>>);

constexpr bool operator==(impeller::PrimitiveType lhs,
                          ipl_primitive_type_t rhs) {
  return static_cast<ipl_primitive_type_t>(lhs) == rhs;
}

static_assert(impeller::PrimitiveType::kTriangle ==
              IPL_PRIMITIVE_TYPE_TRIANGLE);
static_assert(impeller::PrimitiveType::kTriangleStrip ==
              IPL_PRIMITIVE_TYPE_TRIANGLE_STRIP);
static_assert(impeller::PrimitiveType::kLine == IPL_PRIMITIVE_TYPE_LINE);
static_assert(impeller::PrimitiveType::kLineStrip ==
              IPL_PRIMITIVE_TYPE_LINE_STRIP);
static_assert(impeller::PrimitiveType::kPoint == IPL_PRIMITIVE_TYPE_POINT);
static_assert(impeller::PrimitiveType::kTriangleFan ==
              IPL_PRIMITIVE_TYPE_TRIANGLE_FAN);

static_assert(std::is_same_v<std::underlying_type_t<impeller::PolygonMode>,
                             std::underlying_type_t<ipl_polygon_mode_t>>);

constexpr bool operator==(impeller::PolygonMode lhs, ipl_polygon_mode_t rhs) {
  return static_cast<ipl_polygon_mode_t>(lhs) == rhs;
}

static_assert(impeller::PolygonMode::kFill == IPL_POLYGON_MODE_FILL);
static_assert(impeller::PolygonMode::kLine == IPL_POLYGON_MODE_LINE);
