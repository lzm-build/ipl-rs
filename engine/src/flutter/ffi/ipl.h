#ifndef FLUTTER_FFI_IPL_H_
#define FLUTTER_FFI_IPL_H_

#include <stdalign.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <cstddef>

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/impeller/geometry/matrix.h
// ---------------------------------------------------------------------------

// impeller::Matrix
typedef struct ipl_matrix {
  float data[16];
} ipl_matrix_t;

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/impeller/geometry/matrix.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/impeller/geometry/point.h
// ---------------------------------------------------------------------------

// impeller::Point
typedef struct ipl_f32_point {
  float x;
  float y;
} ipl_f32_point_t;

// impeller::IPoint32
typedef struct ipl_i32_point {
  int32_t x;
  int32_t y;
} ipl_i32_point_t;

// impeller::UintPoint32
typedef struct ipl_u32_point {
  uint32_t x;
  uint32_t y;
} ipl_u32_point_t;

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/impeller/geometry/point.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/impeller/geometry/rect.h
// ---------------------------------------------------------------------------

// impeller::Rect
typedef struct ipl_f32_rect {
  float left;
  float top;
  float right;
  float bottom;
} ipl_f32_rect_t;

// impeller::IRect32
typedef struct ipl_i32_rect {
  int32_t left;
  int32_t top;
  int32_t right;
  int32_t bottom;
} ipl_i32_rect_t;

// impeller::IRect64
typedef struct ipl_i64_rect {
  int64_t left;
  int64_t top;
  int64_t right;
  int64_t bottom;
} ipl_i64_rect_t;

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/impeller/geometry/rect.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/impeller/geometry/rstransform.h
// ---------------------------------------------------------------------------

// flutter::DlRSTransform
typedef struct ipl_rs_transform {
  float scaled_cos;
  float scaled_sin;
  float translate_x;
  float translate_y;
} ipl_rs_transform_t;

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/impeller/geometry/rstransform.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/impeller/geometry/size.h
// ---------------------------------------------------------------------------

// impeller::Size
typedef struct ipl_f32_size {
  float width;
  float height;
} ipl_f32_size_t;

// impeller::ISize32
typedef struct ipl_i32_size {
  int32_t width;
  int32_t height;
} ipl_i32_size_t;

// impeller::ISize64
typedef struct ipl_i64_size {
  int64_t width;
  int64_t height;
} ipl_i64_size_t;

// impeller::Vector2
typedef ipl_f32_point_t ipl_vector2_t;

// impeller::Quad
typedef struct ipl_quad {
  ipl_f32_point_t value[4];
} ipl_quad_t;

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/impeller/geometry/size.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/impeller/geometry/rounding_radii.h
// ---------------------------------------------------------------------------

// impeller::RoundingRadii
typedef struct ipl_rounding_radii {
  ipl_f32_size_t top_left;
  ipl_f32_point_t top_right;
  ipl_f32_point_t bottom_left;
  ipl_f32_point_t bottom_right;
} ipl_rounding_radii_t;

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/impeller/geometry/rounding_radii.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/impeller/geometry/round_rect.h
// ---------------------------------------------------------------------------

// impeller::RoundRect
typedef struct ipl_round_rect {
  ipl_f32_rect_t bounds;
  ipl_rounding_radii_t radii;
} ipl_round_rect_t;

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/impeller/geometry/round_rect.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/impeller/geometry/vector.h
// ---------------------------------------------------------------------------

// impeller::Vector3
typedef struct ipl_vector3 {
  float x;
  float y;
  float z;
} ipl_vector3_t;

// impeller::Vector4
typedef struct ipl_vector4 {
  float x;
  float y;
  float z;
  float w;
} ipl_vector4_t;

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/impeller/geometry/vector.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/impeller/base/flags.h
// ---------------------------------------------------------------------------

// impeller::Flags
typedef struct ipl_flags {
  bool antialiased_lines;
  bool use_sdfs;
} ipl_flags_t;

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/impeller/base/flags.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/impeller/core/formats.h
// ---------------------------------------------------------------------------

// impeller::WindingOrder
typedef enum ipl_winding_order : int {
  IPL_WINDING_ORDER_CLOCKWISE = 0,
  IPL_WINDING_ORDER_COUNTER_CLOCKWISE = 1,
} ipl_winding_order_t;

// impeller::StorageMode
typedef enum ipl_storage_mode : int {
  IPL_STORAGE_MODE_HOST_VISIBLE = 0,
  IPL_STORAGE_MODE_DEVICE_PRIVATE = 1,
  IPL_STORAGE_MODE_DEVICE_TRANSIENT = 2,
} ipl_storage_mode_t;

// impeller::PixelFormat
typedef enum ipl_pixel_format : uint8_t {
  IPL_PIXEL_FORMAT_UNKNOWN = 0,
  IPL_PIXEL_FORMAT_A8_UNORM_INT = 1,
  IPL_PIXEL_FORMAT_R8_UNORM_INT = 2,
  IPL_PIXEL_FORMAT_R8_G8_UNORM_INT = 3,
  IPL_PIXEL_FORMAT_R8_G8_B8_A8_UNORM_INT = 4,
  IPL_PIXEL_FORMAT_R8_G8_B8_A8_UNORM_INT_SRGB = 5,
  IPL_PIXEL_FORMAT_B8_G8_R8_A8_UNORM_INT = 6,
  IPL_PIXEL_FORMAT_B8_G8_R8_A8_UNORM_INT_SRGB = 7,
  IPL_PIXEL_FORMAT_R32_G32_B32_A32_FLOAT = 8,
  IPL_PIXEL_FORMAT_R16_G16_B16_A16_FLOAT = 9,
  IPL_PIXEL_FORMAT_B10_G10_R10_XR = 10,
  IPL_PIXEL_FORMAT_B10_G10_R10_XR_SRGB = 11,
  IPL_PIXEL_FORMAT_B10_G10_R10_A10_XR = 12,
  IPL_PIXEL_FORMAT_R32_FLOAT = 13,
  IPL_PIXEL_FORMAT_S8_UINT = 14,
  IPL_PIXEL_FORMAT_D24_UNORM_S8_UINT = 15,
  IPL_PIXEL_FORMAT_D32_FLOAT_S8_UINT = 16,
  IPL_PIXEL_FORMAT_BC1_RGBA_UNORM_INT = 17,
  IPL_PIXEL_FORMAT_BC1_RGBA_UNORM_INT_SRGB = 18,
  IPL_PIXEL_FORMAT_BC3_RGBA_UNORM_INT = 19,
  IPL_PIXEL_FORMAT_BC3_RGBA_UNORM_INT_SRGB = 20,
  IPL_PIXEL_FORMAT_BC5_RG_UNORM_INT = 21,
  IPL_PIXEL_FORMAT_BC7_RGBA_UNORM_INT = 22,
  IPL_PIXEL_FORMAT_BC7_RGBA_UNORM_INT_SRGB = 23,
  IPL_PIXEL_FORMAT_ETC2_RGB8_UNORM_INT = 24,
  IPL_PIXEL_FORMAT_ETC2_RGB8_UNORM_INT_SRGB = 25,
  IPL_PIXEL_FORMAT_ETC2_RGBA8_UNORM_INT = 26,
  IPL_PIXEL_FORMAT_ETC2_RGBA8_UNORM_INT_SRGB = 27,
  IPL_PIXEL_FORMAT_ASTC_4X4_LDR = 28,
  IPL_PIXEL_FORMAT_ASTC_4X4_LDR_SRGB = 29,
  IPL_PIXEL_FORMAT_ASTC_8X8_LDR = 30,
  IPL_PIXEL_FORMAT_ASTC_8X8_LDR_SRGB = 31,
  IPL_PIXEL_FORMAT_ASTC_4X4_HDR = 32,
  IPL_PIXEL_FORMAT_ASTC_8X8_HDR = 33,
} ipl_pixel_format_t;

// impeller::TextureType
typedef enum ipl_texture_type : int {
  IPL_TEXTURE_TYPE_TEXTURE_2D = 0,
  IPL_TEXTURE_TYPE_TEXTURE_2D_MULTISAMPLE = 1,
  IPL_TEXTURE_TYPE_TEXTURE_CUBE = 2,
  IPL_TEXTURE_TYPE_TEXTURE_EXTERNAL_OES = 3,
} ipl_texture_type_t;

// impeller::SampleCount
typedef enum ipl_sample_count : uint8_t {
  IPL_SAMPLE_COUNT_COUNT_1 = 1,
  IPL_SAMPLE_COUNT_COUNT_4 = 4,
} ipl_sample_count_t;

// impeller::TextureUsage
typedef enum ipl_texture_usage : int {
  IPL_TEXTURE_USAGE_UNKNOWN = 0,
  IPL_TEXTURE_USAGE_SHADER_READ = 1 << 0,
  IPL_TEXTURE_USAGE_SHADER_WRITE = 1 << 1,
  IPL_TEXTURE_USAGE_RENDER_TARGET = 1 << 2,
} ipl_texture_usage_t;

// impeller::IndexType
typedef enum ipl_index_type : uint8_t {
  IPL_INDEX_TYPE_UNKNOWN = 0,
  IPL_INDEX_TYPE_16BIT = 1,
  IPL_INDEX_TYPE_32BIT = 2,
  IPL_INDEX_TYPE_NONE = 3,
} ipl_index_type_t;

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/impeller/core/formats.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/impeller/core/range.h
// ---------------------------------------------------------------------------

// impeller::Range
typedef struct ipl_range {
  size_t offset;
  size_t length;
} ipl_range_t;

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/impeller/core/range.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/impeller/core/allocator.h
// ---------------------------------------------------------------------------

#if defined(__i386__) || defined(__arm__) || defined(_M_IX86)
// std::shared_ptr<impeller::Allocator>
typedef struct ipl_allocator {
  alignas(4) char data[8];
} ipl_allocator_t;
#else
// std::shared_ptr<impeller::Allocator>
typedef struct ipl_allocator {
  alignas(8) char data[16];
} ipl_allocator_t;
#endif

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/impeller/core/allocator.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/impeller/core/buffer_view.h
// ---------------------------------------------------------------------------

#if defined(__i386__) || defined(__arm__) || defined(_M_IX86)
// impeller::BufferView
typedef struct ipl_buffer_view {
  // Opaque storage
  alignas(4) char data[20];
} ipl_buffer_view_t;
#else
// impeller::BufferView
typedef struct ipl_buffer_view {
  // Opaque storage
  alignas(8) char data[40];
} ipl_buffer_view_t;
#endif

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/impeller/core/buffer_view.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/impeller/core/device_buffer.h
// ---------------------------------------------------------------------------

#if defined(__i386__) || defined(__arm__) || defined(_M_IX86)
// std::shared_ptr<impeller::DeviceBuffer>
typedef struct ipl_device_buffer {
  // Opaque storage
  alignas(4) char data[8];
} ipl_device_buffer_t;

// std::shared_ptr<const impeller::DeviceBuffer>
typedef struct ipl_const_device_buffer {
  // Opaque storage
  alignas(4) char data[8];
} ipl_const_device_buffer_t;
#else
// std::shared_ptr<impeller::DeviceBuffer>
typedef struct ipl_device_buffer {
  // Opaque storage
  alignas(8) char data[16];
} ipl_device_buffer_t;

// std::shared_ptr<const impeller::DeviceBuffer>
typedef struct ipl_const_device_buffer {
  // Opaque storage
  alignas(8) char data[16];
} ipl_const_device_buffer_t;
#endif

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/impeller/core/device_buffer.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/impeller/core/device_buffer_descriptor.h
// ---------------------------------------------------------------------------

// impeller::DeviceBufferDescriptor
typedef struct ipl_device_buffer_descriptor {
  ipl_storage_mode_t storage_mode;
  size_t size;
  bool readback;
} ipl_device_buffer_descriptor_t;

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/impeller/core/device_buffer_descriptor.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/impeller/core/host_buffer.h
// ---------------------------------------------------------------------------

#if defined(__i386__) || defined(__arm__) || defined(_M_IX86)
// std::shared_ptr<impeller::HostBuffer>
typedef struct ipl_host_buffer {
  alignas(4) char data[8];
} ipl_host_buffer_t;
#else
// std::shared_ptr<impeller::HostBuffer>
typedef struct ipl_host_buffer {
  alignas(8) char data[16];
} ipl_host_buffer_t;
#endif

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/impeller/core/host_buffer.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/impeller/core/texture.h
// ---------------------------------------------------------------------------

#if defined(__i386__) || defined(__arm__) || defined(_M_IX86)
// std::shared_ptr<impeller::Texture>
typedef struct ipl_texture {
  alignas(4) char data[8];
} ipl_texture_t;
#else
// std::shared_ptr<impeller::Texture>
typedef struct ipl_texture {
  alignas(8) char data[16];
} ipl_texture_t;
#endif

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/impeller/core/texture.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/impeller/core/texture_descriptor.h
// ---------------------------------------------------------------------------

// impeller::CompressionType
typedef enum ipl_compression_type : int {
  IPL_COMPRESSION_TYPE_LOSSLESS = 0,
  IPL_COMPRESSION_TYPE_LOSSY = 1,
} ipl_compression_type_t;

// impeller::TextureDescriptor
typedef struct ipl_texture_descriptor {
  ipl_storage_mode_t storage_mode;
  ipl_texture_type_t type;
  ipl_pixel_format_t format;
  ipl_i64_size_t size;
  size_t mip_count;
  ipl_texture_usage_t usage;
  ipl_sample_count_t sample_count;
  ipl_compression_type_t compression_type;
} ipl_texture_descriptor_t;

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/impeller/core/texture_descriptor.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/impeller/core/vertex_buffer.h
// ---------------------------------------------------------------------------

// impeller::TextureDescriptor
typedef struct ipl_vertex_buffer {
  ipl_buffer_view_t vertex_buffer;
  ipl_buffer_view_t index_buffer;
  size_t vertex_count;
  ipl_index_type_t index_type;
} ipl_vertex_buffer_t;

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/impeller/core/vertex_buffer.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/display_list/dl_blend_mode.h
// ---------------------------------------------------------------------------

typedef enum ipl_blend_mode : uint8_t {
  IPL_BLEND_MODE_CLEAR = 0,
  IPL_BLEND_MODE_SRC = 1,
  IPL_BLEND_MODE_DST = 2,
  IPL_BLEND_MODE_SRC_OVER = 3,
  IPL_BLEND_MODE_DST_OVER = 4,
  IPL_BLEND_MODE_SRC_IN = 5,
  IPL_BLEND_MODE_DST_IN = 6,
  IPL_BLEND_MODE_SRC_OUT = 7,
  IPL_BLEND_MODE_DST_OUT = 8,
  IPL_BLEND_MODE_SRC_A_TOP = 9,
  IPL_BLEND_MODE_DST_A_TOP = 10,
  IPL_BLEND_MODE_XOR = 11,
  IPL_BLEND_MODE_PLUS = 12,
  IPL_BLEND_MODE_MODULATE = 13,
  IPL_BLEND_MODE_SCREEN = 14,
  IPL_BLEND_MODE_OVERLAY = 15,
  IPL_BLEND_MODE_DARKEN = 16,
  IPL_BLEND_MODE_LIGHTEN = 17,
  IPL_BLEND_MODE_COLOR_DODGE = 18,
  IPL_BLEND_MODE_COLOR_BURN = 19,
  IPL_BLEND_MODE_HARD_LIGHT = 20,
  IPL_BLEND_MODE_SOFT_LIGHT = 21,
  IPL_BLEND_MODE_DIFFERENCE = 22,
  IPL_BLEND_MODE_EXCLUSION = 23,
  IPL_BLEND_MODE_MULTIPLY = 24,
  IPL_BLEND_MODE_HUE = 25,
  IPL_BLEND_MODE_SATURATION = 26,
  IPL_BLEND_MODE_COLOR = 27,
  IPL_BLEND_MODE_LUMINOSITY = 28,
} ipl_blend_mode_t;

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/display_list/dl_blend_mode.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/display_list/dl_color.h
// ---------------------------------------------------------------------------

// flutter::DlColorSpace
typedef enum ipl_color_space : int {
  IPL_COLOR_SPACE_SRGB = 0,
  IPL_COLOR_SPACE_EXTENDED_SRGB = 1,
  IPL_COLOR_SPACE_DISPLAY_P3 = 2,
} ipl_color_space_t;

// flutter::DlColor
typedef struct ipl_color {
  float alpha;
  float red;
  float green;
  float blue;
  ipl_color_space_t color_space;
} ipl_color_t;

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/display_list/dl_color.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/display_list/dl_types.h
// ---------------------------------------------------------------------------

// flutter::DlClipOp
typedef enum ipl_clip_op : int {
  IPL_CLIP_OP_DIFFERENCE = 0,
  IPL_CLIP_OP_INTERSECT = 1,
} ipl_clip_op_t;

// flutter::DlPointMode
typedef enum ipl_point_mode : int {
  IPL_POINT_MODE_POINTS = 0,
  IPL_POINT_MODE_LINES = 1,
  IPL_POINT_MODE_POLYGON = 2,
} ipl_point_mode_t;

// flutter::DlSrcRectConstraint
typedef enum ipl_src_rect_constraint : int {
  IPL_SRC_RECT_CONSTRAINT_STRICT = 0,
  IPL_SRC_RECT_CONSTRAINT_FAST = 1,
} ipl_src_rect_constraint_t;

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/display_list/dl_types.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/display_list/dl_sampling_options.h
// ---------------------------------------------------------------------------

// flutter::DlFilterMode
typedef enum ipl_filter_mode : int {
  IPL_FILTER_MODE_NEAREST = 0,
  IPL_FILTER_MODE_LINEAR = 1,
} ipl_filter_mode_t;

// flutter::DlImageSampling
typedef enum ipl_image_sampling : int {
  IPL_IMAGE_SAMPLING_NEAREST_NEIGHBOR = 0,
  IPL_IMAGE_SAMPLING_LINEAR = 1,
  IPL_IMAGE_SAMPLING_MIPMAP_LINEAR = 2,
  IPL_IMAGE_SAMPLING_CUBIC = 3,
} ipl_image_sampling_t;

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/display_list/dl_sampling_options.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/display_list/dl_tile_mode.h
// ---------------------------------------------------------------------------

// flutter::DlTileMode
typedef enum ipl_tile_mode : int {
  IPL_TILE_MODE_CLAMP = 0,
  IPL_TILE_MODE_REPEAT = 1,
  IPL_TILE_MODE_MIRROR = 2,
  IPL_TILE_MODE_DECAL = 3,
} ipl_tile_mode_t;

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/display_list/dl_tile_mode.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/display_list/effects/dl_color_filter.h
// ---------------------------------------------------------------------------

#if defined(__i386__) || defined(__arm__) || defined(_M_IX86)
// std::shared_ptr<flutter::DlColorFilter>
typedef struct ipl_color_filter {
  alignas(4) char data[8];
} ipl_color_filter_t;
#else
// std::shared_ptr<flutter::DlColorFilter>
typedef struct ipl_color_filter {
  alignas(8) char data[16];
} ipl_color_filter_t;
#endif

#if defined(__i386__) || defined(__arm__) || defined(_M_IX86)
// std::shared_ptr<const flutter::DlColorFilter>
typedef struct ipl_const_color_filter {
  alignas(4) char data[8];
} ipl_const_color_filter_t;
#else
// std::shared_ptr<const flutter::DlColorFilter>
typedef struct ipl_const_color_filter {
  alignas(8) char data[16];
} ipl_const_color_filter_t;
#endif

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/display_list/effects/dl_color_filter.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/display_list/effects/dl_color_source.h
// ---------------------------------------------------------------------------

#if defined(__i386__) || defined(__arm__) || defined(_M_IX86)
// std::shared_ptr<flutter::DlColorSource>
typedef struct ipl_color_source {
  alignas(4) char data[8];
} ipl_color_source_t;
#else
// std::shared_ptr<flutter::DlColorSource>
typedef struct ipl_color_source {
  alignas(8) char data[16];
} ipl_color_source_t;
#endif

#if defined(__i386__) || defined(__arm__) || defined(_M_IX86)
// std::shared_ptr<const flutter::DlColorSource>
typedef struct ipl_const_color_source {
  alignas(4) char data[8];
} ipl_const_color_source_t;
#else
// std::shared_ptr<const flutter::DlColorSource>
typedef struct ipl_const_color_source {
  alignas(8) char data[16];
} ipl_const_color_source_t;
#endif

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/display_list/effects/dl_color_source.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/display_list/effects/dl_image_filter.h
// ---------------------------------------------------------------------------

#if defined(__i386__) || defined(__arm__) || defined(_M_IX86)
// std::shared_ptr<flutter::DlImageFilter>
typedef struct ipl_image_filter {
  alignas(4) char data[8];
} ipl_image_filter_t;
#else
// std::shared_ptr<flutter::DlImageFilter>
typedef struct ipl_image_filter {
  alignas(8) char data[16];
} ipl_image_filter_t;
#endif

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/display_list/effects/dl_image_filter.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/display_list/effects/dl_mask_filter.h
// ---------------------------------------------------------------------------

// flutter::DlBlurStyle
typedef enum ipl_blur_style : int {
  IPL_BLUR_STYLE_NORMAL = 0,
  IPL_BLUR_STYLE_SOLID = 1,
  IPL_BLUR_STYLE_OUTER = 2,
  IPL_BLUR_STYLE_INNER = 3,
} ipl_blur_style_t;

#if defined(__i386__) || defined(__arm__) || defined(_M_IX86)
// std::shared_ptr<flutter::DlMaskFilter>
typedef struct ipl_mask_filter {
  alignas(4) char data[8];
} ipl_mask_filter_t;
#else
// std::shared_ptr<flutter::DlMaskFilter>
typedef struct ipl_mask_filter {
  alignas(8) char data[16];
} ipl_mask_filter_t;
#endif

#if defined(__i386__) || defined(__arm__) || defined(_M_IX86)
// std::shared_ptr<const flutter::DlMaskFilter>
typedef struct ipl_const_mask_filter {
  alignas(4) char data[8];
} ipl_const_mask_filter_t;
#else
// std::shared_ptr<const flutter::DlMaskFilter>
typedef struct ipl_const_mask_filter {
  alignas(8) char data[16];
} ipl_const_mask_filter_t;
#endif

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/display_list/effects/dl_mask_filter.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/display_list/image/dl_image.h
// ---------------------------------------------------------------------------

#if defined(__i386__) || defined(__arm__) || defined(_M_IX86)
// sk_sp<flutter::DlImage>
typedef struct ipl_image {
  alignas(4) char data[4];
} ipl_image_t;
#else
// sk_sp<flutter::DlImage>
typedef struct ipl_image {
  alignas(8) char data[8];
} ipl_image_t;
#endif

#if defined(__i386__) || defined(__arm__) || defined(_M_IX86)
// sk_sp<const flutter::DlImage>
typedef struct ipl_const_image {
  alignas(4) char data[4];
} ipl_const_image_t;
#else
// sk_sp<const flutter::DlImage>
typedef struct ipl_const_image {
  alignas(8) char data[8];
} ipl_const_image_t;
#endif

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/display_list/image/dl_image.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/display_list/dl_paint.h
// ---------------------------------------------------------------------------

// flutter::DlDrawStyle
typedef enum ipl_draw_style : int {
  IPL_DRAW_STYLE_FILL = 0,
  IPL_DRAW_STYLE_STROKE = 1,
  IPL_DRAW_STYLE_STROKE_AND_FILL = 2,
} ipl_draw_style_t;

// flutter::DlStrokeCap
typedef enum ipl_stroke_cap : int {
  IPL_STROKE_CAP_BUTT = 0,
  IPL_STROKE_CAP_ROUND = 1,
  IPL_STROKE_CAP_SQUARE = 2,
} ipl_stroke_cap_t;

// flutter::DlStrokeJoin
typedef enum ipl_stroke_join : int {
  IPL_STROKE_JOIN_MITER = 0,
  IPL_STROKE_JOIN_ROUND = 1,
  IPL_STROKE_JOIN_BEVEL = 2,
} ipl_stroke_join_t;

#if defined(__i386__) || defined(__arm__) || defined(_M_IX86)
// flutter::DlPaint
typedef struct ipl_paint {
  alignas(4) char data[64];
} ipl_paint_t;
#else
// flutter::DlPaint
typedef struct ipl_paint {
  alignas(8) char data[96];
} ipl_paint_t;
#endif

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/display_list/dl_paint.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/display_list/dl_path.h
// ---------------------------------------------------------------------------

// flutter::DlPathFillType
typedef enum ipl_path_fill_type : int {
  IPL_PATH_FILL_TYPE_NON_ZERO = 0,
  IPL_PATH_FILL_TYPE_ODD = 1,
} ipl_path_fill_type_t;

#if defined(__i386__) || defined(__arm__) || defined(_M_IX86)
// flutter::DlPath
typedef struct ipl_path {
  alignas(4) char data[12];
} ipl_path_t;
#else
// flutter::DlPath
typedef struct ipl_path {
  alignas(8) char data[24];
} ipl_path_t;
#endif

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/display_list/dl_path.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/display_list/dl_path_builder.h
// ---------------------------------------------------------------------------

#if defined(__i386__) || defined(__arm__) || defined(_M_IX86)
// flutter::DlPathBuilder
typedef struct ipl_path_builder {
  alignas(4) char data[408];
} ipl_path_builder_t;
#else
// flutter::DlPathBuilder
typedef struct ipl_path_builder {
  alignas(8) char data[424];
} ipl_path_builder_t;
#endif

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/display_list/dl_path_builder.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/display_list/dl_text.h
// ---------------------------------------------------------------------------

#if defined(__i386__) || defined(__arm__) || defined(_M_IX86)
// std::shared_ptr<flutter::DlText>
typedef struct ipl_text {
  alignas(4) char data[8];
} ipl_text_t;
#else
// std::shared_ptr<flutter::DlText>
typedef struct ipl_text {
  alignas(8) char data[16];
} ipl_text_t;
#endif

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/display_list/dl_text.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/display_list/display_list.h
// ---------------------------------------------------------------------------

#if defined(__i386__) || defined(__arm__) || defined(_M_IX86)
// sk_sp<flutter::DisplayList>
typedef struct ipl_display_list {
  alignas(4) char data[4];
} ipl_display_list_t;
#else
// sk_sp<flutter::DisplayList>
typedef struct ipl_display_list {
  alignas(8) char data[8];
} ipl_display_list_t;
#endif

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/display_list/display_list.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/display_list/dl_builder.h
// ---------------------------------------------------------------------------

#if defined(__i386__) || defined(__arm__) || defined(_M_IX86)
// sk_sp<flutter::DisplayListBuilder>
typedef struct ipl_display_list_builder {
  alignas(4) char data[4];
} ipl_display_list_builder_t;
#else
// sk_sp<flutter::DisplayListBuilder>
typedef struct ipl_display_list_builder {
  alignas(8) char data[8];
} ipl_display_list_builder_t;
#endif

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/display_list/dl_builder.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/txt/src/txt/font_style.h
// ---------------------------------------------------------------------------

// txt::FontStyle
typedef enum ipl_font_style : int {
  IPL_FONT_STYLE_NORMAL = 0,
  IPL_FONT_STYLE_ITALIC = 1,
} ipl_font_style_t;

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/txt/src/txt/font_style.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/txt/src/txt/paragraph_style.h
// ---------------------------------------------------------------------------

// txt::TextAlign
typedef enum ipl_text_align : int {
  IPL_TEXT_ALIGN_LEFT = 0,
  IPL_TEXT_ALIGN_RIGHT = 1,
  IPL_TEXT_ALIGN_CENTER = 2,
  IPL_TEXT_ALIGN_JUSTIFY = 3,
  IPL_TEXT_ALIGN_START = 4,
  IPL_TEXT_ALIGN_END = 5,
} ipl_text_align_t;

// txt::TextDirection
typedef enum ipl_text_direction : int {
  IPL_TEXT_DIRECTION_RTL = 0,
  IPL_TEXT_DIRECTION_LTR = 1,
} ipl_text_direction_t;

// txt::TextHeightBehavior
typedef enum ipl_text_height_behavior : unsigned int {
  IPL_TEXT_HEIGHT_BEHAVIOR_ALL = 0x0,
  IPL_TEXT_HEIGHT_BEHAVIOR_DISABLE_FIRST_ASCENT = 0x1,
  IPL_TEXT_HEIGHT_BEHAVIOR_DISABLE_LAST_DESCENT = 0x2,
  IPL_TEXT_HEIGHT_BEHAVIOR_DISABLE_ALL = 0x1 | 0x2,
} ipl_text_height_behavior_t;

#if defined(__i386__) || defined(__arm__) || defined(_M_IX86)
typedef struct ipl_paragraph_style {
  alignas(8) char data[144];
} ipl_paragraph_style_t;
#else
typedef struct ipl_paragraph_style {
  alignas(8) char data[208];
} ipl_paragraph_style_t;
#endif

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/txt/src/txt/paragraph_style.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/txt/src/txt/text_decoration.h
// ---------------------------------------------------------------------------

// txt::TextDecoration
typedef enum ipl_text_decoration : int {
  IPL_TEXT_DECORATION_NONE = 0x0,
  IPL_TEXT_DECORATION_UNDERLINE = 0x1,
  IPL_TEXT_DECORATION_OVERLINE = 0x2,
  IPL_TEXT_DECORATION_LINE_THROUGH = 0x4,
} ipl_text_decoration_t;

// txt::TextDecorationStyle
typedef enum ipl_text_decoration_style : unsigned int {
  IPL_DECORATION_STYLE_SOLID = 0,
  IPL_DECORATION_STYLE_DOUBLE = 1,
  IPL_DECORATION_STYLE_DOTTED = 2,
  IPL_DECORATION_STYLE_DASHED = 3,
  IPL_DECORATION_STYLE_WAVY = 4,
} ipl_text_decoration_style_t;

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/txt/src/txt/text_decoration.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/txt/src/txt/text_baseline.h
// ---------------------------------------------------------------------------

// txt::TextBaseline
typedef enum ipl_text_baseline : unsigned int {
  IPL_TEXT_BASELINE_ALPHABETIC = 0,
  IPL_TEXT_BASELINE_IDEOGRAPHIC = 1,
} ipl_text_baseline_t;

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/txt/src/txt/text_baseline.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/txt/src/txt/text_shadow.h
// ---------------------------------------------------------------------------

#if defined(__i386__) || defined(__arm__) || defined(_M_IX86)
// txt::TextShadow
typedef struct ipl_text_shadow {
  alignas(8) char data[24];
} ipl_text_shadow_t;
#else
// txt::TextShadow
typedef struct ipl_text_shadow {
  alignas(8) char data[24];
} ipl_text_shadow_t;
#endif

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/txt/src/txt/text_shadow.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/txt/src/txt/font_features.h
// ---------------------------------------------------------------------------

typedef struct ipl_font_features* ipl_font_features_t;

typedef struct ipl_font_variations* ipl_font_variations_t;

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/txt/src/txt/font_features.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/txt/src/txt/placeholder_run.h
// ---------------------------------------------------------------------------

// txt::PlaceholderAlignment
typedef enum ipl_placeholder_alignment : int {
  IPL_PLACEHOLDER_ALIGNMENT_BASELINE = 0,
  IPL_PLACEHOLDER_ALIGNMENT_ABOVE_BASELINE = 1,
  IPL_PLACEHOLDER_ALIGNMENT_BELOW_BASELINE = 2,
  IPL_PLACEHOLDER_ALIGNMENT_TOP = 3,
  IPL_PLACEHOLDER_ALIGNMENT_BOTTOM = 4,
  IPL_PLACEHOLDER_ALIGNMENT_MIDDLE = 5,
} ipl_placeholder_alignment_t;

// txt::PlaceholderRun
typedef struct ipl_placehoder_run {
  double width;
  double height;
  ipl_placeholder_alignment_t alignment;
  ipl_text_baseline_t baseline;
  double baseline_offset;
} ipl_placehoder_run_t;

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/txt/src/txt/placeholder_run.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/txt/src/txt/text_style.h
// ---------------------------------------------------------------------------

#if defined(__i386__) || defined(__arm__) || defined(_M_IX86)
// txt::TextStyle
typedef struct ipl_text_style {
  alignas(8) char data[280];
} ipl_text_style_t;
#else
// txt::TextStyle
typedef struct ipl_text_style {
  alignas(8) char data[408];
} ipl_text_style_t;
#endif

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/txt/src/txt/text_style.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/txt/src/txt/font_collection.h
// ---------------------------------------------------------------------------

#if defined(__i386__) || defined(__arm__) || defined(_M_IX86)
// std::shared_ptr<txt::FontCollection>
typedef struct ipl_font_collection {
  alignas(4) char data[8];
} ipl_font_collection_t;
#else
// std::shared_ptr<txt::FontCollection>
typedef struct ipl_font_collection {
  alignas(8) char data[16];
} ipl_font_collection_t;
#endif

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/txt/src/txt/font_collection.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/txt/src/txt/paragraph.h
// ---------------------------------------------------------------------------

#if defined(__i386__) || defined(__arm__) || defined(_M_IX86)
// std::unique_ptr<txt::Paragraph>
typedef struct ipl_paragraph {
  alignas(4) char data[4];
} ipl_paragraph_t;
#else
// std::unique_ptr<txt::Paragraph>
typedef struct ipl_paragraph {
  alignas(8) char data[8];
} ipl_paragraph_t;
#endif

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/txt/src/txt/paragraph.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/txt/src/skia/paragraph_builder_skia.h
// ---------------------------------------------------------------------------

#if defined(__i386__) || defined(__arm__) || defined(_M_IX86)
// std::unique_ptr<txt::ParagraphBuilderSkia>
typedef struct ipl_paragraph_builder {
  alignas(4) char data[4];
} ipl_paragraph_builder_t;
#else
// std::unique_ptr<txt::ParagraphBuilderSkia>
typedef struct ipl_paragraph_builder {
  alignas(8) char data[8];
} ipl_paragraph_builder_t;
#endif

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/txt/src/skia/paragraph_builder_skia.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/impeller/typographer/typographer_context.h
// ---------------------------------------------------------------------------

#if defined(__i386__) || defined(__arm__) || defined(_M_IX86)
// std::shared_ptr<impeller::TypographerContext>
typedef struct ipl_typographer_context {
  alignas(4) char data[8];
} ipl_typographer_context_t;
#else
// std::shared_ptr<impeller::TypographerContext>
typedef struct ipl_typographer_context {
  alignas(8) char data[16];
} ipl_typographer_context_t;
#endif

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/impeller/typographer/typographer_context.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/impeller/renderer/context.h
// ---------------------------------------------------------------------------

#if defined(__i386__) || defined(__arm__) || defined(_M_IX86)
// std::shared_ptr<impeller::Context>
typedef struct ipl_context {
  alignas(4) char data[8];
} ipl_context_t;
#else
// std::shared_ptr<impeller::Context>
typedef struct ipl_context {
  alignas(8) char data[16];
} ipl_context_t;
#endif

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/impeller/renderer/context.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/impeller/renderer/surface.h
// ---------------------------------------------------------------------------

#if defined(__i386__) || defined(__arm__) || defined(_M_IX86)
// std::unique_ptr<impeller::Surface>
typedef struct ipl_surface {
  alignas(4) char data[4];
} ipl_surface_t;
#else
// std::unique_ptr<impeller::Surface>
typedef struct ipl_surface {
  alignas(8) char data[8];
} ipl_surface_t;
#endif

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/impeller/renderer/surface.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/impeller/renderer/backend/vulkan/context_vk.h
// ---------------------------------------------------------------------------

#if defined(__i386__) || defined(__arm__) || defined(_M_IX86)
// std::shared_ptr<impeller::ContextVK>
typedef struct ipl_vk_context {
  alignas(4) char data[8];
} ipl_vk_context_t;

// impeller::ContextVK::Settings
typedef struct ipl_vk_context_settings {
  alignas(8) char data[144];
} ipl_vk_context_settings_t;
#else
// std::shared_ptr<impeller::ContextVK>
typedef struct ipl_vk_context {
  alignas(8) char data[16];
} ipl_vk_context_t;

// impeller::ContextVK::Settings
typedef struct ipl_vk_context_settings {
  alignas(8) char data[144];
} ipl_vk_context_settings_t;
#endif

typedef struct VkInstance_T* VkInstance;
typedef struct VkPhysicalDevice_T* VkPhysicalDevice;
typedef struct VkDevice_T* VkDevice;
typedef struct VkQueue_T* VkQueue;

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/impeller/renderer/backend/vulkan/context_vk.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN]
// engine/src/flutter/impeller/renderer/backend/vulkan/swapchain/swapchain_vk.h
// ---------------------------------------------------------------------------

#if defined(__i386__) || defined(__arm__) || defined(_M_IX86)
// std::shared_ptr<impeller::SwapchainVK>
typedef struct ipl_vk_swapchain {
  alignas(4) char data[8];
} ipl_vk_swapchain_t;

typedef struct uint64_t VkSurfaceKHR;
#else
// std::shared_ptr<impeller::SwapchainVK>
typedef struct ipl_vk_swapchain {
  alignas(8) char data[16];
} ipl_vk_swapchain_t;

typedef struct VkSurfaceKHR_T* VkSurfaceKHR;
#endif

// ---------------------------------------------------------------------------
// [END]
// engine/src/flutter/impeller/renderer/backend/vulkan/swapchain/swapchain_vk.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/impeller/renderer/render_target.h
// ---------------------------------------------------------------------------

// impeller::RenderTarget *
typedef struct ipl_render_target* ipl_render_target_t;
// const impeller::RenderTarget *
typedef const struct ipl_render_target* ipl_const_render_target_t;

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/impeller/renderer/render_target.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/impeller/entity/contents/content_context.h
// ---------------------------------------------------------------------------

#if defined(__i386__) || defined(__arm__) || defined(_M_IX86)
// std::unique_ptr<impeller::ContentContext>
typedef struct ipl_content_context {
  alignas(4) char data[4];
} ipl_content_context_t;
#else
// std::unique_ptr<impeller::ContentContext>
typedef struct ipl_content_context {
  alignas(8) char data[8];
} ipl_content_context_t;
#endif

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/impeller/entity/contents/content_context.h
// ---------------------------------------------------------------------------

// ===========================================================================
// [BEGIN] Function Declaration
// ===========================================================================

#ifdef __cplusplus
extern "C" {
#endif

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/impeller/core/allocator.h
// ---------------------------------------------------------------------------

// std::shared_ptr<impeller::Allocator> destructor
void ipl_allocator_drop(ipl_allocator_t* self);

// std::shared_ptr<impeller::Allocator> copy constructor
void ipl_allocator_clone(const ipl_allocator_t* self, ipl_allocator_t* out);

// impeller::Allocator::CreateBuffer
bool ipl_allocator_create_buffer(const ipl_allocator_t* self,
                                 const ipl_device_buffer_descriptor_t* desc,
                                 ipl_device_buffer_t* out);

// impeller::Allocator::CreateTexture
bool ipl_allocator_create_texture(const ipl_allocator_t* self,
                                  const ipl_texture_descriptor_t* desc,
                                  bool threadsafe,
                                  ipl_texture_t* out);

// impeller::Allocator::MinimumBytesPerRow
uint16_t ipl_allocator_minimum_bytes_per_row(const ipl_allocator_t* self,
                                             ipl_pixel_format_t format);

// impeller::Allocator::CreateBufferWithCopy
bool ipl_allocator_create_buffer_with_copy(const ipl_allocator_t* self,
                                           const uint8_t* buffer,
                                           size_t length,
                                           ipl_device_buffer_t* out);

// impeller::Allocator::GetMaxTextureSizeSupported
void ipl_allocator_get_max_texture_size_supported(const ipl_allocator_t* self,
                                                  ipl_i64_size_t* out);

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/impeller/core/allocator.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/impeller/core/buffer_view.h
// ---------------------------------------------------------------------------

void ipl_buffer_view_drop(ipl_buffer_view_t* out);

void ipl_buffer_view_get_range(const ipl_buffer_view_t* self, ipl_range_t* out);

// impeller::BufferView::TakeBuffer
bool ipl_buffer_view_take_buffer(ipl_buffer_view_t* self,
                                 ipl_const_device_buffer_t* out);

const ipl_device_buffer_descriptor_t*
ipl_buffer_view_get_device_buffer_descriptor(const ipl_buffer_view_t* self);

uint8_t* ipl_buffer_view_on_get_contents(const ipl_buffer_view_t* self);

void ipl_buffer_view_flush(const ipl_buffer_view_t* self,
                           const ipl_range_t* range);

void ipl_buffer_view_invalidate(const ipl_buffer_view_t* self,
                                const ipl_range_t* range);

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/impeller/core/buffer_view.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/impeller/core/device_buffer.h
// ---------------------------------------------------------------------------

bool ipl_device_buffer_copy_host_buffer(const ipl_device_buffer_t* self,
                                        const uint8_t* source,
                                        const ipl_range_t* source_range,
                                        size_t offset);

bool ipl_device_buffer_set_label(const ipl_device_buffer_t* self,
                                 const char* ptr,
                                 size_t len);

void ipl_device_buffer_as_buffer_view(const ipl_device_buffer_t* self,
                                      ipl_buffer_view_t* out);

const ipl_device_buffer_descriptor_t*
ipl_device_buffer_get_device_buffer_descriptor(const ipl_device_buffer_t* self);

uint8_t* ipl_device_buffer_on_get_contents(const ipl_device_buffer_t* self);

void ipl_device_buffer_flush(const ipl_device_buffer_t* self,
                             const ipl_range_t* range);

void ipl_device_buffer_invalidate(const ipl_device_buffer_t* self,
                                  const ipl_range_t* range);

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/impeller/core/device_buffer.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/impeller/core/host_buffer.h
// ---------------------------------------------------------------------------

void ipl_host_buffer_drop(ipl_host_buffer_t* self);

bool ipl_host_buffer_emplace(const ipl_host_buffer_t* self,
                             const void* buffer,
                             size_t length,
                             size_t align,
                             ipl_buffer_view_t* out);

size_t ipl_host_buffer_get_minimum_uniform_alignment(
    const ipl_host_buffer_t* self);

void ipl_host_buffer_reset(const ipl_host_buffer_t* self);

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/impeller/core/host_buffer.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/impeller/core/texture.h
// ---------------------------------------------------------------------------

void ipl_texture_drop(ipl_texture_t* self);

void ipl_texture_clone(const ipl_texture_t* self, ipl_texture_t* out);

void ipl_texture_set_label(const ipl_texture_t* self,
                           const char* ptr,
                           size_t len);

void ipl_texture_get_size(const ipl_texture_t* self, ipl_i64_size_t* out);

bool ipl_texture_is_opaque(const ipl_texture_t* self);

size_t ipl_texture_get_mip_count(const ipl_texture_t* self);

const ipl_texture_descriptor_t* ipl_texture_get_texture_descriptor(
    const ipl_texture_t* self);

bool ipl_texture_needs_mipmap_generation(const ipl_texture_t* self);

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/impeller/core/texture.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/display_list/dl_color.h
// ---------------------------------------------------------------------------

void ipl_color_new(float alpha,
                   float red,
                   float green,
                   float blue,
                   ipl_color_space_t color_space,
                   ipl_color_t* out);

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/display_list/dl_color.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/display_list/effects/dl_color_filter.h
// ---------------------------------------------------------------------------

bool ipl_color_filter_new_blend(const ipl_color_t* color,
                                ipl_blend_mode_t mode,
                                ipl_const_color_filter_t* out);

bool ipl_color_filter_new_matrix(const float matrix[20],
                                 ipl_const_color_filter_t* out);

void ipl_color_filter_new_srgb_to_linear_gamma(ipl_const_color_filter_t* out);

void ipl_color_filter_new_linear_to_srgb_gamma(ipl_const_color_filter_t* out);

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/display_list/effects/dl_color_filter.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/display_list/effects/dl_color_source.h
// ---------------------------------------------------------------------------

void ipl_color_source_drop(ipl_color_source_t* self);

bool ipl_color_source_new_image(const ipl_const_image_t* image,
                                ipl_tile_mode_t horizontal_tile_mode,
                                ipl_tile_mode_t vertical_tile_mode,
                                ipl_image_sampling_t sampling,
                                const ipl_matrix_t* matrix,
                                ipl_color_source_t* out);

bool ipl_color_source_new_linear(const ipl_f32_point_t* start_point,
                                 const ipl_f32_point_t* end_point,
                                 uint32_t stop_count,
                                 const ipl_color_t* colors,
                                 const float* stops,
                                 ipl_tile_mode_t tile_mode,
                                 const ipl_matrix_t* matrix,
                                 ipl_color_source_t* out);

bool ipl_color_source_new_radial(const ipl_f32_point_t* center,
                                 float radius,
                                 uint32_t stop_count,
                                 const ipl_color_t* colors,
                                 const float* stops,
                                 ipl_tile_mode_t tile_mode,
                                 const ipl_matrix_t* matrix,
                                 ipl_color_source_t* out);

bool ipl_color_source_new_conical(const ipl_f32_point_t* start_center,
                                  float start_radius,
                                  const ipl_f32_point_t* end_center,
                                  float end_radius,
                                  uint32_t stop_count,
                                  const ipl_color_t* colors,
                                  const float* stops,
                                  ipl_tile_mode_t tile_mode,
                                  const ipl_matrix_t* matrix,
                                  ipl_color_source_t* out);

bool ipl_color_source_new_sweep(const ipl_f32_point_t* center,
                                float start,
                                float end,
                                uint32_t stop_count,
                                const ipl_color_t* colors,
                                const float* stops,
                                ipl_tile_mode_t tile_mode,
                                const ipl_matrix_t* matrix,
                                ipl_color_source_t* out);

// flutter::DlColorSource::MakeRuntimeEffect

bool ipl_color_source_is_opaque(const ipl_color_source_t* self);

void ipl_const_color_source_drop(ipl_const_color_source_t* self);

bool ipl_const_color_source_is_opaque(const ipl_const_color_source_t* self);

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/display_list/effects/dl_color_source.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/display_list/effects/dl_image_filter.h
// ---------------------------------------------------------------------------

void ipl_image_filter_drop(ipl_image_filter_t* self);

bool ipl_image_filter_new_blur(float sigma_x,
                               float sigma_y,
                               ipl_tile_mode_t tile_mode,
                               ipl_image_filter_t* out);

bool ipl_image_filter_new_dilate(float radius_x,
                                 float radius_y,
                                 ipl_image_filter_t* out);

bool ipl_image_filter_new_erode(float radius_x,
                                float radius_y,
                                ipl_image_filter_t* out);

bool ipl_image_filter_new_matrix(const ipl_matrix_t* matrix,
                                 ipl_image_sampling_t sampling,
                                 ipl_image_filter_t* out);

// flutter::DlImageFilter::MakeRuntimeEffect

bool ipl_image_filter_new_color_filter(const ipl_const_color_filter_t* filter,
                                       ipl_image_filter_t* out);

bool ipl_image_filter_new_compose(const ipl_image_filter_t* outer,
                                  const ipl_image_filter_t* inner,
                                  ipl_image_filter_t* out);

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/display_list/effects/dl_image_filter.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/display_list/effects/dl_mask_filter.h
// ---------------------------------------------------------------------------

void ipl_mask_filter_drop(ipl_mask_filter_t* self);

bool ipl_mask_filter_new_blur(ipl_blur_style_t style,
                              float sigma,
                              bool respect_ctm,
                              ipl_mask_filter_t* out);

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/display_list/effects/dl_mask_filter.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/display_list/image/dl_image.h
// ---------------------------------------------------------------------------

void ipl_image_drop(ipl_image_t* self);

bool ipl_image_new(const ipl_texture_t* texture, ipl_image_t* out);

// DlImageImpeller::GetImpellerTexture

ipl_color_space_t ipl_image_get_color_space(const ipl_image_t* self);

bool ipl_image_is_opaque(const ipl_image_t* self);

void ipl_image_get_size(const ipl_image_t* self, ipl_i64_size_t* out);

size_t ipl_image_get_approximate_byte_size(const ipl_image_t* self);

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/display_list/image/dl_image.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/display_list/dl_paint.h
// ---------------------------------------------------------------------------

void ipl_paint_drop(ipl_paint_t* self);

void ipl_paint_new(const ipl_color_t* color, ipl_paint_t* out);

bool ipl_paint_is_anti_alias(const ipl_paint_t* self);

void ipl_paint_set_anti_alias(ipl_paint_t* self, bool is_anti_alias);

bool ipl_paint_is_invert_colors(const ipl_paint_t* self);

void ipl_paint_set_invert_colors(ipl_paint_t* self, bool is_invert_colors);

void ipl_paint_get_color(const ipl_paint_t* self, ipl_color_t* out);

void ipl_paint_set_color(ipl_paint_t* self, const ipl_color_t* color);

uint8_t ipl_paint_get_alpha(const ipl_paint_t* self);

void ipl_paint_set_alpha(ipl_paint_t* self, uint8_t alpha);

float ipl_paint_get_opacity(const ipl_paint_t* self);

void ipl_paint_set_opacity(ipl_paint_t* self, float opacity);

ipl_blend_mode_t ipl_paint_get_blend_mode(const ipl_paint_t* self);

void ipl_paint_set_blend_mode(ipl_paint_t* self, ipl_blend_mode_t mode);

ipl_draw_style_t ipl_paint_get_draw_style(const ipl_paint_t* self);

void ipl_paint_set_draw_style(ipl_paint_t* self, ipl_draw_style_t style);

ipl_stroke_cap_t ipl_paint_get_stroke_cap(const ipl_paint_t* self);

void ipl_paint_set_stroke_cap(ipl_paint_t* self, ipl_stroke_cap_t cap);

ipl_stroke_join_t ipl_paint_get_stroke_join(const ipl_paint_t* self);

void ipl_paint_set_stroke_join(ipl_paint_t* self, ipl_stroke_join_t join);

float ipl_paint_get_stroke_width(const ipl_paint_t* self);

void ipl_paint_set_stroke_width(ipl_paint_t* self, float width);

float ipl_paint_get_stroke_miter(const ipl_paint_t* self);

void ipl_paint_set_stroke_miter(ipl_paint_t* self, float miter);

const ipl_const_color_source_t* ipl_paint_get_color_source(
    const ipl_paint_t* self);

void ipl_paint_set_color_source(ipl_paint_t* self,
                                const ipl_const_color_source_t* source);

const ipl_const_color_filter_t* ipl_paint_get_color_filter(
    const ipl_paint_t* self);

void ipl_paint_set_color_filter(ipl_paint_t* self,
                                const ipl_const_color_filter_t* filter);

const ipl_image_filter_t* ipl_paint_get_image_filter(const ipl_paint_t* self);

void ipl_paint_set_image_filter(ipl_paint_t* self,
                                const ipl_image_filter_t* filter);

const ipl_const_mask_filter_t* ipl_paint_get_mask_filter(
    const ipl_paint_t* self);

void ipl_paint_set_mask_filter(ipl_paint_t* self,
                               const ipl_mask_filter_t* filter);

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/display_list/dl_paint.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/display_list/dl_path.h
// ---------------------------------------------------------------------------

void ipl_path_drop(ipl_path_t* self);

void ipl_path_new_rec(const ipl_f32_rect_t* rect, ipl_path_t* out);

void ipl_path_new_rec(const ipl_f32_rect_t* rect, ipl_path_t* out);

void ipl_path_new_rect_ltrb(float left,
                            float top,
                            float right,
                            float bottom,
                            ipl_path_t* out);

void ipl_path_new_rect_xywh(float x,
                            float y,
                            float width,
                            float height,
                            ipl_path_t* out);

void ipl_path_new_oval(const ipl_f32_rect_t* bounds, ipl_path_t* out);

void ipl_path_new_oval_ltrb(float left,
                            float top,
                            float right,
                            float bottom,
                            ipl_path_t* out);

void ipl_path_new_circle(const ipl_f32_point_t* center,
                         float radius,
                         ipl_path_t* out);

void ipl_path_new_round_rect(const ipl_round_rect_t* rrect, ipl_path_t* out);

void ipl_path_new_round_rect_xy(const ipl_f32_rect_t* rect,
                                float x_radius,
                                float y_radius,
                                bool counter_clock_wise,
                                ipl_path_t* out);

// flutter::DlPath::MakeRoundSuperellipse

void ipl_path_new_line(const ipl_f32_point_t* a,
                       const ipl_f32_point_t* b,
                       ipl_path_t* out);

void ipl_path_new_poly(const ipl_f32_point_t* pts,
                       int count,
                       bool close,
                       ipl_path_fill_type_t fill_type,
                       ipl_path_t* out);

void ipl_path_new_arc(const ipl_f32_rect_t* bounds,
                      float start,
                      float sweep,
                      bool use_center,
                      ipl_path_t* out);

void ipl_path_with_offset(const ipl_path_t* self,
                          const ipl_f32_point_t* offset,
                          ipl_path_t* out);

void ipl_path_with_fill_type(const ipl_path_t* self,
                             ipl_path_fill_type_t type,
                             ipl_path_t* out);

bool ipl_path_is_empty(const ipl_path_t* self);

bool ipl_path_is_rect(const ipl_path_t* self,
                      ipl_f32_rect_t* rect,
                      bool* is_closed);

bool ipl_path_is_oval(const ipl_path_t* self, ipl_f32_rect_t* bounds);

bool ipl_path_is_line(const ipl_path_t* self,
                      ipl_f32_point_t* start,
                      ipl_f32_point_t* end);

bool ipl_path_is_round_rect(const ipl_path_t* self, ipl_round_rect_t* rrect);

bool ipl_path_contains(const ipl_path_t* self, const ipl_f32_point_t* point);

void ipl_path_get_bounds(const ipl_path_t* self, ipl_f32_rect_t* out);

ipl_path_fill_type_t ipl_path_get_fill_type(const ipl_path_t* self);

bool ipl_path_operator_equal(const ipl_path_t* self, const ipl_path_t* other);

bool ipl_path_is_volatile(const ipl_path_t* self);

bool ipl_path_is_convex(const ipl_path_t* self);

void ipl_path_operator_add(const ipl_path_t* self,
                           const ipl_path_t* other,
                           ipl_path_t* out);

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/display_list/dl_path.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/display_list/dl_text.h
// ---------------------------------------------------------------------------

void ipl_text_drop(ipl_text_t* self);

void ipl_text_get_bounds(const ipl_text_t* self, ipl_f32_rect_t* out);

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/display_list/dl_text.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/display_list/display_list.h
// ---------------------------------------------------------------------------

void ipl_display_list_drop(ipl_display_list_t* self);

void ipl_display_list_get_bounds(const ipl_display_list_t* self,
                                 ipl_f32_rect_t* out);

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/display_list/display_list.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/display_list/dl_path_builder.h
// ---------------------------------------------------------------------------

void ipl_path_builder_drop(ipl_path_builder_t* self);

ipl_path_builder_t* ipl_path_bulder_set_fill_type(
    ipl_path_builder_t* self,
    ipl_path_fill_type_t fill_type);

ipl_path_builder_t* ipl_path_builder_move_to(ipl_path_builder_t* self,
                                             const ipl_f32_point_t* p2);

ipl_path_builder_t* ipl_path_builder_line_to(ipl_path_builder_t* self,
                                             const ipl_f32_point_t* p2);

ipl_path_builder_t* ipl_path_builder_quadratic_curve_to(
    ipl_path_builder_t* self,
    const ipl_f32_point_t* cp,
    const ipl_f32_point_t* p2);

ipl_path_builder_t* ipl_path_builder_conic_curve_to(ipl_path_builder_t* self,
                                                    const ipl_f32_point_t* cp,
                                                    const ipl_f32_point_t* p2,
                                                    float weight);

ipl_path_builder_t* ipl_path_builder_cubic_curve_to(ipl_path_builder_t* self,
                                                    const ipl_f32_point_t* cp1,
                                                    const ipl_f32_point_t* cp2,
                                                    const ipl_f32_point_t* p2);

ipl_path_builder_t* ipl_path_builder_close(ipl_path_builder_t* self);

ipl_path_builder_t* ipl_path_builder_add_rect(ipl_path_builder_t* self,
                                              const ipl_f32_rect_t* rect);

ipl_path_builder_t* ipl_path_builder_add_oval(ipl_path_builder_t* self,
                                              const ipl_f32_rect_t* bounds);

ipl_path_builder_t* ipl_path_builder_add_circle(ipl_path_builder_t* self,
                                                const ipl_f32_point_t* center,
                                                float radius);

ipl_path_builder_t* ipl_path_builder_add_round_rect(
    ipl_path_builder_t* self,
    const ipl_round_rect_t* round_rect);

// flutter::DlPathBuilder::AddRoundSuperellipse

ipl_path_builder_t* ipl_path_builder_add_arc(ipl_path_builder_t* self,
                                             const ipl_f32_rect_t* bounds,
                                             float start,
                                             float sweep,
                                             bool use_center);

ipl_path_builder_t* ipl_path_builder_add_path(ipl_path_builder_t* self,
                                              const ipl_path_t* path);

void ipl_path_builder_copy_path(ipl_path_builder_t* self, ipl_path_t* out);

void ipl_path_builder_take_path(ipl_path_builder_t* self, ipl_path_t* out);

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/display_list/dl_path_builder.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/display_list/dl_builder.h
// ---------------------------------------------------------------------------

void ipl_display_list_builder_drop(ipl_display_list_builder_t* self);

void ipl_display_list_builder_new(const ipl_f32_rect_t* cull_rect,
                                  bool prepare_rtree,
                                  ipl_display_list_builder_t* out);

void ipl_display_list_builder_get_base_layer_dimensions(
    const ipl_display_list_builder_t* self,
    ipl_i64_size_t* out);

// flutter::DisplayListBuilder::GetRecordCount
size_t ipl_display_list_builder_get_record_count(
    const ipl_display_list_builder_t* self);

// flutter::DisplayListBuilder::IsEmpty
bool ipl_display_list_builder_is_empty(const ipl_display_list_builder_t* self);

// flutter::DisplayListBuilder::Save
void ipl_display_list_builder_save(const ipl_display_list_builder_t* self);

void ipl_display_list_builder_save_layer(const ipl_display_list_builder_t* self,
                                         const ipl_f32_rect_t* bounds,
                                         const ipl_paint_t* paint,
                                         const ipl_image_filter_t* backdrop,
                                         const int64_t* backdrop_id);

// flutter::DisplayListBuilder::Restore
void ipl_display_list_builder_restore(const ipl_display_list_builder_t* self);

// flutter::DisplayListBuilder::GetSaveCount
int ipl_display_list_builder_get_save_count(
    const ipl_display_list_builder_t* self);

// flutter::DisplayListBuilder::RestoreToCount
void ipl_display_list_builder_restore_to_count(
    const ipl_display_list_builder_t* self,
    int restore_count);

// flutter::DisplayListBuilder::Translate
void ipl_display_list_builder_translate(const ipl_display_list_builder_t* self,
                                        float tx,
                                        float ty);

// flutter::DisplayListBuilder::Scale
void ipl_display_list_builder_scale(const ipl_display_list_builder_t* self,
                                    float sx,
                                    float sy);

// flutter::DisplayListBuilder::Rotate
void ipl_display_list_builder_rotate(const ipl_display_list_builder_t* self,
                                     float degrees);

// flutter::DisplayListBuilder::Skew
void ipl_display_list_builder_skew(const ipl_display_list_builder_t* self,
                                   float sx,
                                   float sy);

// flutter::DisplayListBuilder::Transform2DAffine
void ipl_display_list_builder_transform_2d_affine(
    const ipl_display_list_builder_t* self,
    float mxx,
    float mxy,
    float mxt,
    float myx,
    float myy,
    float myt);

// flutter::DisplayListBuilder::TransformFullPerspective
void ipl_display_list_builder_transform_full_perspective(
    const ipl_display_list_builder_t* self,
    float mxx,
    float mxy,
    float mxz,
    float mxt,
    float myx,
    float myy,
    float myz,
    float myt,
    float mzx,
    float mzy,
    float mzz,
    float mzt,
    float mwx,
    float mwy,
    float mwz,
    float mwt);

// flutter::DisplayListBuilder::TransformReset
void ipl_display_list_builder_transform_reset(
    const ipl_display_list_builder_t* self);

// flutter::DisplayListBuilder::Transform
void ipl_display_list_builder_transform(const ipl_display_list_builder_t* self,
                                        const ipl_matrix_t* matrix);

// flutter::DisplayListBuilder::SetTransform
void ipl_display_list_builder_set_transform(
    const ipl_display_list_builder_t* self,
    const ipl_matrix_t* matrix);

// flutter::DisplayListBuilder::GetMatrix
void ipl_display_list_builder_get_matrix(const ipl_display_list_builder_t* self,
                                         ipl_matrix_t* out);

void ipl_display_list_builder_clip_rect(const ipl_display_list_builder_t* self,
                                        const ipl_f32_rect_t* rect,
                                        ipl_clip_op_t clip_op,
                                        bool is_aa);

void ipl_display_list_builder_clip_oval(const ipl_display_list_builder_t* self,
                                        const ipl_f32_rect_t* bounds,
                                        ipl_clip_op_t clip_op,
                                        bool is_aa);

void ipl_display_list_builder_clip_round_rect(
    const ipl_display_list_builder_t* self,
    const ipl_round_rect_t* rrect,
    ipl_clip_op_t clip_op,
    bool is_aa);

// DisplayListBuilder::ClipRoundSuperellipse

void ipl_display_list_builder_clip_path(const ipl_display_list_builder_t* self,
                                        const ipl_path_t* path,
                                        ipl_clip_op_t clip_op,
                                        bool is_aa);

void ipl_display_list_builder_get_destination_clip_coverage(
    const ipl_display_list_builder_t* self,
    ipl_f32_rect_t* out);

void ipl_display_list_builder_get_local_clip_coverage(
    const ipl_display_list_builder_t* self,
    ipl_f32_rect_t* out);

bool ipl_display_list_builder_quick_reject(
    const ipl_display_list_builder_t* self,
    const ipl_f32_rect_t* bounds);

// flutter::DisplayListBuilder::DrawPaint
void ipl_display_list_builder_draw_paint(const ipl_display_list_builder_t* self,
                                         const ipl_paint_t* paint);

// flutter::DisplayListBuilder::DrawColor
void ipl_display_list_builder_draw_color(const ipl_display_list_builder_t* self,
                                         const ipl_color_t* color,
                                         ipl_blend_mode_t mode);

// flutter::DisplayListBuilder::DrawLine
void ipl_display_list_builder_draw_line(const ipl_display_list_builder_t* self,
                                        const ipl_f32_point_t* p0,
                                        const ipl_f32_point_t* p1,
                                        const ipl_paint_t* paint);

// flutter::DisplayListBuilder::DrawDashedLine
void ipl_display_list_builder_draw_dashed_line(
    const ipl_display_list_builder_t* self,
    const ipl_f32_point_t* p0,
    const ipl_f32_point_t* p1,
    float on_length,
    float off_length,
    const ipl_paint_t* paint);

// flutter::DisplayListBuilder::DrawRect
void ipl_display_list_builder_draw_rect(const ipl_display_list_builder_t* self,
                                        const ipl_f32_rect_t* rect,
                                        const ipl_paint_t* paint);

// flutter::DisplayListBuilder::DrawOval
void ipl_display_list_builder_draw_oval(const ipl_display_list_builder_t* self,
                                        const ipl_f32_rect_t* bounds,
                                        const ipl_paint_t* paint);

// flutter::DisplayListBuilder::DrawCircle
void ipl_display_list_builder_draw_circle(
    const ipl_display_list_builder_t* self,
    const ipl_f32_point_t* center,
    float radius,
    const ipl_paint_t* paint);

// flutter::DisplayListBuilder::DrawRoundRect
void ipl_display_list_builder_draw_round_rect(
    const ipl_display_list_builder_t* self,
    const ipl_round_rect_t* rrect,
    const ipl_paint_t* paint);

// flutter::DisplayListBuilder::DrawDiffRoundRect
void ipl_display_list_builder_draw_diff_round_rect(
    const ipl_display_list_builder_t* self,
    const ipl_round_rect_t* outer,
    const ipl_round_rect_t* inner,
    const ipl_paint_t* paint);

// flutter::DisplayListBuilder::DrawRoundSuperellipse

// flutter::DisplayListBuilder::DrawPath
void ipl_display_list_builder_draw_path(const ipl_display_list_builder_t* self,
                                        const ipl_path_t* path,
                                        const ipl_paint_t* paint);

// flutter::DisplayListBuilder::DrawArc
void ipl_display_list_builder_draw_arc(const ipl_display_list_builder_t* self,
                                       const ipl_f32_rect_t* bounds,
                                       float start,
                                       float sweep,
                                       bool use_center,
                                       const ipl_paint_t* paint);

// flutter::DisplayListBuilder::DrawPoints
void ipl_display_list_builder_draw_points(
    const ipl_display_list_builder_t* self,
    ipl_point_mode_t mode,
    uint32_t count,
    const ipl_f32_point_t pts[],
    const ipl_paint_t* paint);

// flutter::DisplayListBuilder::DrawVertices

// flutter::DisplayListBuilder::DrawImage
void ipl_display_list_builder_draw_image(const ipl_display_list_builder_t* self,
                                         const ipl_image_t* image,
                                         const ipl_f32_point_t* point,
                                         ipl_image_sampling_t sampling,
                                         const ipl_paint_t* paint);

// flutter::DisplayListBuilder::DrawImageRect
void ipl_display_list_builder_draw_image_rect(
    const ipl_display_list_builder_t* self,
    const ipl_image_t* image,
    const ipl_f32_rect_t* src,
    const ipl_f32_rect_t* dst,
    ipl_image_sampling_t sampling,
    const ipl_paint_t* paint,
    ipl_src_rect_constraint_t constraint);

// flutter::DisplayListBuilder::DrawImageNine
void ipl_display_list_builder_draw_image_nine(
    const ipl_display_list_builder_t* self,
    const ipl_image_t* image,
    const ipl_i32_rect_t* center,
    const ipl_f32_rect_t* dst,
    ipl_filter_mode_t filter,
    const ipl_paint_t* paint);

// flutter::DisplayListBuilder::DrawAtlas
void ipl_display_list_builder_draw_atlas(const ipl_display_list_builder_t* self,
                                         const ipl_image_t* atlas,
                                         const ipl_rs_transform_t xform[],
                                         const ipl_f32_rect_t tex[],
                                         const ipl_color_t colors[],
                                         int count,
                                         ipl_blend_mode_t mode,
                                         ipl_image_sampling_t sampling,
                                         const ipl_f32_rect_t* cull_rect,
                                         const ipl_paint_t* paint);

// flutter::DisplayListBuilder::DrawDisplayList
void ipl_display_list_builder_draw_display_list(
    const ipl_display_list_builder_t* self,
    const ipl_display_list_t* display_list,
    float opacity);

// flutter::DisplayListBuilder::DrawText
void ipl_display_list_builder_draw_text(const ipl_display_list_builder_t* self,
                                        const ipl_text_t* text,
                                        float x,
                                        float y,
                                        const ipl_paint_t* paint);

// flutter::DisplayListBuilder::DrawShadow
void ipl_display_list_builder_draw_shadow(
    const ipl_display_list_builder_t* self,
    const ipl_path_t* path,
    const ipl_color_t* color,
    float elevation,
    bool transparent_occluder,
    float dpr);

// flutter::DisplayListBuilder::Flush
void ipl_display_list_builder_flush(const ipl_display_list_builder_t* self);

// flutter::DisplayListBuilder::Build
void ipl_display_list_builder_build(const ipl_display_list_builder_t* self,
                                    ipl_display_list_t* out);

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/display_list/dl_builder.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/txt/src/txt/paragraph_style.h
// ---------------------------------------------------------------------------

void ipl_paragraph_style_new(ipl_paragraph_style_t* out);

void ipl_paragraph_style_drop(ipl_paragraph_style_t* self);

void ipl_paragraph_style_set(ipl_paragraph_style_t* self, int font_weight);

int ipl_paragraph_style_get_font_weight(const ipl_paragraph_style_t* self);

void ipl_paragraph_style_set_font_weight(ipl_paragraph_style_t* self,
                                         int font_weight);

int ipl_paragraph_style_get_font_weight(const ipl_paragraph_style_t* self);

void ipl_paragraph_style_set_font_style(ipl_paragraph_style_t* self,
                                        ipl_font_style_t font_style);

ipl_font_style_t ipl_paragraph_style_get_font_style(
    const ipl_paragraph_style_t* self);

void ipl_paragraph_style_set_font_family(ipl_paragraph_style_t* self,
                                         const char* ptr,
                                         size_t len);

void ipl_paragraph_style_get_font_family(const ipl_paragraph_style_t* self,
                                         const char** ptr,
                                         size_t* len);

void ipl_paragraph_style_set_font_size(ipl_paragraph_style_t* self,
                                       double font_size);

double ipl_paragraph_style_get_font_size(const ipl_paragraph_style_t* self);

void ipl_paragraph_style_set_height(ipl_paragraph_style_t* self, double height);

double ipl_paragraph_style_get_height(const ipl_paragraph_style_t* self);

void ipl_paragraph_style_set_has_height_override(ipl_paragraph_style_t* self,
                                                 bool has_height_override);

bool ipl_paragraph_style_get_has_height_override(
    const ipl_paragraph_style_t* self);

void ipl_paragraph_style_set_text_height_behavior(
    ipl_paragraph_style_t* self,
    ipl_text_height_behavior_t text_height_behavior);

ipl_text_height_behavior_t ipl_paragraph_style_get_text_height_behavior(
    const ipl_paragraph_style_t* self);

void ipl_paragraph_style_set_strut_enabled(ipl_paragraph_style_t* self,
                                           bool strut_enabled);

bool ipl_paragraph_style_get_strut_enabled(const ipl_paragraph_style_t* self);

void ipl_paragraph_style_set_strut_font_weight(ipl_paragraph_style_t* self,
                                               int strut_font_weight);

int ipl_paragraph_style_get_strut_font_weight(
    const ipl_paragraph_style_t* self);

void ipl_paragraph_style_set_strut_font_style(
    ipl_paragraph_style_t* self,
    ipl_font_style_t strut_font_style);

ipl_font_style_t ipl_paragraph_style_get_strut_font_style(
    const ipl_paragraph_style_t* self);

void ipl_paragraph_style_set_strut_font_size(ipl_paragraph_style_t* self,
                                             double strut_font_size);

double ipl_paragraph_style_get_strut_font_size(
    const ipl_paragraph_style_t* self);

void ipl_paragraph_style_set_strut_height(ipl_paragraph_style_t* self,
                                          double strut_height);

double ipl_paragraph_style_get_strut_height(const ipl_paragraph_style_t* self);

void ipl_paragraph_style_set_strut_has_height_override(
    ipl_paragraph_style_t* self,
    bool strut_has_height_override);

bool ipl_paragraph_style_get_strut_has_height_override(
    const ipl_paragraph_style_t* self);

void ipl_paragraph_style_set_strut_half_leading(ipl_paragraph_style_t* self,
                                                bool strut_half_leading);

bool ipl_paragraph_style_get_strut_half_leading(
    const ipl_paragraph_style_t* self);

void ipl_paragraph_style_set_strut_leading(ipl_paragraph_style_t* self,
                                           double strut_leading);

double ipl_paragraph_style_get_strut_leading(const ipl_paragraph_style_t* self);

void ipl_paragraph_style_set_force_strut_height(ipl_paragraph_style_t* self,
                                                bool force_strut_height);

bool ipl_paragraph_style_get_force_strut_height(
    const ipl_paragraph_style_t* self);

void ipl_paragraph_style_set_text_align(ipl_paragraph_style_t* self,
                                        ipl_text_align_t text_align);

ipl_text_align_t ipl_paragraph_style_get_text_align(
    const ipl_paragraph_style_t* self);

void ipl_paragraph_style_set_text_direction(
    ipl_paragraph_style_t* self,
    ipl_text_direction_t text_direction);

ipl_text_direction_t ipl_paragraph_style_get_text_direction(
    const ipl_paragraph_style_t* self);

void ipl_paragraph_style_set_max_lines(ipl_paragraph_style_t* self,
                                       size_t max_lines);

size_t ipl_paragraph_style_get_max_lines(const ipl_paragraph_style_t* self);

void ipl_paragraph_style_set_ellipsis(ipl_paragraph_style_t* self,
                                      const char16_t* ptr,
                                      size_t len);

void ipl_paragraph_style_get_ellipsis(const ipl_paragraph_style_t* self,
                                      const char16_t** ptr,
                                      size_t* len);

void ipl_paragraph_style_set_locale(ipl_paragraph_style_t* self,
                                    const char* ptr,
                                    size_t len);

void ipl_paragraph_style_get_locale(const ipl_paragraph_style_t* self,
                                    const char** ptr,
                                    size_t* len);

void ipl_paragraph_style_get_text_style(const ipl_paragraph_style_t* self,
                                        ipl_text_style_t* out);

bool ipl_paragraph_style_unlimited_lines(const ipl_paragraph_style_t* self);

bool ipl_paragraph_style_ellipsized(const ipl_paragraph_style_t* self);

ipl_text_align_t ipl_paragraph_style_effective_align(
    const ipl_paragraph_style_t* self);

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/txt/src/txt/paragraph_style.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/txt/src/txt/text_shadow.h
// ---------------------------------------------------------------------------

void ipl_text_shadow_new(const ipl_color_t* color,
                         const ipl_f32_point_t* offset,
                         double blur_sigma,
                         ipl_text_shadow_t* out);

void ipl_text_shadow_drop(ipl_text_shadow_t* self);

void ipl_text_shadow_set(ipl_text_shadow_t* self, const ipl_color_t* color);

void ipl_text_shadow_get_color(const ipl_text_shadow_t* self, ipl_color_t* out);

void ipl_text_shadow_get_offset(const ipl_text_shadow_t* self,
                                ipl_f32_point_t* out);

void ipl_text_shadow_set_offset(ipl_text_shadow_t* self,
                                const ipl_f32_point_t* offset);

double ipl_text_shadow_get_blur_sigma(const ipl_text_shadow_t* self);

void ipl_text_shadow_set_blur_sigma(ipl_text_shadow_t* self, double blur_sigma);

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/txt/src/txt/text_shadow.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/txt/src/txt/font_features.h
// ---------------------------------------------------------------------------

void ipl_font_features_drop(ipl_font_features_t self);

void ipl_font_features_set_feature(ipl_font_features_t self,
                                   const char* ptr,
                                   size_t len,
                                   int value);

void ipl_font_variations_drop(ipl_font_variations_t self);

void ipl_font_variations_set_axis_value(ipl_font_variations_t self,
                                        const char* ptr,
                                        size_t len,
                                        float value);

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/txt/src/txt/font_features.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/txt/src/txt/text_style.h
// ---------------------------------------------------------------------------

void ipl_text_style_new(ipl_text_style_t* out);

void ipl_text_style_drop(ipl_text_style_t* self);

void ipl_text_style_set_color(ipl_text_style_t* self, const ipl_color_t* color);

void ipl_text_style_get_color(const ipl_text_style_t* self, ipl_color_t* out);

int ipl_text_style_get_decoration(const ipl_text_style_t* self);

void ipl_text_style_set_decoration(ipl_text_style_t* self, int decoration);

void ipl_text_style_get_decoration_color(const ipl_text_style_t* self,
                                         ipl_color_t* out);

void ipl_text_style_set_decoration_color(ipl_text_style_t* self,
                                         const ipl_color_t* color);

ipl_text_decoration_style_t ipl_text_style_get_decoration_style(
    const ipl_text_style_t* self);

void ipl_text_style_set_decoration_style(ipl_text_style_t* self,
                                         ipl_text_decoration_style_t style);

double ipl_text_style_get_decoration_thickness_multiplier(
    const ipl_text_style_t* self);

void ipl_text_style_set_decoration_thickness_multiplier(ipl_text_style_t* self,
                                                        double multiplier);

int ipl_text_style_get_font_weight(const ipl_text_style_t* self);

void ipl_text_style_set_font_weight(ipl_text_style_t* self, int font_weight);

ipl_font_style_t ipl_text_style_get_font_style(const ipl_text_style_t* self);

void ipl_text_style_set_font_style(ipl_text_style_t* self,
                                   ipl_font_style_t font_style);

ipl_text_baseline_t ipl_text_style_get_text_baseline(
    const ipl_text_style_t* self);

void ipl_text_style_set_text_baseline(ipl_text_style_t* self,
                                      ipl_text_baseline_t text_baseline);

bool ipl_text_style_get_half_leading(const ipl_text_style_t* self);

void ipl_text_style_set_half_leading(ipl_text_style_t* self, bool half_leading);

void ipl_text_style_set_font_families(ipl_text_style_t* self,
                                      const char* const* ptrs,
                                      const size_t* lens,
                                      size_t count);

void ipl_text_style_get_font_families(const ipl_text_style_t* self,
                                      const char*** ptrs,
                                      size_t** lens,
                                      size_t* count);

void ipl_text_style_set_font_size(ipl_text_style_t* self, double font_size);

double ipl_text_style_get_font_size(const ipl_text_style_t* self);

void ipl_text_style_set_letter_spacing(ipl_text_style_t* self,
                                       double letter_spacing);

double ipl_text_style_get_letter_spacing(const ipl_text_style_t* self);

void ipl_text_style_set_word_spacing(ipl_text_style_t* self,
                                     double word_spacing);

double ipl_text_style_get_word_spacing(const ipl_text_style_t* self);

void ipl_text_style_set_height(ipl_text_style_t* self, double height);

double ipl_text_style_get_height(const ipl_text_style_t* self);

void ipl_text_style_set_has_height_override(ipl_text_style_t* self,
                                            bool has_height_override);

bool ipl_text_style_get_has_height_override(const ipl_text_style_t* self);

void ipl_text_style_set_locale(ipl_text_style_t* self,
                               const char* ptr,
                               size_t len);

void ipl_text_style_get_locale(const ipl_text_style_t* self,
                               const char** ptr,
                               size_t* len);

bool ipl_text_style_has_background(const ipl_text_style_t* self);

void ipl_text_style_get_background(const ipl_text_style_t* self,
                                   ipl_paint_t* out);

void ipl_text_style_set_background(ipl_text_style_t* self,
                                   const ipl_paint_t* paint);

void ipl_text_style_clear_background(ipl_text_style_t* self);

bool ipl_text_style_has_foreground(const ipl_text_style_t* self);

void ipl_text_style_get_foreground(const ipl_text_style_t* self,
                                   ipl_paint_t* out);

void ipl_text_style_set_foreground(ipl_text_style_t* self,
                                   const ipl_paint_t* paint);

void ipl_text_style_clear_foreground(ipl_text_style_t* self);

void ipl_text_style_set_text_shadows(ipl_text_style_t* self,
                                     const ipl_text_shadow_t* shadows,
                                     size_t count);

void ipl_text_style_get_text_shadows(const ipl_text_style_t* self,
                                     ipl_text_shadow_t* out,
                                     size_t* count);

const ipl_font_features_t* ipl_text_style_get_font_features(
    const ipl_text_style_t* self);

void ipl_text_style_set_font_features(ipl_text_style_t* self,
                                      const ipl_font_features_t* font_features);

const ipl_font_variations_t* ipl_text_style_get_font_variations(
    const ipl_text_style_t* self);

void ipl_text_style_set_font_variations(
    ipl_text_style_t* self,
    const ipl_font_variations_t* font_variations);

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/txt/src/txt/text_style.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/txt/src/txt/font_collection.h
// ---------------------------------------------------------------------------

void ipl_font_collection_new(ipl_font_collection_t* out);

void ipl_font_collection_drop(ipl_font_collection_t* self);

void ipl_font_collection_setup_default_font_manager(
    const ipl_font_collection_t* self,
    uint32_t font_initialization_data);

void ipl_font_collection_disable_font_fallback(
    const ipl_font_collection_t* self);

void ipl_font_collection_clear_font_family_cache(
    const ipl_font_collection_t* self);

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/txt/src/txt/font_collection.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/txt/src/txt/paragraph.h
// ---------------------------------------------------------------------------

void ipl_paragraph_drop(ipl_paragraph_t* self);

// flutter::Paragraph::GetMaxWidth
double ipl_paragraph_get_max_width(const ipl_paragraph_t* self);

// flutter::Paragraph::GetHeight
double ipl_paragraph_get_height(const ipl_paragraph_t* self);

// flutter::Paragraph::GetLongestLine
double ipl_paragraph_get_longest_line(const ipl_paragraph_t* self);

// flutter::Paragraph::GetMinIntrinsicWidth
double ipl_paragraph_get_min_intrinsic_width(const ipl_paragraph_t* self);

// flutter::Paragraph::GetMaxIntrinsicWidth
double ipl_paragraph_get_max_intrinsic_width(const ipl_paragraph_t* self);

// flutter::Paragraph::GetAlphabeticBaseline
double ipl_paragraph_get_alphabetic_baseline(const ipl_paragraph_t* self);

// flutter::Paragraph::GetIdeographicBaseline
double ipl_paragraph_get_ideographic_baseline(const ipl_paragraph_t* self);

// flutter::Paragraph::DidExceedMaxLines
bool ipl_paragraph_did_exceed_max_lines(const ipl_paragraph_t* self);

// flutter::Paragraph::Layout
void ipl_paragraph_layout(const ipl_paragraph_t* self, double width);

// flutter::Paragraph::Paint
bool ipl_paragraph_paint(const ipl_paragraph_t* self,
                         const ipl_display_list_builder_t* builder,
                         double x,
                         double y);

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/txt/src/txt/paragraph.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/txt/src/skia/paragraph_builder_skia.h
// ---------------------------------------------------------------------------

void ipl_paragraph_builder_new(const ipl_paragraph_style_t* style,
                               const ipl_font_collection_t* font_collection,
                               ipl_paragraph_builder_t* out);

void ipl_paragraph_builder_drop(ipl_paragraph_builder_t* self);

void ipl_paragraph_builder_push_style(const ipl_paragraph_builder_t* self,
                                      const ipl_text_style_t* style);

void ipl_paragraph_builder_pop(const ipl_paragraph_builder_t* self);

const ipl_text_style_t* ipl_paragraph_builder_peek_style(
    const ipl_paragraph_builder_t* self);

void ipl_paragraph_builder_add_text(const ipl_paragraph_builder_t* self,
                                    const uint8_t* utf8_data,
                                    size_t byte_length);

void ipl_paragraph_builder_add_placeholder(const ipl_paragraph_builder_t* self,
                                           ipl_placehoder_run_t* span);

void ipl_paragraph_builder_build(const ipl_paragraph_builder_t* self,
                                 ipl_paragraph_t* out);

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/txt/src/skia/paragraph_builder_skia.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/impeller/typographer/typographer_context.h
// ---------------------------------------------------------------------------

void ipl_typographer_context_drop(ipl_typographer_context_t* self);

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/impeller/typographer/typographer_context.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/impeller/renderer/context.h
// ---------------------------------------------------------------------------

void ipl_context_drop(ipl_context_t* self);

void ipl_context_clone(const ipl_context_t* self, ipl_context_t* out);

void ipl_context_from_vk_context(const ipl_vk_context_t* vk_context,
                                 ipl_context_t* out);

void ipl_context_reset_thread_local_state(const ipl_context_t* self);

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/impeller/renderer/context.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/impeller/renderer/surface.h
// ---------------------------------------------------------------------------

void ipl_surface_drop(ipl_surface_t* self);

void ipl_surface_get_size(const ipl_surface_t* self, ipl_i64_size_t* out);

ipl_const_render_target_t ipl_surface_get_render_target(
    const ipl_surface_t* self);

bool ipl_surface_present(const ipl_surface_t* self);

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/impeller/renderer/surface.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/impeller/renderer/backend/vulkan/context_vk.h
// ---------------------------------------------------------------------------

void ipl_vk_context_settings_new(ipl_vk_context_settings_t* out);

void ipl_vk_context_settings_drop(ipl_vk_context_settings_t* self);

void ipl_vk_context_settings_set_proc_address_callback(
    ipl_vk_context_settings_t* self,
    void* (*proc_address_callback)(VkInstance, const char*));

void ipl_vk_context_settings_set_enable_validation(
    ipl_vk_context_settings_t* self,
    bool enable_validation);

void ipl_vk_context_settings_set_flags(ipl_vk_context_settings_t* self,
                                       const ipl_flags_t* flags);

bool ipl_vk_context_new(ipl_vk_context_settings_t* settings,
                        ipl_vk_context_t* out);

void ipl_vk_context_drop(ipl_vk_context_t* self);

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/impeller/renderer/backend/vulkan/context_vk.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN]
// engine/src/flutter/impeller/renderer/backend/vulkan/swapchain/swapchain_vk.h
// ---------------------------------------------------------------------------

bool ipl_vk_swapchain_new(const ipl_context_t* context,
                          VkSurfaceKHR surface,
                          const ipl_i64_size_t* size,
                          bool enable_msaa,
                          ipl_vk_swapchain_t* out);

void ipl_vk_swapchain_drop(ipl_vk_swapchain_t* self);

bool ipl_vk_swapchain_acquire_next_drawable(const ipl_vk_swapchain_t* self,
                                            ipl_surface_t* out);

void ipl_vk_swapchain_update_surface_size(const ipl_vk_swapchain_t* self,
                                          const ipl_i64_size_t* size);

// ---------------------------------------------------------------------------
// [END]
// engine/src/flutter/impeller/renderer/backend/vulkan/swapchain/swapchain_vk.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/impeller/renderer/render_target.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/impeller/renderer/render_target.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/impeller/entity/contents/content_context.h
// ---------------------------------------------------------------------------

bool ipl_content_context_new(
    const ipl_context_t* context,
    const ipl_typographer_context_t* typographer_context,
    ipl_content_context_t* out);

void ipl_content_context_drop(ipl_content_context_t* self);

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/impeller/entity/contents/content_context.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/impeller/display_list/dl_dispatcher.h
// ---------------------------------------------------------------------------

bool ipl_display_list_render_to_target(const ipl_display_list_t* self,
                                       const ipl_content_context_t* context,
                                       ipl_const_render_target_t render_target,
                                       const ipl_f32_rect_t* cull_rect,
                                       bool reset_host_buffer,
                                       bool is_onscreen);

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/impeller/display_list/dl_dispatcher.h
// ---------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif

// ===========================================================================
// [END] Function Declaration
// ===========================================================================

#endif  // FLUTTER_FFI_IPL_H_
