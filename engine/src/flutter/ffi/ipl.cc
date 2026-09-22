#include <cassert>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <optional>
#include <string_view>
#include <type_traits>
#include <utility>

#include "ipl.h"

#include "display_list/dl_blend_mode.h"
#include "display_list/dl_builder.h"
#include "display_list/dl_color.h"
#include "display_list/dl_paint.h"
#include "display_list/effects/dl_color_filter.h"
#include "display_list/effects/dl_color_source.h"
#include "display_list/effects/dl_image_filter.h"
#include "display_list/effects/dl_mask_filter.h"
#include "display_list/geometry/dl_geometry_types.h"
#include "display_list/geometry/dl_path.h"
#include "display_list/geometry/dl_path_builder.h"
#include "display_list/image/dl_image.h"
#include "impeller/base/flags.h"
#include "impeller/core/allocator.h"
#include "impeller/core/buffer_view.h"
#include "impeller/core/device_buffer.h"
#include "impeller/core/device_buffer_descriptor.h"
#include "impeller/core/formats.h"
#include "impeller/core/host_buffer.h"
#include "impeller/core/range.h"
#include "impeller/core/texture.h"
#include "impeller/core/texture_descriptor.h"
#include "impeller/core/vertex_buffer.h"
#include "impeller/display_list/dl_dispatcher.h"
#include "impeller/display_list/dl_image_impeller.h"
#include "impeller/entity/contents/content_context.h"
#include "impeller/geometry/matrix.h"
#include "impeller/geometry/point.h"
#include "impeller/geometry/rect.h"
#include "impeller/geometry/round_rect.h"
#include "impeller/geometry/rounding_radii.h"
#include "impeller/geometry/rstransform.h"
#include "impeller/geometry/size.h"
#include "impeller/geometry/vector.h"
#include "include/core/SkRefCnt.h"

#include "txt/font_collection.h"
#include "txt/font_features.h"
#include "txt/font_style.h"
#include "txt/paragraph.h"
#include "txt/paragraph_builder.h"
#include "txt/paragraph_style.h"
#include "txt/placeholder_run.h"
#include "txt/text_baseline.h"
#include "txt/text_decoration.h"
#include "txt/text_shadow.h"
#include "txt/text_style.h"

#include "impeller/renderer/backend/vulkan/context_vk.h"
#include "impeller/renderer/backend/vulkan/swapchain/swapchain_vk.h"
#include "impeller/renderer/context.h"
#include "impeller/renderer/render_target.h"
#include "impeller/renderer/surface.h"
#include "impeller/typographer/typographer_context.h"
#include "vulkan/vulkan.hpp"
#include "vulkan/vulkan_core.h"

// ===========================================================================
// [BEGIN] Type Checking And Type Conversion
// ===========================================================================

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/impeller/geometry/matrix.h
// ---------------------------------------------------------------------------

// impeller::Matrix
static_assert(std::is_standard_layout_v<impeller::Matrix>);
static_assert(std::is_standard_layout_v<ipl_matrix_t>);
static_assert(sizeof(impeller::Matrix) == sizeof(ipl_matrix_t));
static_assert(alignof(impeller::Matrix) == alignof(ipl_matrix_t));
static_assert(offsetof(impeller::Matrix, m) == offsetof(ipl_matrix_t, data));
static_assert(std::is_same_v<decltype(impeller::Matrix::m),
                             decltype(ipl_matrix_t::data)>);
static_assert(__builtin_is_cpp_trivially_relocatable(impeller::Matrix));
static_assert(__builtin_is_cpp_trivially_relocatable(ipl_matrix_t));

static inline void validate(const ipl_matrix_t* src) {
  assert(src != nullptr);
  assert(reinterpret_cast<intptr_t>(src) % alignof(ipl_matrix_t) == 0);
}

static inline void validate(const impeller::Matrix* src) {
  assert(src != nullptr);
  assert(reinterpret_cast<intptr_t>(src) % alignof(impeller::Matrix) == 0);
}

[[maybe_unused]] static inline impeller::Matrix* transmute(ipl_matrix_t* src) {
  validate(src);
  return reinterpret_cast<impeller::Matrix*>(src);
}

[[maybe_unused]] static inline const impeller::Matrix* transmute(
    const ipl_matrix_t* src,
    bool is_nonnull = true) {
  if (is_nonnull) {
    validate(src);
  }
  return reinterpret_cast<const impeller::Matrix*>(src);
}

[[maybe_unused]] static inline ipl_matrix_t* transmute(impeller::Matrix* src) {
  validate(src);
  return reinterpret_cast<ipl_matrix_t*>(src);
}

[[maybe_unused]] static inline const ipl_matrix_t* transmute(
    const impeller::Matrix* src) {
  validate(src);
  return reinterpret_cast<const ipl_matrix_t*>(src);
}

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/impeller/geometry/matrix.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/impeller/geometry/point.h
// ---------------------------------------------------------------------------

// impeller::Point
static_assert(std::is_standard_layout_v<impeller::Point>);
static_assert(std::is_standard_layout_v<ipl_f32_point_t>);
static_assert(sizeof(impeller::Point) == sizeof(ipl_f32_point_t));
static_assert(alignof(impeller::Point) == alignof(ipl_f32_point_t));
static_assert(offsetof(impeller::Point, x) == offsetof(ipl_f32_point_t, x));
static_assert(offsetof(impeller::Point, y) == offsetof(ipl_f32_point_t, y));
static_assert(
    std::is_same_v<decltype(impeller::Point::x), decltype(ipl_f32_point_t::x)>);
static_assert(
    std::is_same_v<decltype(impeller::Point::y), decltype(ipl_f32_point_t::y)>);
static_assert(__builtin_is_cpp_trivially_relocatable(impeller::Point));
static_assert(__builtin_is_cpp_trivially_relocatable(ipl_f32_point_t));

static inline void validate(const ipl_f32_point_t* src) {
  assert(src != nullptr);
  assert(reinterpret_cast<intptr_t>(src) % alignof(ipl_f32_point_t) == 0);
}

static inline void validate(const impeller::Point* src) {
  assert(src != nullptr);
  assert(reinterpret_cast<intptr_t>(src) % alignof(impeller::Point) == 0);
}

[[maybe_unused]] static inline impeller::Point* transmute(
    ipl_f32_point_t* src,
    bool is_nonnull = true) {
  if (is_nonnull) {
    assert(src != nullptr);
    assert(reinterpret_cast<intptr_t>(src) % alignof(ipl_f32_point_t) == 0);
  }
  return reinterpret_cast<impeller::Point*>(src);
}

[[maybe_unused]] static inline const impeller::Point* transmute(
    const ipl_f32_point_t* src) {
  validate(src);
  return reinterpret_cast<const impeller::Point*>(src);
}

[[maybe_unused]] static inline ipl_f32_point_t* transmute(
    impeller::Point* src) {
  validate(src);
  return reinterpret_cast<ipl_f32_point_t*>(src);
}

[[maybe_unused]] static inline const ipl_f32_point_t* transmute(
    const impeller::Point* src) {
  validate(src);
  return reinterpret_cast<const ipl_f32_point_t*>(src);
}

// impeller::IPoint32
static_assert(std::is_standard_layout_v<impeller::IPoint32>);
static_assert(std::is_standard_layout_v<ipl_i32_point_t>);
static_assert(sizeof(impeller::IPoint32) == sizeof(ipl_i32_point_t));
static_assert(alignof(impeller::IPoint32) == alignof(ipl_i32_point_t));
static_assert(offsetof(impeller::IPoint32, x) == offsetof(ipl_i32_point_t, x));
static_assert(offsetof(impeller::IPoint32, y) == offsetof(ipl_i32_point_t, y));
static_assert(std::is_same_v<decltype(impeller::IPoint32::x),
                             decltype(ipl_i32_point_t::x)>);
static_assert(std::is_same_v<decltype(impeller::IPoint32::y),
                             decltype(ipl_i32_point_t::y)>);
static_assert(__builtin_is_cpp_trivially_relocatable(impeller::IPoint32));
static_assert(__builtin_is_cpp_trivially_relocatable(ipl_i32_point_t));

// impeller::UintPoint32
static_assert(std::is_standard_layout_v<impeller::UintPoint32>);
static_assert(std::is_standard_layout_v<ipl_u32_point_t>);
static_assert(sizeof(impeller::UintPoint32) == sizeof(ipl_u32_point_t));
static_assert(alignof(impeller::UintPoint32) == alignof(ipl_u32_point_t));
static_assert(offsetof(impeller::UintPoint32, x) ==
              offsetof(ipl_u32_point_t, x));
static_assert(offsetof(impeller::UintPoint32, y) ==
              offsetof(ipl_u32_point_t, y));
static_assert(std::is_same_v<decltype(impeller::UintPoint32::x),
                             decltype(ipl_u32_point_t::x)>);
static_assert(std::is_same_v<decltype(impeller::UintPoint32::y),
                             decltype(ipl_u32_point_t::y)>);
static_assert(__builtin_is_cpp_trivially_relocatable(impeller::UintPoint32));
static_assert(__builtin_is_cpp_trivially_relocatable(ipl_u32_point_t));

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/impeller/geometry/point.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/impeller/geometry/rect.h
// ---------------------------------------------------------------------------

// impeller::Rect
static_assert(std::is_standard_layout_v<impeller::Rect>);
static_assert(std::is_standard_layout_v<ipl_f32_rect_t>);
static_assert(sizeof(impeller::Rect) == sizeof(ipl_f32_rect_t));
static_assert(alignof(impeller::Rect) == alignof(ipl_f32_rect_t));
static_assert(__is_layout_compatible(impeller::Rect, ipl_f32_rect_t));
static_assert(__builtin_is_cpp_trivially_relocatable(impeller::Rect));
static_assert(__builtin_is_cpp_trivially_relocatable(ipl_f32_rect_t));

static inline void validate(const ipl_f32_rect_t* src) {
  assert(src != nullptr);
  assert(reinterpret_cast<intptr_t>(src) % alignof(ipl_f32_rect_t) == 0);
}

static inline void validate(const impeller::Rect* src) {
  assert(src != nullptr);
  assert(reinterpret_cast<intptr_t>(src) % alignof(impeller::Rect) == 0);
}

[[maybe_unused]] static inline impeller::Rect* transmute(
    ipl_f32_rect_t* src,
    bool is_nonnull = true) {
  if (is_nonnull) {
    validate(src);
  }
  return reinterpret_cast<impeller::Rect*>(src);
}

[[maybe_unused]] static inline const impeller::Rect* transmute(
    const ipl_f32_rect_t* src,
    bool is_nonnull = true) {
  if (is_nonnull) {
    validate(src);
  }
  return reinterpret_cast<const impeller::Rect*>(src);
}

[[maybe_unused]] static inline ipl_f32_rect_t* transmute(impeller::Rect* src) {
  validate(src);
  return reinterpret_cast<ipl_f32_rect_t*>(src);
}

[[maybe_unused]] static inline const ipl_f32_rect_t* transmute(
    const impeller::Rect* src) {
  validate(src);
  return reinterpret_cast<const ipl_f32_rect_t*>(src);
}

// impeller::IRect32
static_assert(std::is_standard_layout_v<impeller::IRect32>);
static_assert(std::is_standard_layout_v<ipl_i32_rect_t>);
static_assert(sizeof(impeller::IRect32) == sizeof(ipl_i32_rect_t));
static_assert(alignof(impeller::IRect32) == alignof(ipl_i32_rect_t));
static_assert(__is_layout_compatible(impeller::IRect32, ipl_i32_rect_t));
static_assert(__builtin_is_cpp_trivially_relocatable(impeller::IRect32));
static_assert(__builtin_is_cpp_trivially_relocatable(ipl_i32_rect_t));

static inline void validate(const ipl_i32_rect_t* src) {
  assert(src != nullptr);
  assert(reinterpret_cast<intptr_t>(src) % alignof(ipl_i32_rect_t) == 0);
}

static inline void validate(const impeller::IRect32* src) {
  assert(src != nullptr);
  assert(reinterpret_cast<intptr_t>(src) % alignof(impeller::IRect32) == 0);
}

[[maybe_unused]] static inline impeller::IRect32* transmute(
    ipl_i32_rect_t* src,
    bool is_nonnull = true) {
  if (is_nonnull) {
    validate(src);
  }
  return reinterpret_cast<impeller::IRect32*>(src);
}

[[maybe_unused]] static inline const impeller::IRect32* transmute(
    const ipl_i32_rect_t* src) {
  validate(src);
  return reinterpret_cast<const impeller::IRect32*>(src);
}

[[maybe_unused]] static inline ipl_i32_rect_t* transmute(
    impeller::IRect32* src) {
  validate(src);
  return reinterpret_cast<ipl_i32_rect_t*>(src);
}

[[maybe_unused]] static inline const ipl_i32_rect_t* transmute(
    const impeller::IRect32* src) {
  validate(src);
  return reinterpret_cast<const ipl_i32_rect_t*>(src);
}

// impeller::IRect64
static_assert(std::is_standard_layout_v<impeller::IRect64>);
static_assert(std::is_standard_layout_v<ipl_i64_rect_t>);
static_assert(sizeof(impeller::IRect64) == sizeof(ipl_i64_rect_t));
static_assert(alignof(impeller::IRect64) == alignof(ipl_i64_rect_t));
static_assert(__is_layout_compatible(impeller::IRect64, ipl_i64_rect_t));
static_assert(__builtin_is_cpp_trivially_relocatable(impeller::IRect64));
static_assert(__builtin_is_cpp_trivially_relocatable(ipl_i64_rect_t));

static inline void validate(const ipl_i64_rect_t* src) {
  assert(src != nullptr);
  assert(reinterpret_cast<intptr_t>(src) % alignof(ipl_i64_rect_t) == 0);
}

static inline void validate(const impeller::IRect64* src) {
  assert(src != nullptr);
  assert(reinterpret_cast<intptr_t>(src) % alignof(impeller::IRect64) == 0);
}

[[maybe_unused]] static inline impeller::IRect64* transmute(
    ipl_i64_rect_t* src,
    bool is_nonnull = true) {
  if (is_nonnull) {
    validate(src);
  }
  return reinterpret_cast<impeller::IRect64*>(src);
}

[[maybe_unused]] static inline const impeller::IRect64* transmute(
    const ipl_i64_rect_t* src) {
  validate(src);
  return reinterpret_cast<const impeller::IRect64*>(src);
}

[[maybe_unused]] static inline ipl_i64_rect_t* transmute(
    impeller::IRect64* src) {
  validate(src);
  return reinterpret_cast<ipl_i64_rect_t*>(src);
}

[[maybe_unused]] static inline const ipl_i64_rect_t* transmute(
    const impeller::IRect64* src) {
  validate(src);
  return reinterpret_cast<const ipl_i64_rect_t*>(src);
}

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/impeller/geometry/rect.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/impeller/geometry/rstransform.h
// ---------------------------------------------------------------------------

// impeller::RSTransform
static_assert(std::is_standard_layout_v<impeller::RSTransform>);
static_assert(std::is_standard_layout_v<ipl_rs_transform_t>);
static_assert(sizeof(impeller::RSTransform) == sizeof(ipl_rs_transform_t));
static_assert(alignof(impeller::RSTransform) == alignof(ipl_rs_transform_t));
static_assert(offsetof(impeller::RSTransform, scaled_cos) ==
              offsetof(ipl_rs_transform_t, scaled_cos));
static_assert(offsetof(impeller::RSTransform, scaled_sin) ==
              offsetof(ipl_rs_transform_t, scaled_sin));
static_assert(offsetof(impeller::RSTransform, translate_x) ==
              offsetof(ipl_rs_transform_t, translate_x));
static_assert(offsetof(impeller::RSTransform, translate_y) ==
              offsetof(ipl_rs_transform_t, translate_y));
static_assert(std::is_same_v<decltype(impeller::RSTransform::scaled_cos),
                             decltype(ipl_rs_transform_t::scaled_cos)>);
static_assert(std::is_same_v<decltype(impeller::RSTransform::scaled_sin),
                             decltype(ipl_rs_transform_t::scaled_sin)>);
static_assert(std::is_same_v<decltype(impeller::RSTransform::translate_x),
                             decltype(ipl_rs_transform_t::translate_x)>);
static_assert(std::is_same_v<decltype(impeller::RSTransform::translate_y),
                             decltype(ipl_rs_transform_t::translate_y)>);
static_assert(__is_layout_compatible(impeller::RSTransform,
                                     ipl_rs_transform_t));
static_assert(__builtin_is_cpp_trivially_relocatable(impeller::RSTransform));
static_assert(__builtin_is_cpp_trivially_relocatable(ipl_rs_transform_t));

static inline void validate(const ipl_rs_transform_t* src) {
  assert(src != nullptr);
  assert(reinterpret_cast<intptr_t>(src) % alignof(ipl_rs_transform_t) == 0);
}

static inline void validate(const impeller::RSTransform* src) {
  assert(src != nullptr);
  assert(reinterpret_cast<intptr_t>(src) % alignof(impeller::RSTransform) == 0);
}

[[maybe_unused]] static inline impeller::RSTransform* transmute(
    ipl_rs_transform_t* src) {
  validate(src);
  return reinterpret_cast<impeller::RSTransform*>(src);
}

[[maybe_unused]] static inline const impeller::RSTransform* transmute(
    const ipl_rs_transform_t* src) {
  validate(src);
  return reinterpret_cast<const impeller::RSTransform*>(src);
}

[[maybe_unused]] static inline ipl_rs_transform_t* transmute(
    impeller::RSTransform* src) {
  validate(src);
  return reinterpret_cast<ipl_rs_transform_t*>(src);
}

[[maybe_unused]] static inline const ipl_rs_transform_t* transmute(
    const impeller::RSTransform* src) {
  validate(src);
  return reinterpret_cast<const ipl_rs_transform_t*>(src);
}

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/impeller/geometry/rstransform.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/impeller/geometry/size.h
// ---------------------------------------------------------------------------

// impeller::Size
static_assert(std::is_standard_layout_v<impeller::Size>);
static_assert(std::is_standard_layout_v<ipl_f32_size_t>);
static_assert(sizeof(impeller::Size) == sizeof(ipl_f32_size_t));
static_assert(alignof(impeller::Size) == alignof(ipl_f32_size_t));
static_assert(offsetof(impeller::Size, width) ==
              offsetof(ipl_f32_size_t, width));
static_assert(offsetof(impeller::Size, height) ==
              offsetof(ipl_f32_size_t, height));
static_assert(std::is_same_v<decltype(impeller::Size::width),
                             decltype(ipl_f32_size_t::width)>);
static_assert(std::is_same_v<decltype(impeller::Size::height),
                             decltype(ipl_f32_size_t::height)>);
static_assert(__builtin_is_cpp_trivially_relocatable(impeller::Size));
static_assert(__builtin_is_cpp_trivially_relocatable(ipl_f32_size_t));

// impeller::ISize32
static_assert(std::is_standard_layout_v<impeller::ISize32>);
static_assert(std::is_standard_layout_v<ipl_i32_size_t>);
static_assert(sizeof(impeller::ISize32) == sizeof(ipl_i32_size_t));
static_assert(alignof(impeller::ISize32) == alignof(ipl_i32_size_t));
static_assert(offsetof(impeller::ISize32, width) ==
              offsetof(ipl_i32_size_t, width));
static_assert(offsetof(impeller::ISize32, height) ==
              offsetof(ipl_i32_size_t, height));
static_assert(std::is_same_v<decltype(impeller::ISize32::width),
                             decltype(ipl_i32_size_t::width)>);
static_assert(std::is_same_v<decltype(impeller::ISize32::height),
                             decltype(ipl_i32_size_t::height)>);
static_assert(__builtin_is_cpp_trivially_relocatable(impeller::ISize32));
static_assert(__builtin_is_cpp_trivially_relocatable(ipl_i32_size_t));

// impeller::ISize64
static_assert(std::is_standard_layout_v<impeller::ISize64>);
static_assert(std::is_standard_layout_v<ipl_i64_size_t>);
static_assert(sizeof(impeller::ISize64) == sizeof(ipl_i64_size_t));
static_assert(alignof(impeller::ISize64) == alignof(ipl_i64_size_t));
static_assert(offsetof(impeller::ISize64, width) ==
              offsetof(ipl_i64_size_t, width));
static_assert(offsetof(impeller::ISize64, height) ==
              offsetof(ipl_i64_size_t, height));
static_assert(std::is_same_v<decltype(impeller::ISize64::width),
                             decltype(ipl_i64_size_t::width)>);
static_assert(std::is_same_v<decltype(impeller::ISize64::height),
                             decltype(ipl_i64_size_t::height)>);
static_assert(__builtin_is_cpp_trivially_relocatable(impeller::ISize64));
static_assert(__builtin_is_cpp_trivially_relocatable(ipl_i64_size_t));

static inline void validate(const ipl_i64_size_t* src) {
  assert(src != nullptr);
  assert(reinterpret_cast<intptr_t>(src) % alignof(ipl_i64_size_t) == 0);
}

static inline void validate(const impeller::ISize64* src) {
  assert(src != nullptr);
  assert(reinterpret_cast<intptr_t>(src) % alignof(impeller::ISize64) == 0);
}

[[maybe_unused]] static inline impeller::ISize64* transmute(
    ipl_i64_size_t* src) {
  validate(src);
  return reinterpret_cast<impeller::ISize64*>(src);
}

[[maybe_unused]] static inline const impeller::ISize64* transmute(
    const ipl_i64_size_t* src) {
  validate(src);
  return reinterpret_cast<const impeller::ISize64*>(src);
}

[[maybe_unused]] static inline ipl_i64_size_t* transmute(
    impeller::ISize64* src) {
  validate(src);
  return reinterpret_cast<ipl_i64_size_t*>(src);
}

[[maybe_unused]] static inline const ipl_i64_size_t* transmute(
    const impeller::ISize64* src) {
  validate(src);
  return reinterpret_cast<const ipl_i64_size_t*>(src);
}

// impeller::Vector2
static_assert(std::is_standard_layout_v<impeller::Vector2>);
static_assert(std::is_standard_layout_v<ipl_vector2_t>);
static_assert(sizeof(impeller::Vector2) == sizeof(ipl_vector2_t));
static_assert(alignof(impeller::Vector2) == alignof(ipl_vector2_t));
static_assert(offsetof(impeller::Vector2, x) == offsetof(ipl_vector2_t, x));
static_assert(offsetof(impeller::Vector2, y) == offsetof(ipl_vector2_t, y));
static_assert(
    std::is_same_v<decltype(impeller::Vector2::x), decltype(ipl_vector2_t::x)>);
static_assert(
    std::is_same_v<decltype(impeller::Vector2::y), decltype(ipl_vector2_t::y)>);
static_assert(__builtin_is_cpp_trivially_relocatable(impeller::Vector2));
static_assert(__builtin_is_cpp_trivially_relocatable(ipl_vector2_t));

// impeller::Quad
static_assert(std::is_standard_layout_v<impeller::Quad>);
static_assert(std::is_standard_layout_v<ipl_quad_t>);
static_assert(sizeof(impeller::Quad) == sizeof(ipl_quad_t));
static_assert(alignof(impeller::Quad) == alignof(ipl_quad_t));
static_assert(__builtin_is_cpp_trivially_relocatable(impeller::Quad));
static_assert(__builtin_is_cpp_trivially_relocatable(ipl_quad_t));

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/impeller/geometry/size.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/impeller/geometry/rounding_radii.h
// ---------------------------------------------------------------------------

static_assert(std::is_standard_layout_v<impeller::RoundingRadii>);
static_assert(std::is_standard_layout_v<ipl_rounding_radii_t>);
static_assert(sizeof(impeller::RoundingRadii) == sizeof(ipl_rounding_radii_t));
static_assert(alignof(impeller::RoundingRadii) ==
              alignof(ipl_rounding_radii_t));
static_assert(offsetof(impeller::RoundingRadii, top_left) ==
              offsetof(ipl_rounding_radii_t, top_left));
static_assert(offsetof(impeller::RoundingRadii, top_right) ==
              offsetof(ipl_rounding_radii_t, top_right));
static_assert(offsetof(impeller::RoundingRadii, bottom_left) ==
              offsetof(ipl_rounding_radii_t, bottom_left));
static_assert(offsetof(impeller::RoundingRadii, bottom_right) ==
              offsetof(ipl_rounding_radii_t, bottom_right));
static_assert(__is_layout_compatible(impeller::RoundingRadii,
                                     ipl_rounding_radii_t));
static_assert(__builtin_is_cpp_trivially_relocatable(impeller::RoundingRadii));
static_assert(__builtin_is_cpp_trivially_relocatable(ipl_rounding_radii_t));

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/impeller/geometry/rounding_radii.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/impeller/geometry/round_rect.h
// ---------------------------------------------------------------------------

// impeller::RoundRect
static_assert(std::is_standard_layout_v<impeller::RoundRect>);
static_assert(std::is_standard_layout_v<ipl_round_rect_t>);
static_assert(sizeof(impeller::RoundRect) == sizeof(ipl_round_rect_t));
static_assert(alignof(impeller::RoundRect) == alignof(ipl_round_rect_t));
static_assert(__is_layout_compatible(impeller::RoundRect, ipl_round_rect_t));
static_assert(__builtin_is_cpp_trivially_relocatable(impeller::RoundRect));
static_assert(__builtin_is_cpp_trivially_relocatable(ipl_round_rect_t));

static inline void validate(const ipl_round_rect_t* src) {
  assert(src != nullptr);
  assert(reinterpret_cast<intptr_t>(src) % alignof(ipl_round_rect_t) == 0);
}

static inline void validate(const impeller::RoundRect* src) {
  assert(src != nullptr);
  assert(reinterpret_cast<intptr_t>(src) % alignof(impeller::RoundRect) == 0);
}

[[maybe_unused]] static inline impeller::RoundRect* transmute(
    ipl_round_rect_t* src,
    bool is_nonnull = true) {
  if (is_nonnull) {
    validate(src);
  }
  return reinterpret_cast<impeller::RoundRect*>(src);
}

[[maybe_unused]] static inline const impeller::RoundRect* transmute(
    const ipl_round_rect_t* src) {
  validate(src);
  return reinterpret_cast<const impeller::RoundRect*>(src);
}

[[maybe_unused]] static inline ipl_round_rect_t* transmute(
    impeller::RoundRect* src) {
  validate(src);
  return reinterpret_cast<ipl_round_rect_t*>(src);
}

[[maybe_unused]] static inline const ipl_round_rect_t* transmute(
    const impeller::RoundRect* src) {
  validate(src);
  return reinterpret_cast<const ipl_round_rect_t*>(src);
}

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/impeller/geometry/round_rect.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/impeller/geometry/vector.h
// ---------------------------------------------------------------------------

// impeller::Vector3
static_assert(std::is_standard_layout_v<impeller::Vector3>);
static_assert(std::is_standard_layout_v<ipl_vector3_t>);
static_assert(sizeof(impeller::Vector3) == sizeof(ipl_vector3_t));
static_assert(alignof(impeller::Vector3) == alignof(ipl_vector3_t));
static_assert(offsetof(impeller::Vector3, x) == offsetof(ipl_vector3_t, x));
static_assert(offsetof(impeller::Vector3, y) == offsetof(ipl_vector3_t, y));
static_assert(offsetof(impeller::Vector3, z) == offsetof(ipl_vector3_t, z));
static_assert(
    std::is_same_v<decltype(impeller::Vector3::x), decltype(ipl_vector3_t::x)>);
static_assert(
    std::is_same_v<decltype(impeller::Vector3::y), decltype(ipl_vector3_t::y)>);
static_assert(
    std::is_same_v<decltype(impeller::Vector3::z), decltype(ipl_vector3_t::z)>);
static_assert(__builtin_is_cpp_trivially_relocatable(impeller::Vector3));
static_assert(__builtin_is_cpp_trivially_relocatable(ipl_vector3_t));

// impeller::Vector4
static_assert(std::is_standard_layout_v<impeller::Vector4>);
static_assert(std::is_standard_layout_v<ipl_vector4_t>);
static_assert(sizeof(impeller::Vector4) == sizeof(ipl_vector4_t));
static_assert(alignof(impeller::Vector4) == alignof(ipl_vector4_t));
static_assert(offsetof(impeller::Vector4, x) == offsetof(ipl_vector4_t, x));
static_assert(offsetof(impeller::Vector4, y) == offsetof(ipl_vector4_t, y));
static_assert(offsetof(impeller::Vector4, z) == offsetof(ipl_vector4_t, z));
static_assert(offsetof(impeller::Vector4, w) == offsetof(ipl_vector4_t, w));
static_assert(
    std::is_same_v<decltype(impeller::Vector4::x), decltype(ipl_vector4_t::x)>);
static_assert(
    std::is_same_v<decltype(impeller::Vector4::y), decltype(ipl_vector4_t::y)>);
static_assert(
    std::is_same_v<decltype(impeller::Vector4::z), decltype(ipl_vector4_t::z)>);
static_assert(
    std::is_same_v<decltype(impeller::Vector4::w), decltype(ipl_vector4_t::w)>);
static_assert(__builtin_is_cpp_trivially_relocatable(impeller::Vector4));
static_assert(__builtin_is_cpp_trivially_relocatable(ipl_vector4_t));

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/impeller/geometry/vector.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/impeller/base/flags.h
// ---------------------------------------------------------------------------

// impeller::Flags
static_assert(std::is_standard_layout_v<ipl_flags_t>);
static_assert(std::is_standard_layout_v<impeller::Flags>);
static_assert(sizeof(impeller::Flags) == sizeof(ipl_flags_t));
static_assert(alignof(impeller::Flags) == alignof(ipl_flags_t));
static_assert(offsetof(impeller::Flags, antialiased_lines) ==
              offsetof(ipl_flags_t, antialiased_lines));
static_assert(offsetof(impeller::Flags, use_sdfs) ==
              offsetof(ipl_flags_t, use_sdfs));
static_assert(__is_layout_compatible(impeller::Flags, ipl_flags_t));
static_assert(__builtin_is_cpp_trivially_relocatable(impeller::Flags));
static_assert(__builtin_is_cpp_trivially_relocatable(ipl_flags_t));

static inline void validate(const ipl_flags_t* src) {
  assert(src != nullptr);
  assert(reinterpret_cast<intptr_t>(src) % alignof(ipl_flags_t) == 0);
}

static inline void validate(const impeller::Flags* src) {
  assert(src != nullptr);
  assert(reinterpret_cast<intptr_t>(src) % alignof(impeller::Flags) == 0);
}

[[maybe_unused]] static inline impeller::Flags* transmute(ipl_flags_t* src) {
  validate(src);
  return reinterpret_cast<impeller::Flags*>(src);
}

[[maybe_unused]] static inline const impeller::Flags* transmute(
    const ipl_flags_t* src) {
  validate(src);
  return reinterpret_cast<const impeller::Flags*>(src);
}

[[maybe_unused]] static inline ipl_flags_t* transmute(impeller::Flags* src) {
  validate(src);
  return reinterpret_cast<ipl_flags_t*>(src);
}

[[maybe_unused]] static inline const ipl_flags_t* transmute(
    const impeller::Flags* src) {
  validate(src);
  return reinterpret_cast<const ipl_flags_t*>(src);
}

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/impeller/base/flags.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/impeller/core/formats.h
// ---------------------------------------------------------------------------

static_assert(std::is_same_v<std::underlying_type_t<impeller::WindingOrder>,
                             std::underlying_type_t<ipl_winding_order_t>>);

constexpr bool operator==(impeller::WindingOrder lhs, ipl_winding_order_t rhs) {
  return static_cast<ipl_winding_order_t>(lhs) == rhs;
}

static_assert(impeller::WindingOrder::kClockwise ==
              IPL_WINDING_ORDER_CLOCKWISE);
static_assert(impeller::WindingOrder::kCounterClockwise ==
              IPL_WINDING_ORDER_COUNTER_CLOCKWISE);

[[maybe_unused]] static inline void validate(ipl_winding_order_t src) {
#ifndef NDEBUG
  switch (src) {
    case IPL_WINDING_ORDER_CLOCKWISE:
    case IPL_WINDING_ORDER_COUNTER_CLOCKWISE:
      break;
    default:
      assert(false);
  }
#endif
}

[[maybe_unused]] static inline void validate(impeller::WindingOrder src) {
#ifndef NDEBUG
  switch (src) {
    case impeller::WindingOrder::kClockwise:
    case impeller::WindingOrder::kCounterClockwise:
      break;
    default:
      assert(false);
  }
#endif
}

[[maybe_unused]] static inline impeller::WindingOrder transmute(
    ipl_winding_order_t src) {
  validate(src);
  return static_cast<impeller::WindingOrder>(src);
}

[[maybe_unused]] static inline ipl_winding_order_t transmute(
    impeller::WindingOrder src) {
  validate(src);
  return static_cast<ipl_winding_order_t>(src);
}

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

[[maybe_unused]] static inline void validate(ipl_storage_mode_t src) {
#ifndef NDEBUG
  switch (src) {
    case IPL_STORAGE_MODE_HOST_VISIBLE:
    case IPL_STORAGE_MODE_DEVICE_PRIVATE:
    case IPL_STORAGE_MODE_DEVICE_TRANSIENT:
      break;
    default:
      assert(false);
  }
#endif
}

[[maybe_unused]] static inline void validate(impeller::StorageMode src) {
#ifndef NDEBUG
  switch (src) {
    case impeller::StorageMode::kHostVisible:
    case impeller::StorageMode::kDevicePrivate:
    case impeller::StorageMode::kDeviceTransient:
      break;
    default:
      assert(false);
  }
#endif
}

[[maybe_unused]] static inline impeller::StorageMode transmute(
    ipl_storage_mode_t src) {
  validate(src);
  return static_cast<impeller::StorageMode>(src);
}

[[maybe_unused]] static inline ipl_storage_mode_t transmute(
    impeller::StorageMode src) {
  validate(src);
  return static_cast<ipl_storage_mode_t>(src);
}

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

[[maybe_unused]] static inline void validate(ipl_pixel_format_t src) {
#ifndef NDEBUG
  switch (src) {
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
      assert(false);
  }
#endif
}

[[maybe_unused]] static inline void validate(impeller::PixelFormat src) {
#ifndef NDEBUG
  switch (src) {
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
      assert(false);
  }
#endif
}

[[maybe_unused]] static inline impeller::PixelFormat transmute(
    ipl_pixel_format_t src) {
  validate(src);
  return static_cast<impeller::PixelFormat>(src);
}

[[maybe_unused]] static inline ipl_pixel_format_t transmute(
    impeller::PixelFormat src) {
  validate(src);
  return static_cast<ipl_pixel_format_t>(src);
}

static_assert(std::is_same_v<std::underlying_type_t<impeller::TextureType>,
                             std::underlying_type_t<ipl_texture_type_t>>);

constexpr bool operator==(impeller::TextureType lhs, ipl_texture_type_t rhs) {
  return static_cast<ipl_texture_type_t>(lhs) == rhs;
}

static_assert(impeller::TextureType::kTexture2D == IPL_TEXTURE_TYPE_TEXTURE_2D);
static_assert(impeller::TextureType::kTexture2DMultisample ==
              IPL_TEXTURE_TYPE_TEXTURE_2D_MULTISAMPLE);
static_assert(impeller::TextureType::kTextureCube ==
              IPL_TEXTURE_TYPE_TEXTURE_CUBE);
static_assert(impeller::TextureType::kTextureExternalOES ==
              IPL_TEXTURE_TYPE_TEXTURE_EXTERNAL_OES);

[[maybe_unused]] static inline void validate(ipl_texture_type_t src) {
#ifndef NDEBUG
  switch (src) {
    case IPL_TEXTURE_TYPE_TEXTURE_2D:
    case IPL_TEXTURE_TYPE_TEXTURE_2D_MULTISAMPLE:
    case IPL_TEXTURE_TYPE_TEXTURE_CUBE:
    case IPL_TEXTURE_TYPE_TEXTURE_EXTERNAL_OES:
      break;
    default:
      assert(false);
  }
#endif
}

[[maybe_unused]] static inline void validate(impeller::TextureType src) {
#ifndef NDEBUG
  switch (src) {
    case impeller::TextureType::kTexture2D:
    case impeller::TextureType::kTexture2DMultisample:
    case impeller::TextureType::kTextureCube:
    case impeller::TextureType::kTextureExternalOES:
      break;
    default:
      assert(false);
  }
#endif
}

[[maybe_unused]] static inline impeller::TextureType transmute(
    ipl_texture_type_t src) {
  validate(src);
  return static_cast<impeller::TextureType>(src);
}

[[maybe_unused]] static inline ipl_texture_type_t transmute(
    impeller::TextureType src) {
  validate(src);
  return static_cast<ipl_texture_type_t>(src);
}

static_assert(std::is_same_v<std::underlying_type_t<impeller::SampleCount>,
                             std::underlying_type_t<ipl_sample_count_t>>);

constexpr bool operator==(impeller::SampleCount lhs, ipl_sample_count_t rhs) {
  return static_cast<ipl_sample_count_t>(lhs) == rhs;
}

static_assert(impeller::SampleCount::kCount1 == IPL_SAMPLE_COUNT_COUNT_1);
static_assert(impeller::SampleCount::kCount4 == IPL_SAMPLE_COUNT_COUNT_4);

[[maybe_unused]] static inline void validate(ipl_sample_count_t src) {
#ifndef NDEBUG
  switch (src) {
    case IPL_SAMPLE_COUNT_COUNT_1:
    case IPL_SAMPLE_COUNT_COUNT_4:
      break;
    default:
      assert(false);
  }
#endif
}

[[maybe_unused]] static inline void validate(impeller::SampleCount src) {
#ifndef NDEBUG
  switch (src) {
    case impeller::SampleCount::kCount1:
    case impeller::SampleCount::kCount4:
      break;
    default:
      assert(false);
  }
#endif
}

[[maybe_unused]] static inline impeller::SampleCount transmute(
    ipl_sample_count_t src) {
  validate(src);
  return static_cast<impeller::SampleCount>(src);
}

[[maybe_unused]] static inline ipl_sample_count_t transmute(
    impeller::SampleCount src) {
  validate(src);
  return static_cast<ipl_sample_count_t>(src);
}

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

[[maybe_unused]] static inline void validate(ipl_texture_usage_t src) {
#ifndef NDEBUG
  std::underlying_type_t<ipl_texture_usage_t> src_val = src;
  src_val &= ~IPL_TEXTURE_USAGE_UNKNOWN;
  src_val &= ~IPL_TEXTURE_USAGE_SHADER_READ;
  src_val &= ~IPL_TEXTURE_USAGE_SHADER_WRITE;
  src_val &= ~IPL_TEXTURE_USAGE_RENDER_TARGET;
  assert(!src_val);
#endif
}

[[maybe_unused]] static inline void validate(impeller::TextureUsageMask src) {
#ifndef NDEBUG
  src &= ~impeller::TextureUsage::kUnknown;
  src &= ~impeller::TextureUsage::kShaderRead;
  src &= ~impeller::TextureUsage::kShaderWrite;
  src &= ~impeller::TextureUsage::kRenderTarget;
  assert(!src);
#endif
}

[[maybe_unused]] static inline impeller::TextureUsageMask transmute(
    ipl_texture_usage_t src) {
  validate(src);
  return static_cast<impeller::TextureUsage>(src);
}

[[maybe_unused]] static inline ipl_texture_usage_t transmute(
    impeller::TextureUsageMask src) {
  validate(src);
  return static_cast<ipl_texture_usage_t>(
      static_cast<impeller::TextureUsageMask::MaskType>(src));
}

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/impeller/core/formats.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/impeller/core/range.h
// ---------------------------------------------------------------------------

// impeller::Range
static_assert(std::is_standard_layout_v<impeller::Range>);
static_assert(std::is_standard_layout_v<ipl_range_t>);
static_assert(sizeof(impeller::Range) == sizeof(ipl_range_t));
static_assert(alignof(impeller::Range) == alignof(ipl_range_t));
static_assert(offsetof(impeller::Range, offset) ==
              offsetof(ipl_range_t, offset));
static_assert(offsetof(impeller::Range, length) ==
              offsetof(ipl_range_t, length));
static_assert(std::is_same_v<decltype(impeller::Range::offset),
                             decltype(ipl_range_t::offset)>);
static_assert(std::is_same_v<decltype(impeller::Range::length),
                             decltype(ipl_range_t::length)>);
static_assert(__builtin_is_cpp_trivially_relocatable(impeller::Range));
static_assert(__builtin_is_cpp_trivially_relocatable(ipl_range_t));

static inline void validate(const ipl_range_t* src) {
  assert(src != nullptr);
  assert(reinterpret_cast<intptr_t>(src) % alignof(ipl_range_t) == 0);
}

static inline void validate(const impeller::Range* src) {
  assert(src != nullptr);
  assert(reinterpret_cast<intptr_t>(src) % alignof(impeller::Range) == 0);
}

[[maybe_unused]] static inline impeller::Range* transmute(ipl_range_t* src) {
  validate(src);
  return reinterpret_cast<impeller::Range*>(src);
}

[[maybe_unused]] static inline const impeller::Range* transmute(
    const ipl_range_t* src) {
  validate(src);
  return reinterpret_cast<const impeller::Range*>(src);
}

[[maybe_unused]] static inline ipl_range_t* transmute(impeller::Range* src) {
  validate(src);
  return reinterpret_cast<ipl_range_t*>(src);
}

[[maybe_unused]] static inline const ipl_range_t* transmute(
    const impeller::Range* src) {
  validate(src);
  return reinterpret_cast<const ipl_range_t*>(src);
}

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/impeller/core/range.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/impeller/core/allocator.h
// ---------------------------------------------------------------------------

static_assert(sizeof(std::shared_ptr<impeller::Allocator>) ==
              sizeof(ipl_allocator_t));
static_assert(alignof(std::shared_ptr<impeller::Allocator>) ==
              alignof(ipl_allocator_t));
// Manual check. `__builtin_is_cpp_trivially_relocatable` is overly
// conservative.
// static_assert(__builtin_is_cpp_trivially_relocatable(std::shared_ptr<impeller::Allocator>));
static_assert(__builtin_is_cpp_trivially_relocatable(ipl_allocator_t));

static inline void validate(const ipl_allocator_t* src) {
  assert(src != nullptr);
  assert(reinterpret_cast<intptr_t>(src) % alignof(ipl_allocator_t) == 0);
}

static inline void validate(const std::shared_ptr<impeller::Allocator>* src) {
  assert(src != nullptr);
  assert(reinterpret_cast<intptr_t>(src) %
             alignof(std::shared_ptr<impeller::Allocator>) ==
         0);
}

[[maybe_unused]] static inline std::shared_ptr<impeller::Allocator>* transmute(
    ipl_allocator_t* src) {
  validate(src);
  return reinterpret_cast<std::shared_ptr<impeller::Allocator>*>(src);
}

[[maybe_unused]] static inline const std::shared_ptr<impeller::Allocator>*
transmute(const ipl_allocator_t* src) {
  validate(src);
  return reinterpret_cast<const std::shared_ptr<impeller::Allocator>*>(src);
}

[[maybe_unused]] static inline ipl_allocator_t* transmute(
    std::shared_ptr<impeller::Allocator>* src) {
  validate(src);
  return reinterpret_cast<ipl_allocator_t*>(src);
}

[[maybe_unused]] static inline const ipl_allocator_t* transmute(
    const std::shared_ptr<impeller::Allocator>* src) {
  validate(src);
  return reinterpret_cast<const ipl_allocator_t*>(src);
}

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/impeller/core/allocator.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/impeller/core/buffer_view.h
// ---------------------------------------------------------------------------

// impeller::BufferView

static_assert(std::is_standard_layout_v<impeller::BufferView>);
static_assert(std::is_standard_layout_v<ipl_buffer_view_t>);
static_assert(sizeof(impeller::BufferView) == sizeof(ipl_buffer_view_t));
static_assert(alignof(impeller::BufferView) == alignof(ipl_buffer_view_t));
// Manual check. `__builtin_is_cpp_trivially_relocatable` is overly
// conservative.
// static_assert(__builtin_is_cpp_trivially_relocatable(impeller::BufferView));
static_assert(__builtin_is_cpp_trivially_relocatable(ipl_buffer_view_t));

static inline void validate(const ipl_buffer_view_t* src) {
  assert(src != nullptr);
  assert(reinterpret_cast<intptr_t>(src) % alignof(ipl_buffer_view_t) == 0);
}

static inline void validate(const impeller::BufferView* src) {
  assert(src != nullptr);
  assert(reinterpret_cast<intptr_t>(src) % alignof(impeller::BufferView) == 0);
}

[[maybe_unused]] static inline impeller::BufferView* transmute(
    ipl_buffer_view_t* src) {
  validate(src);
  return reinterpret_cast<impeller::BufferView*>(src);
}

[[maybe_unused]] static inline const impeller::BufferView* transmute(
    const ipl_buffer_view_t* src) {
  validate(src);
  return reinterpret_cast<const impeller::BufferView*>(src);
}

[[maybe_unused]] static inline ipl_buffer_view_t* transmute(
    impeller::BufferView* src) {
  validate(src);
  return reinterpret_cast<ipl_buffer_view_t*>(src);
}

[[maybe_unused]] static inline const ipl_buffer_view_t* transmute(
    const impeller::BufferView* src) {
  validate(src);
  return reinterpret_cast<const ipl_buffer_view_t*>(src);
}

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/impeller/core/buffer_view.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/impeller/core/device_buffer.h
// ---------------------------------------------------------------------------

// std::shared_ptr<impeller::DeviceBuffer>
static_assert(sizeof(std::shared_ptr<impeller::DeviceBuffer>) ==
              sizeof(ipl_device_buffer_t));
static_assert(alignof(std::shared_ptr<impeller::DeviceBuffer>) ==
              alignof(ipl_device_buffer_t));
// Manual check. `__builtin_is_cpp_trivially_relocatable` is overly
// conservative.
// static_assert(__builtin_is_cpp_trivially_relocatable(std::shared_ptr<impeller::DeviceBuffer>));
static_assert(__builtin_is_cpp_trivially_relocatable(ipl_device_buffer_t));

static inline void validate(const ipl_device_buffer_t* src) {
  assert(src != nullptr);
  assert(reinterpret_cast<intptr_t>(src) % alignof(ipl_device_buffer_t) == 0);
}

static inline void validate(
    const std::shared_ptr<impeller::DeviceBuffer>* src) {
  assert(src != nullptr);
  assert(reinterpret_cast<intptr_t>(src) %
             alignof(std::shared_ptr<impeller::DeviceBuffer>) ==
         0);
}

[[maybe_unused]] static inline std::shared_ptr<impeller::DeviceBuffer>*
transmute(ipl_device_buffer_t* src) {
  validate(src);
  return reinterpret_cast<std::shared_ptr<impeller::DeviceBuffer>*>(src);
}

[[maybe_unused]] static inline const std::shared_ptr<impeller::DeviceBuffer>*
transmute(const ipl_device_buffer_t* src) {
  validate(src);
  return reinterpret_cast<const std::shared_ptr<impeller::DeviceBuffer>*>(src);
}

[[maybe_unused]] static inline ipl_device_buffer_t* transmute(
    std::shared_ptr<impeller::DeviceBuffer>* src) {
  validate(src);
  return reinterpret_cast<ipl_device_buffer_t*>(src);
}

[[maybe_unused]] static inline const ipl_device_buffer_t* transmute(
    const std::shared_ptr<impeller::DeviceBuffer>* src) {
  validate(src);
  return reinterpret_cast<const ipl_device_buffer_t*>(src);
}

// std::shared_ptr<const impeller::DeviceBuffer>
static_assert(sizeof(std::shared_ptr<const impeller::DeviceBuffer>) ==
              sizeof(ipl_const_device_buffer_t));
static_assert(alignof(std::shared_ptr<const impeller::DeviceBuffer>) ==
              alignof(ipl_const_device_buffer_t));
// Manual check. `__builtin_is_cpp_trivially_relocatable` is overly
// conservative.
// static_assert(__builtin_is_cpp_trivially_relocatable(std::shared_ptr<const
// impeller::DeviceBuffer>));
static_assert(
    __builtin_is_cpp_trivially_relocatable(ipl_const_device_buffer_t));

static inline void validate(const ipl_const_device_buffer_t* src) {
  assert(src != nullptr);
  assert(reinterpret_cast<intptr_t>(src) % alignof(ipl_const_device_buffer_t) ==
         0);
}

static inline void validate(
    const std::shared_ptr<const impeller::DeviceBuffer>* src) {
  assert(src != nullptr);
  assert(reinterpret_cast<intptr_t>(src) %
             alignof(std::shared_ptr<const impeller::DeviceBuffer>) ==
         0);
}

[[maybe_unused]] static inline std::shared_ptr<const impeller::DeviceBuffer>*
transmute(ipl_const_device_buffer_t* src) {
  validate(src);
  return reinterpret_cast<std::shared_ptr<const impeller::DeviceBuffer>*>(src);
}

[[maybe_unused]] static inline const std::shared_ptr<
    const impeller::DeviceBuffer>*
transmute(const ipl_const_device_buffer_t* src) {
  validate(src);
  return reinterpret_cast<const std::shared_ptr<const impeller::DeviceBuffer>*>(
      src);
}

[[maybe_unused]] static inline ipl_const_device_buffer_t* transmute(
    std::shared_ptr<const impeller::DeviceBuffer>* src) {
  validate(src);
  return reinterpret_cast<ipl_const_device_buffer_t*>(src);
}

[[maybe_unused]] static inline const ipl_const_device_buffer_t* transmute(
    const std::shared_ptr<const impeller::DeviceBuffer>* src) {
  validate(src);
  return reinterpret_cast<const ipl_const_device_buffer_t*>(src);
}

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/impeller/core/device_buffer.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/impeller/core/device_buffer_descriptor.h
// ---------------------------------------------------------------------------

// impeller::DeviceBufferDescriptor
static_assert(std::is_standard_layout_v<impeller::DeviceBufferDescriptor>);
static_assert(std::is_standard_layout_v<ipl_device_buffer_descriptor_t>);
static_assert(sizeof(impeller::DeviceBufferDescriptor) ==
              sizeof(ipl_device_buffer_descriptor_t));
static_assert(alignof(impeller::DeviceBufferDescriptor) ==
              alignof(ipl_device_buffer_descriptor_t));
static_assert(offsetof(impeller::DeviceBufferDescriptor, storage_mode) ==
              offsetof(ipl_device_buffer_descriptor_t, storage_mode));
static_assert(offsetof(impeller::DeviceBufferDescriptor, size) ==
              offsetof(ipl_device_buffer_descriptor_t, size));
static_assert(offsetof(impeller::DeviceBufferDescriptor, readback) ==
              offsetof(ipl_device_buffer_descriptor_t, readback));
static_assert(__is_layout_compatible(impeller::DeviceBufferDescriptor,
                                     ipl_device_buffer_descriptor_t));
static_assert(
    __builtin_is_cpp_trivially_relocatable(impeller::DeviceBufferDescriptor));
static_assert(
    __builtin_is_cpp_trivially_relocatable(ipl_device_buffer_descriptor_t));

static inline void validate(const ipl_device_buffer_descriptor_t* src) {
  assert(src != nullptr);
  assert(reinterpret_cast<intptr_t>(src) %
             alignof(ipl_device_buffer_descriptor_t) ==
         0);
}

static inline void validate(const impeller::DeviceBufferDescriptor* src) {
  assert(src != nullptr);
  assert(reinterpret_cast<intptr_t>(src) %
             alignof(impeller::DeviceBufferDescriptor) ==
         0);
}

[[maybe_unused]] static inline impeller::DeviceBufferDescriptor* transmute(
    ipl_device_buffer_descriptor_t* src) {
  validate(src);
  return reinterpret_cast<impeller::DeviceBufferDescriptor*>(src);
}

[[maybe_unused]] static inline const impeller::DeviceBufferDescriptor*
transmute(const ipl_device_buffer_descriptor_t* src) {
  validate(src);
  return reinterpret_cast<const impeller::DeviceBufferDescriptor*>(src);
}

[[maybe_unused]] static inline ipl_device_buffer_descriptor_t* transmute(
    impeller::DeviceBufferDescriptor* src) {
  validate(src);
  return reinterpret_cast<ipl_device_buffer_descriptor_t*>(src);
}

[[maybe_unused]] static inline const ipl_device_buffer_descriptor_t* transmute(
    const impeller::DeviceBufferDescriptor* src) {
  validate(src);
  return reinterpret_cast<const ipl_device_buffer_descriptor_t*>(src);
}

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/impeller/core/device_buffer_descriptor.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/impeller/core/host_buffer.h
// ---------------------------------------------------------------------------

// std::shared_ptr<impeller::HostBuffer>
static_assert(sizeof(std::shared_ptr<impeller::HostBuffer>) ==
              sizeof(ipl_host_buffer_t));
static_assert(alignof(std::shared_ptr<impeller::HostBuffer>) ==
              alignof(ipl_host_buffer_t));
// Manual check. `__builtin_is_cpp_trivially_relocatable` is overly
// conservative.
// static_assert(__builtin_is_cpp_trivially_relocatable(std::shared_ptr<impeller::HostBuffer>));
static_assert(__builtin_is_cpp_trivially_relocatable(ipl_host_buffer_t));

static inline void validate(const ipl_host_buffer_t* src) {
  assert(src != nullptr);
  assert(reinterpret_cast<intptr_t>(src) % alignof(ipl_host_buffer_t) == 0);
}

static inline void validate(const std::shared_ptr<impeller::HostBuffer>* src) {
  assert(src != nullptr);
  assert(reinterpret_cast<intptr_t>(src) %
             alignof(std::shared_ptr<impeller::HostBuffer>) ==
         0);
}

[[maybe_unused]] static inline std::shared_ptr<impeller::HostBuffer>* transmute(
    ipl_host_buffer_t* src) {
  validate(src);
  return reinterpret_cast<std::shared_ptr<impeller::HostBuffer>*>(src);
}

[[maybe_unused]] static inline const std::shared_ptr<impeller::HostBuffer>*
transmute(const ipl_host_buffer_t* src) {
  validate(src);
  return reinterpret_cast<const std::shared_ptr<impeller::HostBuffer>*>(src);
}

[[maybe_unused]] static inline ipl_host_buffer_t* transmute(
    std::shared_ptr<impeller::HostBuffer>* src) {
  validate(src);
  return reinterpret_cast<ipl_host_buffer_t*>(src);
}

[[maybe_unused]] static inline const ipl_host_buffer_t* transmute(
    const std::shared_ptr<impeller::HostBuffer>* src) {
  validate(src);
  return reinterpret_cast<const ipl_host_buffer_t*>(src);
}

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/impeller/core/host_buffer.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/impeller/core/texture.h
// ---------------------------------------------------------------------------

// std::shared_ptr<impeller::Texture>
static_assert(sizeof(std::shared_ptr<impeller::Texture>) ==
              sizeof(ipl_texture_t));
static_assert(alignof(std::shared_ptr<impeller::Texture>) ==
              alignof(ipl_texture_t));
// Manual check. `__builtin_is_cpp_trivially_relocatable` is overly
// conservative.
// static_assert(__builtin_is_cpp_trivially_relocatable(std::shared_ptr<impeller::Texture>));
static_assert(__builtin_is_cpp_trivially_relocatable(ipl_texture_t));

static inline void validate(const ipl_texture_t* src) {
  assert(src != nullptr);
  assert(reinterpret_cast<intptr_t>(src) % alignof(ipl_texture_t) == 0);
}

static inline void validate(const std::shared_ptr<impeller::Texture>* src) {
  assert(src != nullptr);
  assert(reinterpret_cast<intptr_t>(src) %
             alignof(std::shared_ptr<impeller::Texture>) ==
         0);
}

[[maybe_unused]] static inline std::shared_ptr<impeller::Texture>* transmute(
    ipl_texture_t* src) {
  validate(src);
  return reinterpret_cast<std::shared_ptr<impeller::Texture>*>(src);
}

[[maybe_unused]] static inline const std::shared_ptr<impeller::Texture>*
transmute(const ipl_texture_t* src) {
  validate(src);
  return reinterpret_cast<const std::shared_ptr<impeller::Texture>*>(src);
}

[[maybe_unused]] static inline ipl_texture_t* transmute(
    std::shared_ptr<impeller::Texture>* src) {
  validate(src);
  return reinterpret_cast<ipl_texture_t*>(src);
}

[[maybe_unused]] static inline const ipl_texture_t* transmute(
    const std::shared_ptr<impeller::Texture>* src) {
  validate(src);
  return reinterpret_cast<const ipl_texture_t*>(src);
}

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/impeller/core/texture.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/impeller/core/texture_descriptor.h
// ---------------------------------------------------------------------------

// impeller::CompressionType
static_assert(std::is_same_v<std::underlying_type_t<impeller::CompressionType>,
                             std::underlying_type_t<ipl_compression_type_t>>);

constexpr bool operator==(impeller::CompressionType lhs,
                          ipl_compression_type_t rhs) {
  return static_cast<ipl_compression_type_t>(lhs) == rhs;
}

static_assert(impeller::CompressionType::kLossless ==
              IPL_COMPRESSION_TYPE_LOSSLESS);
static_assert(impeller::CompressionType::kLossy == IPL_COMPRESSION_TYPE_LOSSY);

[[maybe_unused]] static inline void validate(ipl_compression_type_t src) {
#ifndef NDEBUG
  switch (src) {
    case IPL_COMPRESSION_TYPE_LOSSLESS:
    case IPL_COMPRESSION_TYPE_LOSSY:
      break;
    default:
      assert(false);
  }
#endif
}

[[maybe_unused]] static inline void validate(impeller::CompressionType src) {
#ifndef NDEBUG
  switch (src) {
    case impeller::CompressionType::kLossless:
    case impeller::CompressionType::kLossy:
      break;
    default:
      assert(false);
  }
#endif
}

[[maybe_unused]] static inline impeller::CompressionType transmute(
    ipl_compression_type_t src) {
  validate(src);
  return static_cast<impeller::CompressionType>(src);
}

[[maybe_unused]] static inline ipl_compression_type_t transmute(
    impeller::CompressionType src) {
  validate(src);
  return static_cast<ipl_compression_type_t>(src);
}

// impeller::TextureDescriptor
static_assert(std::is_standard_layout_v<impeller::TextureDescriptor>);
static_assert(std::is_standard_layout_v<ipl_texture_descriptor_t>);
static_assert(sizeof(impeller::TextureDescriptor) ==
              sizeof(ipl_texture_descriptor_t));
static_assert(alignof(impeller::TextureDescriptor) ==
              alignof(ipl_texture_descriptor_t));
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
static_assert(
    std::is_same_v<std::underlying_type_t<
                       decltype(impeller::TextureDescriptor::storage_mode)>,
                   std::underlying_type_t<
                       decltype(ipl_texture_descriptor_t::storage_mode)>>);
static_assert(
    std::is_same_v<
        std::underlying_type_t<decltype(impeller::TextureDescriptor::type)>,
        std::underlying_type_t<decltype(ipl_texture_descriptor_t::type)>>);
static_assert(
    std::is_same_v<
        std::underlying_type_t<decltype(impeller::TextureDescriptor::format)>,
        std::underlying_type_t<decltype(ipl_texture_descriptor_t::format)>>);
static_assert(
    __is_layout_compatible(decltype(impeller::TextureDescriptor::size),
                           decltype(ipl_texture_descriptor_t::size)));
static_assert(std::is_same_v<decltype(impeller::TextureDescriptor::mip_count),
                             decltype(ipl_texture_descriptor_t::mip_count)>);
static_assert(
    std::is_same_v<
        std::underlying_type_t<
            decltype(impeller::TextureDescriptor::usage)::EnumType>,
        std::underlying_type_t<decltype(ipl_texture_descriptor_t::usage)>>);
static_assert(
    std::is_same_v<std::underlying_type_t<
                       decltype(impeller::TextureDescriptor::sample_count)>,
                   std::underlying_type_t<
                       decltype(ipl_texture_descriptor_t::sample_count)>>);
static_assert(
    std::is_same_v<std::underlying_type_t<
                       decltype(impeller::TextureDescriptor::compression_type)>,
                   std::underlying_type_t<
                       decltype(ipl_texture_descriptor_t::compression_type)>>);
static_assert(
    __builtin_is_cpp_trivially_relocatable(impeller::TextureDescriptor));
static_assert(__builtin_is_cpp_trivially_relocatable(ipl_texture_descriptor_t));

static inline void validate(const ipl_texture_descriptor_t* src) {
  assert(src != nullptr);
  assert(reinterpret_cast<intptr_t>(src) % alignof(ipl_texture_descriptor_t) ==
         0);
}

static inline void validate(const impeller::TextureDescriptor* src) {
  assert(src != nullptr);
  assert(reinterpret_cast<intptr_t>(src) %
             alignof(impeller::TextureDescriptor) ==
         0);
}

[[maybe_unused]] static inline impeller::TextureDescriptor* transmute(
    ipl_texture_descriptor_t* src) {
  validate(src);
  return reinterpret_cast<impeller::TextureDescriptor*>(src);
}

[[maybe_unused]] static inline const impeller::TextureDescriptor* transmute(
    const ipl_texture_descriptor_t* src) {
  validate(src);
  return reinterpret_cast<const impeller::TextureDescriptor*>(src);
}

[[maybe_unused]] static inline ipl_texture_descriptor_t* transmute(
    impeller::TextureDescriptor* src) {
  validate(src);
  return reinterpret_cast<ipl_texture_descriptor_t*>(src);
}

[[maybe_unused]] static inline const ipl_texture_descriptor_t* transmute(
    const impeller::TextureDescriptor* src) {
  validate(src);
  return reinterpret_cast<const ipl_texture_descriptor_t*>(src);
}

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/impeller/core/texture_descriptor.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/impeller/core/vertex_buffer.h
// ---------------------------------------------------------------------------

// impeller::VertexBuffer
static_assert(std::is_standard_layout_v<impeller::VertexBuffer>);
static_assert(std::is_standard_layout_v<ipl_vertex_buffer_t>);
static_assert(sizeof(impeller::VertexBuffer) == sizeof(ipl_vertex_buffer_t));
static_assert(alignof(impeller::VertexBuffer) == alignof(ipl_vertex_buffer_t));
static_assert(offsetof(impeller::VertexBuffer, vertex_buffer) ==
              offsetof(ipl_vertex_buffer_t, vertex_buffer));
static_assert(offsetof(impeller::VertexBuffer, index_buffer) ==
              offsetof(ipl_vertex_buffer_t, index_buffer));
static_assert(offsetof(impeller::VertexBuffer, vertex_count) ==
              offsetof(ipl_vertex_buffer_t, vertex_count));
static_assert(offsetof(impeller::VertexBuffer, index_type) ==
              offsetof(ipl_vertex_buffer_t, index_type));
// Manual check. `__builtin_is_cpp_trivially_relocatable` is overly
// conservative.
// static_assert(__builtin_is_cpp_trivially_relocatable(impeller::VertexBuffer));
static_assert(__builtin_is_cpp_trivially_relocatable(ipl_vertex_buffer_t));

static inline void validate(const ipl_vertex_buffer_t* src) {
  assert(src != nullptr);
  assert(reinterpret_cast<intptr_t>(src) % alignof(ipl_vertex_buffer_t) == 0);
}

static inline void validate(const impeller::VertexBuffer* src) {
  assert(src != nullptr);
  assert(reinterpret_cast<intptr_t>(src) % alignof(impeller::VertexBuffer) ==
         0);
}

[[maybe_unused]] static inline impeller::VertexBuffer* transmute(
    ipl_vertex_buffer_t* src) {
  validate(src);
  return reinterpret_cast<impeller::VertexBuffer*>(src);
}

[[maybe_unused]] static inline const impeller::VertexBuffer* transmute(
    const ipl_vertex_buffer_t* src) {
  validate(src);
  return reinterpret_cast<const impeller::VertexBuffer*>(src);
}

[[maybe_unused]] static inline ipl_vertex_buffer_t* transmute(
    impeller::VertexBuffer* src) {
  validate(src);
  return reinterpret_cast<ipl_vertex_buffer_t*>(src);
}

[[maybe_unused]] static inline const ipl_vertex_buffer_t* transmute(
    const impeller::VertexBuffer* src) {
  validate(src);
  return reinterpret_cast<const ipl_vertex_buffer_t*>(src);
}

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/impeller/core/vertex_buffer.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/display_list/dl_blend_mode.h
// ---------------------------------------------------------------------------

static_assert(std::is_same_v<std::underlying_type_t<flutter::DlBlendMode>,
                             std::underlying_type_t<ipl_blend_mode_t>>);

constexpr bool operator==(flutter::DlBlendMode lhs, ipl_blend_mode_t rhs) {
  return static_cast<ipl_blend_mode_t>(lhs) == rhs;
}

static_assert(flutter::DlBlendMode::kClear == IPL_BLEND_MODE_CLEAR);
static_assert(flutter::DlBlendMode::kSrc == IPL_BLEND_MODE_SRC);
static_assert(flutter::DlBlendMode::kDst == IPL_BLEND_MODE_DST);
static_assert(flutter::DlBlendMode::kSrcOver == IPL_BLEND_MODE_SRC_OVER);
static_assert(flutter::DlBlendMode::kDstOver == IPL_BLEND_MODE_DST_OVER);
static_assert(flutter::DlBlendMode::kSrcIn == IPL_BLEND_MODE_SRC_IN);
static_assert(flutter::DlBlendMode::kDstIn == IPL_BLEND_MODE_DST_IN);
static_assert(flutter::DlBlendMode::kSrcOut == IPL_BLEND_MODE_SRC_OUT);
static_assert(flutter::DlBlendMode::kDstOut == IPL_BLEND_MODE_DST_OUT);
static_assert(flutter::DlBlendMode::kSrcATop == IPL_BLEND_MODE_SRC_A_TOP);
static_assert(flutter::DlBlendMode::kDstATop == IPL_BLEND_MODE_DST_A_TOP);
static_assert(flutter::DlBlendMode::kXor == IPL_BLEND_MODE_XOR);
static_assert(flutter::DlBlendMode::kPlus == IPL_BLEND_MODE_PLUS);
static_assert(flutter::DlBlendMode::kModulate == IPL_BLEND_MODE_MODULATE);
static_assert(flutter::DlBlendMode::kScreen == IPL_BLEND_MODE_SCREEN);
static_assert(flutter::DlBlendMode::kOverlay == IPL_BLEND_MODE_OVERLAY);
static_assert(flutter::DlBlendMode::kDarken == IPL_BLEND_MODE_DARKEN);
static_assert(flutter::DlBlendMode::kLighten == IPL_BLEND_MODE_LIGHTEN);
static_assert(flutter::DlBlendMode::kColorDodge == IPL_BLEND_MODE_COLOR_DODGE);
static_assert(flutter::DlBlendMode::kColorBurn == IPL_BLEND_MODE_COLOR_BURN);
static_assert(flutter::DlBlendMode::kHardLight == IPL_BLEND_MODE_HARD_LIGHT);
static_assert(flutter::DlBlendMode::kSoftLight == IPL_BLEND_MODE_SOFT_LIGHT);
static_assert(flutter::DlBlendMode::kDifference == IPL_BLEND_MODE_DIFFERENCE);
static_assert(flutter::DlBlendMode::kExclusion == IPL_BLEND_MODE_EXCLUSION);
static_assert(flutter::DlBlendMode::kMultiply == IPL_BLEND_MODE_MULTIPLY);
static_assert(flutter::DlBlendMode::kHue == IPL_BLEND_MODE_HUE);
static_assert(flutter::DlBlendMode::kSaturation == IPL_BLEND_MODE_SATURATION);
static_assert(flutter::DlBlendMode::kColor == IPL_BLEND_MODE_COLOR);
static_assert(flutter::DlBlendMode::kLuminosity == IPL_BLEND_MODE_LUMINOSITY);

[[maybe_unused]] static inline void validate(ipl_blend_mode_t src) {
#ifndef NDEBUG
  switch (src) {
    case IPL_BLEND_MODE_CLEAR:
    case IPL_BLEND_MODE_SRC:
    case IPL_BLEND_MODE_DST:
    case IPL_BLEND_MODE_SRC_OVER:
    case IPL_BLEND_MODE_DST_OVER:
    case IPL_BLEND_MODE_SRC_IN:
    case IPL_BLEND_MODE_DST_IN:
    case IPL_BLEND_MODE_SRC_OUT:
    case IPL_BLEND_MODE_DST_OUT:
    case IPL_BLEND_MODE_SRC_A_TOP:
    case IPL_BLEND_MODE_DST_A_TOP:
    case IPL_BLEND_MODE_XOR:
    case IPL_BLEND_MODE_PLUS:
    case IPL_BLEND_MODE_MODULATE:
    case IPL_BLEND_MODE_SCREEN:
    case IPL_BLEND_MODE_OVERLAY:
    case IPL_BLEND_MODE_DARKEN:
    case IPL_BLEND_MODE_LIGHTEN:
    case IPL_BLEND_MODE_COLOR_DODGE:
    case IPL_BLEND_MODE_COLOR_BURN:
    case IPL_BLEND_MODE_HARD_LIGHT:
    case IPL_BLEND_MODE_SOFT_LIGHT:
    case IPL_BLEND_MODE_DIFFERENCE:
    case IPL_BLEND_MODE_EXCLUSION:
    case IPL_BLEND_MODE_MULTIPLY:
    case IPL_BLEND_MODE_HUE:
    case IPL_BLEND_MODE_SATURATION:
    case IPL_BLEND_MODE_COLOR:
    case IPL_BLEND_MODE_LUMINOSITY:
      break;
    default:
      assert(false);
  }
#endif
}

[[maybe_unused]] static inline void validate(flutter::DlBlendMode src) {
#ifndef NDEBUG
  switch (src) {
    case flutter::DlBlendMode::kClear:
    case flutter::DlBlendMode::kSrc:
    case flutter::DlBlendMode::kDst:
    case flutter::DlBlendMode::kSrcOver:
    case flutter::DlBlendMode::kDstOver:
    case flutter::DlBlendMode::kSrcIn:
    case flutter::DlBlendMode::kDstIn:
    case flutter::DlBlendMode::kSrcOut:
    case flutter::DlBlendMode::kDstOut:
    case flutter::DlBlendMode::kSrcATop:
    case flutter::DlBlendMode::kDstATop:
    case flutter::DlBlendMode::kXor:
    case flutter::DlBlendMode::kPlus:
    case flutter::DlBlendMode::kModulate:
    case flutter::DlBlendMode::kScreen:
    case flutter::DlBlendMode::kOverlay:
    case flutter::DlBlendMode::kDarken:
    case flutter::DlBlendMode::kLighten:
    case flutter::DlBlendMode::kColorDodge:
    case flutter::DlBlendMode::kColorBurn:
    case flutter::DlBlendMode::kHardLight:
    case flutter::DlBlendMode::kSoftLight:
    case flutter::DlBlendMode::kDifference:
    case flutter::DlBlendMode::kExclusion:
    case flutter::DlBlendMode::kMultiply:
    case flutter::DlBlendMode::kHue:
    case flutter::DlBlendMode::kSaturation:
    case flutter::DlBlendMode::kColor:
    case flutter::DlBlendMode::kLuminosity:
      break;
    default:
      assert(false);
  }
#endif
}

[[maybe_unused]] static inline flutter::DlBlendMode transmute(
    ipl_blend_mode_t src) {
  validate(src);
  return static_cast<flutter::DlBlendMode>(src);
}

[[maybe_unused]] static inline ipl_blend_mode_t transmute(
    flutter::DlBlendMode src) {
  validate(src);
  return static_cast<ipl_blend_mode_t>(src);
}

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/display_list/dl_blend_mode.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/display_list/dl_color.h
// ---------------------------------------------------------------------------

static_assert(std::is_same_v<std::underlying_type_t<flutter::DlColorSpace>,
                             std::underlying_type_t<ipl_color_space_t>>);

constexpr bool operator==(flutter::DlColorSpace lhs, ipl_color_space_t rhs) {
  return static_cast<ipl_color_space_t>(lhs) == rhs;
}

static_assert(flutter::DlColorSpace::kSRGB == IPL_COLOR_SPACE_SRGB);
static_assert(flutter::DlColorSpace::kExtendedSRGB ==
              IPL_COLOR_SPACE_EXTENDED_SRGB);
static_assert(flutter::DlColorSpace::kDisplayP3 == IPL_COLOR_SPACE_DISPLAY_P3);

[[maybe_unused]] static inline void validate(ipl_color_space_t src) {
#ifndef NDEBUG
  switch (src) {
    case IPL_COLOR_SPACE_SRGB:
    case IPL_COLOR_SPACE_EXTENDED_SRGB:
    case IPL_COLOR_SPACE_DISPLAY_P3:
      break;
    default:
      assert(false);
  }
#endif
}

[[maybe_unused]] static inline void validate(flutter::DlColorSpace src) {
#ifndef NDEBUG
  switch (src) {
    case flutter::DlColorSpace::kSRGB:
    case flutter::DlColorSpace::kExtendedSRGB:
    case flutter::DlColorSpace::kDisplayP3:
      break;
    default:
      assert(false);
  }
#endif
}

[[maybe_unused]] static inline flutter::DlColorSpace transmute(
    ipl_color_space_t src) {
  validate(src);
  return static_cast<flutter::DlColorSpace>(src);
}

[[maybe_unused]] static inline ipl_color_space_t transmute(
    flutter::DlColorSpace src) {
  validate(src);
  return static_cast<ipl_color_space_t>(src);
}

// flutter::DlColor
static_assert(std::is_standard_layout_v<flutter::DlColor>);
static_assert(std::is_standard_layout_v<ipl_color_t>);
static_assert(sizeof(flutter::DlColor) == sizeof(ipl_color_t));
static_assert(alignof(flutter::DlColor) == alignof(ipl_color_t));
static_assert(__is_layout_compatible(flutter::DlColor, ipl_color_t));
static_assert(__builtin_is_cpp_trivially_relocatable(flutter::DlColor));
static_assert(__builtin_is_cpp_trivially_relocatable(ipl_color_t));

static inline void validate(const ipl_color_t* src) {
  assert(src != nullptr);
  assert(reinterpret_cast<intptr_t>(src) % alignof(ipl_color_t) == 0);
}

static inline void validate(const flutter::DlColor* src) {
  assert(src != nullptr);
  assert(reinterpret_cast<intptr_t>(src) % alignof(flutter::DlColor) == 0);
}

[[maybe_unused]] static inline flutter::DlColor* transmute(ipl_color_t* src) {
  validate(src);
  return reinterpret_cast<flutter::DlColor*>(src);
}

[[maybe_unused]] static inline const flutter::DlColor* transmute(
    const ipl_color_t* src) {
  validate(src);
  return reinterpret_cast<const flutter::DlColor*>(src);
}

[[maybe_unused]] static inline ipl_color_t* transmute(flutter::DlColor* src) {
  validate(src);
  return reinterpret_cast<ipl_color_t*>(src);
}

[[maybe_unused]] static inline const ipl_color_t* transmute(
    const flutter::DlColor* src) {
  validate(src);
  return reinterpret_cast<const ipl_color_t*>(src);
}

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/display_list/dl_color.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/display_list/dl_types.h
// ---------------------------------------------------------------------------

static_assert(std::is_same_v<std::underlying_type_t<flutter::DlClipOp>,
                             std::underlying_type_t<ipl_clip_op_t>>);

constexpr bool operator==(flutter::DlClipOp lhs, ipl_clip_op_t rhs) {
  return static_cast<ipl_clip_op_t>(lhs) == rhs;
}

static_assert(flutter::DlClipOp::kDifference == IPL_CLIP_OP_DIFFERENCE);
static_assert(flutter::DlClipOp::kIntersect == IPL_CLIP_OP_INTERSECT);

[[maybe_unused]] static inline void validate(ipl_clip_op_t src) {
#ifndef NDEBUG
  switch (src) {
    case IPL_CLIP_OP_DIFFERENCE:
    case IPL_CLIP_OP_INTERSECT:
      break;
    default:
      assert(false);
  }
#endif
}

[[maybe_unused]] static inline void validate(flutter::DlClipOp src) {
#ifndef NDEBUG
  switch (src) {
    case flutter::DlClipOp::kDifference:
    case flutter::DlClipOp::kIntersect:
      break;
    default:
      assert(false);
  }
#endif
}

[[maybe_unused]] static inline flutter::DlClipOp transmute(ipl_clip_op_t src) {
  validate(src);
  return static_cast<flutter::DlClipOp>(src);
}

[[maybe_unused]] static inline ipl_clip_op_t transmute(flutter::DlClipOp src) {
  validate(src);
  return static_cast<ipl_clip_op_t>(src);
}

static_assert(std::is_same_v<std::underlying_type_t<flutter::DlPointMode>,
                             std::underlying_type_t<ipl_point_mode_t>>);

constexpr bool operator==(flutter::DlPointMode lhs, ipl_point_mode_t rhs) {
  return static_cast<ipl_point_mode_t>(lhs) == rhs;
}

static_assert(flutter::DlPointMode::kPoints == IPL_POINT_MODE_POINTS);
static_assert(flutter::DlPointMode::kLines == IPL_POINT_MODE_LINES);
static_assert(flutter::DlPointMode::kPolygon == IPL_POINT_MODE_POLYGON);

[[maybe_unused]] static inline void validate(ipl_point_mode_t src) {
#ifndef NDEBUG
  switch (src) {
    case IPL_POINT_MODE_POINTS:
    case IPL_POINT_MODE_LINES:
    case IPL_POINT_MODE_POLYGON:
      break;
    default:
      assert(false);
  }
#endif
}

[[maybe_unused]] static inline void validate(flutter::DlPointMode src) {
#ifndef NDEBUG
  switch (src) {
    case flutter::DlPointMode::kPoints:
    case flutter::DlPointMode::kLines:
    case flutter::DlPointMode::kPolygon:
      break;
    default:
      assert(false);
  }
#endif
}

[[maybe_unused]] static inline flutter::DlPointMode transmute(
    ipl_point_mode_t src) {
  validate(src);
  return static_cast<flutter::DlPointMode>(src);
}

[[maybe_unused]] static inline ipl_point_mode_t transmute(
    flutter::DlPointMode src) {
  validate(src);
  return static_cast<ipl_point_mode_t>(src);
}

static_assert(
    std::is_same_v<std::underlying_type_t<flutter::DlSrcRectConstraint>,
                   std::underlying_type_t<ipl_src_rect_constraint_t>>);

constexpr bool operator==(flutter::DlSrcRectConstraint lhs,
                          ipl_src_rect_constraint_t rhs) {
  return static_cast<ipl_src_rect_constraint_t>(lhs) == rhs;
}

static_assert(flutter::DlSrcRectConstraint::kStrict ==
              IPL_SRC_RECT_CONSTRAINT_STRICT);
static_assert(flutter::DlSrcRectConstraint::kFast ==
              IPL_SRC_RECT_CONSTRAINT_FAST);

[[maybe_unused]] static inline void validate(ipl_src_rect_constraint_t src) {
#ifndef NDEBUG
  switch (src) {
    case IPL_SRC_RECT_CONSTRAINT_STRICT:
    case IPL_SRC_RECT_CONSTRAINT_FAST:
      break;
    default:
      assert(false);
  }
#endif
}

[[maybe_unused]] static inline void validate(flutter::DlSrcRectConstraint src) {
#ifndef NDEBUG
  switch (src) {
    case flutter::DlSrcRectConstraint::kStrict:
    case flutter::DlSrcRectConstraint::kFast:
      break;
    default:
      assert(false);
  }
#endif
}

[[maybe_unused]] static inline flutter::DlSrcRectConstraint transmute(
    ipl_src_rect_constraint_t src) {
  validate(src);
  return static_cast<flutter::DlSrcRectConstraint>(src);
}

[[maybe_unused]] static inline ipl_src_rect_constraint_t transmute(
    flutter::DlSrcRectConstraint src) {
  validate(src);
  return static_cast<ipl_src_rect_constraint_t>(src);
}

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/display_list/dl_types.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/display_list/dl_sampling_options.h
// ---------------------------------------------------------------------------

static_assert(std::is_same_v<std::underlying_type_t<flutter::DlFilterMode>,
                             std::underlying_type_t<ipl_filter_mode_t>>);

constexpr bool operator==(flutter::DlFilterMode lhs, ipl_filter_mode_t rhs) {
  return static_cast<ipl_filter_mode_t>(lhs) == rhs;
}

static_assert(flutter::DlFilterMode::kNearest == IPL_FILTER_MODE_NEAREST);
static_assert(flutter::DlFilterMode::kLinear == IPL_FILTER_MODE_LINEAR);

[[maybe_unused]] static inline void validate(ipl_filter_mode_t src) {
#ifndef NDEBUG
  switch (src) {
    case IPL_FILTER_MODE_NEAREST:
    case IPL_FILTER_MODE_LINEAR:
      break;
    default:
      assert(false);
  }
#endif
}

[[maybe_unused]] static inline void validate(flutter::DlFilterMode src) {
#ifndef NDEBUG
  switch (src) {
    case flutter::DlFilterMode::kNearest:
    case flutter::DlFilterMode::kLinear:
      break;
    default:
      assert(false);
  }
#endif
}

[[maybe_unused]] static inline flutter::DlFilterMode transmute(
    ipl_filter_mode_t src) {
  validate(src);
  return static_cast<flutter::DlFilterMode>(src);
}

[[maybe_unused]] static inline ipl_filter_mode_t transmute(
    flutter::DlFilterMode src) {
  validate(src);
  return static_cast<ipl_filter_mode_t>(src);
}

static_assert(std::is_same_v<std::underlying_type_t<flutter::DlImageSampling>,
                             std::underlying_type_t<ipl_image_sampling_t>>);

constexpr bool operator==(flutter::DlImageSampling lhs,
                          ipl_image_sampling_t rhs) {
  return static_cast<ipl_image_sampling_t>(lhs) == rhs;
}

static_assert(flutter::DlImageSampling::kNearestNeighbor ==
              IPL_IMAGE_SAMPLING_NEAREST_NEIGHBOR);
static_assert(flutter::DlImageSampling::kLinear == IPL_IMAGE_SAMPLING_LINEAR);
static_assert(flutter::DlImageSampling::kMipmapLinear ==
              IPL_IMAGE_SAMPLING_MIPMAP_LINEAR);
static_assert(flutter::DlImageSampling::kCubic == IPL_IMAGE_SAMPLING_CUBIC);

[[maybe_unused]] static inline void validate(ipl_image_sampling_t src) {
#ifndef NDEBUG
  switch (src) {
    case IPL_IMAGE_SAMPLING_NEAREST_NEIGHBOR:
    case IPL_IMAGE_SAMPLING_LINEAR:
    case IPL_IMAGE_SAMPLING_MIPMAP_LINEAR:
    case IPL_IMAGE_SAMPLING_CUBIC:
      break;
    default:
      assert(false);
  }
#endif
}

[[maybe_unused]] static inline void validate(flutter::DlImageSampling src) {
#ifndef NDEBUG
  switch (src) {
    case flutter::DlImageSampling::kNearestNeighbor:
    case flutter::DlImageSampling::kLinear:
    case flutter::DlImageSampling::kMipmapLinear:
    case flutter::DlImageSampling::kCubic:
      break;
    default:
      assert(false);
  }
#endif
}

[[maybe_unused]] static inline flutter::DlImageSampling transmute(
    ipl_image_sampling_t src) {
  validate(src);
  return static_cast<flutter::DlImageSampling>(src);
}

[[maybe_unused]] static inline ipl_image_sampling_t transmute(
    flutter::DlImageSampling src) {
  validate(src);
  return static_cast<ipl_image_sampling_t>(src);
}

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/display_list/dl_sampling_options.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/display_list/dl_tile_mode.h
// ---------------------------------------------------------------------------

// flutter::DlTileMode
static_assert(std::is_same_v<std::underlying_type_t<flutter::DlTileMode>,
                             std::underlying_type_t<ipl_tile_mode_t>>);

constexpr bool operator==(flutter::DlTileMode lhs, ipl_tile_mode_t rhs) {
  return static_cast<ipl_tile_mode_t>(lhs) == rhs;
}

static_assert(flutter::DlTileMode::kClamp == IPL_TILE_MODE_CLAMP);
static_assert(flutter::DlTileMode::kRepeat == IPL_TILE_MODE_REPEAT);
static_assert(flutter::DlTileMode::kMirror == IPL_TILE_MODE_MIRROR);
static_assert(flutter::DlTileMode::kDecal == IPL_TILE_MODE_DECAL);

[[maybe_unused]] static inline void validate(ipl_tile_mode_t src) {
#ifndef NDEBUG
  switch (src) {
    case IPL_TILE_MODE_CLAMP:
    case IPL_TILE_MODE_REPEAT:
    case IPL_TILE_MODE_MIRROR:
    case IPL_TILE_MODE_DECAL:
      break;
    default:
      assert(false);
  }
#endif
}

[[maybe_unused]] static inline void validate(flutter::DlTileMode src) {
#ifndef NDEBUG
  switch (src) {
    case flutter::DlTileMode::kClamp:
    case flutter::DlTileMode::kRepeat:
    case flutter::DlTileMode::kMirror:
    case flutter::DlTileMode::kDecal:
      break;
    default:
      assert(false);
  }
#endif
}

[[maybe_unused]] static inline flutter::DlTileMode transmute(
    ipl_tile_mode_t src) {
  validate(src);
  return static_cast<flutter::DlTileMode>(src);
}

[[maybe_unused]] static inline ipl_tile_mode_t transmute(
    flutter::DlTileMode src) {
  validate(src);
  return static_cast<ipl_tile_mode_t>(src);
}

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/display_list/dl_tile_mode.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/display_list/dl_color_filter.h
// ---------------------------------------------------------------------------

// std::shared_ptr<flutter::DlColorFilter>
static_assert(sizeof(std::shared_ptr<flutter::DlColorFilter>) ==
              sizeof(ipl_color_filter_t));
static_assert(alignof(std::shared_ptr<flutter::DlColorFilter>) ==
              alignof(ipl_color_filter_t));
// Manual check. `__builtin_is_cpp_trivially_relocatable` is overly
// conservative.
// static_assert(__builtin_is_cpp_trivially_relocatable(std::shared_ptr<flutter::DlColorFilter>));
static_assert(__builtin_is_cpp_trivially_relocatable(ipl_color_filter_t));

// std::shared_ptr<const flutter::DlColorFilter>
static_assert(sizeof(std::shared_ptr<const flutter::DlColorFilter>) ==
              sizeof(ipl_const_color_filter_t));
static_assert(alignof(std::shared_ptr<const flutter::DlColorFilter>) ==
              alignof(ipl_const_color_filter_t));
// Manual check. `__builtin_is_cpp_trivially_relocatable` is overly
// conservative.
// static_assert(__builtin_is_cpp_trivially_relocatable(std::shared_ptr<const
// flutter::DlColorFilter>));
static_assert(__builtin_is_cpp_trivially_relocatable(ipl_const_color_filter_t));

static inline void validate(const ipl_color_filter_t* src) {
  assert(src != nullptr);
  assert(reinterpret_cast<intptr_t>(src) % alignof(ipl_color_filter_t) == 0);
}

static inline void validate(
    const std::shared_ptr<flutter::DlColorFilter>* src) {
  assert(src != nullptr);
  assert(reinterpret_cast<intptr_t>(src) %
             alignof(std::shared_ptr<flutter::DlColorFilter>) ==
         0);
}

[[maybe_unused]] static inline std::shared_ptr<flutter::DlColorFilter>*
transmute(ipl_color_filter_t* src) {
  validate(src);
  return reinterpret_cast<std::shared_ptr<flutter::DlColorFilter>*>(src);
}

[[maybe_unused]] static inline const std::shared_ptr<flutter::DlColorFilter>*
transmute(const ipl_color_filter_t* src) {
  validate(src);
  return reinterpret_cast<const std::shared_ptr<flutter::DlColorFilter>*>(src);
}

[[maybe_unused]] static inline ipl_color_filter_t* transmute(
    std::shared_ptr<flutter::DlColorFilter>* src) {
  validate(src);
  return reinterpret_cast<ipl_color_filter_t*>(src);
}

[[maybe_unused]] static inline const ipl_color_filter_t* transmute(
    const std::shared_ptr<flutter::DlColorFilter>* src) {
  validate(src);
  return reinterpret_cast<const ipl_color_filter_t*>(src);
}

static inline void validate(const ipl_const_color_filter_t* src) {
  assert(src != nullptr);
  assert(reinterpret_cast<intptr_t>(src) % alignof(ipl_const_color_filter_t) ==
         0);
}

static inline void validate(
    const std::shared_ptr<const flutter::DlColorFilter>* src) {
  assert(src != nullptr);
  assert(reinterpret_cast<intptr_t>(src) %
             alignof(std::shared_ptr<const flutter::DlColorFilter>) ==
         0);
}

[[maybe_unused]] static inline std::shared_ptr<const flutter::DlColorFilter>*
transmute(ipl_const_color_filter_t* src) {
  validate(src);
  return reinterpret_cast<std::shared_ptr<const flutter::DlColorFilter>*>(src);
}

[[maybe_unused]] static inline const std::shared_ptr<
    const flutter::DlColorFilter>*
transmute(const ipl_const_color_filter_t* src) {
  validate(src);
  return reinterpret_cast<const std::shared_ptr<const flutter::DlColorFilter>*>(
      src);
}

[[maybe_unused]] static inline ipl_const_color_filter_t* transmute(
    std::shared_ptr<const flutter::DlColorFilter>* src) {
  validate(src);
  return reinterpret_cast<ipl_const_color_filter_t*>(src);
}

[[maybe_unused]] static inline const ipl_const_color_filter_t* transmute(
    const std::shared_ptr<const flutter::DlColorFilter>* src) {
  validate(src);
  return reinterpret_cast<const ipl_const_color_filter_t*>(src);
}

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/display_list/dl_color_filter.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/display_list/dl_color_source.h
// ---------------------------------------------------------------------------

// std::shared_ptr<flutter::DlColorSource>
static_assert(sizeof(std::shared_ptr<flutter::DlColorSource>) ==
              sizeof(ipl_color_source_t));
static_assert(alignof(std::shared_ptr<flutter::DlColorSource>) ==
              alignof(ipl_color_source_t));
// Manual check. `__builtin_is_cpp_trivially_relocatable` is overly
// conservative.
// static_assert(__builtin_is_cpp_trivially_relocatable(std::shared_ptr<flutter::DlColorSource>));
static_assert(__builtin_is_cpp_trivially_relocatable(ipl_color_source_t));

// std::shared_ptr<const flutter::DlColorSource>
static_assert(sizeof(std::shared_ptr<const flutter::DlColorSource>) ==
              sizeof(ipl_const_color_source_t));
static_assert(alignof(std::shared_ptr<const flutter::DlColorSource>) ==
              alignof(ipl_const_color_source_t));
// Manual check. `__builtin_is_cpp_trivially_relocatable` is overly
// conservative.
// static_assert(__builtin_is_cpp_trivially_relocatable(std::shared_ptr<const
// flutter::DlColorSource>));
static_assert(__builtin_is_cpp_trivially_relocatable(ipl_const_color_source_t));

static inline void validate(const ipl_color_source_t* src) {
  assert(src != nullptr);
  assert(reinterpret_cast<intptr_t>(src) % alignof(ipl_color_source_t) == 0);
}

static inline void validate(
    const std::shared_ptr<flutter::DlColorSource>* src) {
  assert(src != nullptr);
  assert(reinterpret_cast<intptr_t>(src) %
             alignof(std::shared_ptr<flutter::DlColorSource>) ==
         0);
}

[[maybe_unused]] static inline std::shared_ptr<flutter::DlColorSource>*
transmute(ipl_color_source_t* src) {
  validate(src);
  return reinterpret_cast<std::shared_ptr<flutter::DlColorSource>*>(src);
}

[[maybe_unused]] static inline const std::shared_ptr<flutter::DlColorSource>*
transmute(const ipl_color_source_t* src) {
  validate(src);
  return reinterpret_cast<const std::shared_ptr<flutter::DlColorSource>*>(src);
}

[[maybe_unused]] static inline ipl_color_source_t* transmute(
    std::shared_ptr<flutter::DlColorSource>* src) {
  validate(src);
  return reinterpret_cast<ipl_color_source_t*>(src);
}

[[maybe_unused]] static inline const ipl_color_source_t* transmute(
    const std::shared_ptr<flutter::DlColorSource>* src) {
  validate(src);
  return reinterpret_cast<const ipl_color_source_t*>(src);
}

static inline void validate(const ipl_const_color_source_t* src) {
  assert(src != nullptr);
  assert(reinterpret_cast<intptr_t>(src) % alignof(ipl_const_color_source_t) ==
         0);
}

static inline void validate(
    const std::shared_ptr<const flutter::DlColorSource>* src) {
  assert(src != nullptr);
  assert(reinterpret_cast<intptr_t>(src) %
             alignof(std::shared_ptr<const flutter::DlColorSource>) ==
         0);
}

[[maybe_unused]] static inline std::shared_ptr<const flutter::DlColorSource>*
transmute(ipl_const_color_source_t* src) {
  validate(src);
  return reinterpret_cast<std::shared_ptr<const flutter::DlColorSource>*>(src);
}

[[maybe_unused]] static inline const std::shared_ptr<
    const flutter::DlColorSource>*
transmute(const ipl_const_color_source_t* src) {
  validate(src);
  return reinterpret_cast<const std::shared_ptr<const flutter::DlColorSource>*>(
      src);
}

[[maybe_unused]] static inline ipl_const_color_source_t* transmute(
    std::shared_ptr<const flutter::DlColorSource>* src) {
  validate(src);
  return reinterpret_cast<ipl_const_color_source_t*>(src);
}

[[maybe_unused]] static inline const ipl_const_color_source_t* transmute(
    const std::shared_ptr<const flutter::DlColorSource>* src) {
  validate(src);
  return reinterpret_cast<const ipl_const_color_source_t*>(src);
}

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/display_list/dl_color_source.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/display_list/dl_image_filter.h
// ---------------------------------------------------------------------------

// std::shared_ptr<flutter::DlImageFilter>
static_assert(sizeof(std::shared_ptr<flutter::DlImageFilter>) ==
              sizeof(ipl_image_filter_t));
static_assert(alignof(std::shared_ptr<flutter::DlImageFilter>) ==
              alignof(ipl_image_filter_t));
// Manual check. `__builtin_is_cpp_trivially_relocatable` is overly
// conservative.
// static_assert(__builtin_is_cpp_trivially_relocatable(std::shared_ptr<flutter::DlImageFilter>));
static_assert(__builtin_is_cpp_trivially_relocatable(ipl_image_filter_t));

static inline void validate(const ipl_image_filter_t* src) {
  assert(src != nullptr);
  assert(reinterpret_cast<intptr_t>(src) % alignof(ipl_image_filter_t) == 0);
}

static inline void validate(
    const std::shared_ptr<flutter::DlImageFilter>* src) {
  assert(src != nullptr);
  assert(reinterpret_cast<intptr_t>(src) %
             alignof(std::shared_ptr<flutter::DlImageFilter>) ==
         0);
}

[[maybe_unused]] static inline std::shared_ptr<flutter::DlImageFilter>*
transmute(ipl_image_filter_t* src) {
  validate(src);
  return reinterpret_cast<std::shared_ptr<flutter::DlImageFilter>*>(src);
}

[[maybe_unused]] static inline const std::shared_ptr<flutter::DlImageFilter>*
transmute(const ipl_image_filter_t* src) {
  validate(src);
  return reinterpret_cast<const std::shared_ptr<flutter::DlImageFilter>*>(src);
}

[[maybe_unused]] static inline ipl_image_filter_t* transmute(
    std::shared_ptr<flutter::DlImageFilter>* src) {
  validate(src);
  return reinterpret_cast<ipl_image_filter_t*>(src);
}

[[maybe_unused]] static inline const ipl_image_filter_t* transmute(
    const std::shared_ptr<flutter::DlImageFilter>* src) {
  validate(src);
  return reinterpret_cast<const ipl_image_filter_t*>(src);
}

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/display_list/dl_image_filter.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/display_list/dl_mask_filter.h
// ---------------------------------------------------------------------------

static_assert(std::is_same_v<std::underlying_type_t<flutter::DlBlurStyle>,
                             std::underlying_type_t<ipl_blur_style_t>>);

constexpr bool operator==(flutter::DlBlurStyle lhs, ipl_blur_style_t rhs) {
  return static_cast<ipl_blur_style_t>(lhs) == rhs;
}

static_assert(flutter::DlBlurStyle::kNormal == IPL_BLUR_STYLE_NORMAL);
static_assert(flutter::DlBlurStyle::kSolid == IPL_BLUR_STYLE_SOLID);
static_assert(flutter::DlBlurStyle::kOuter == IPL_BLUR_STYLE_OUTER);
static_assert(flutter::DlBlurStyle::kInner == IPL_BLUR_STYLE_INNER);

[[maybe_unused]] static inline void validate(ipl_blur_style_t src) {
#ifndef NDEBUG
  switch (src) {
    case IPL_BLUR_STYLE_NORMAL:
    case IPL_BLUR_STYLE_SOLID:
    case IPL_BLUR_STYLE_OUTER:
    case IPL_BLUR_STYLE_INNER:
      break;
    default:
      assert(false);
  }
#endif
}

[[maybe_unused]] static inline void validate(flutter::DlBlurStyle src) {
#ifndef NDEBUG
  switch (src) {
    case flutter::DlBlurStyle::kNormal:
    case flutter::DlBlurStyle::kSolid:
    case flutter::DlBlurStyle::kOuter:
    case flutter::DlBlurStyle::kInner:
      break;
    default:
      assert(false);
  }
#endif
}

[[maybe_unused]] static inline flutter::DlBlurStyle transmute(
    ipl_blur_style_t src) {
  validate(src);
  return static_cast<flutter::DlBlurStyle>(src);
}

[[maybe_unused]] static inline ipl_blur_style_t transmute(
    flutter::DlBlurStyle src) {
  validate(src);
  return static_cast<ipl_blur_style_t>(src);
}

// std::shared_ptr<flutter::DlMaskFilter>
static_assert(sizeof(std::shared_ptr<flutter::DlMaskFilter>) ==
              sizeof(ipl_mask_filter_t));
static_assert(alignof(std::shared_ptr<flutter::DlMaskFilter>) ==
              alignof(ipl_mask_filter_t));
// Manual check. `__builtin_is_cpp_trivially_relocatable` is overly
// conservative.
// static_assert(__builtin_is_cpp_trivially_relocatable(std::shared_ptr<flutter::DlMaskFilter>));
static_assert(__builtin_is_cpp_trivially_relocatable(ipl_mask_filter_t));

// std::shared_ptr<const flutter::DlMaskFilter>
static_assert(sizeof(std::shared_ptr<const flutter::DlMaskFilter>) ==
              sizeof(ipl_const_mask_filter_t));
static_assert(alignof(std::shared_ptr<const flutter::DlMaskFilter>) ==
              alignof(ipl_const_mask_filter_t));
// Manual check. `__builtin_is_cpp_trivially_relocatable` is overly
// conservative.
// static_assert(__builtin_is_cpp_trivially_relocatable(std::shared_ptr<const
// flutter::DlMaskFilter>));
static_assert(__builtin_is_cpp_trivially_relocatable(ipl_const_mask_filter_t));

static inline void validate(const ipl_mask_filter_t* src) {
  assert(src != nullptr);
  assert(reinterpret_cast<intptr_t>(src) % alignof(ipl_mask_filter_t) == 0);
}

static inline void validate(const std::shared_ptr<flutter::DlMaskFilter>* src) {
  assert(src != nullptr);
  assert(reinterpret_cast<intptr_t>(src) %
             alignof(std::shared_ptr<flutter::DlMaskFilter>) ==
         0);
}

[[maybe_unused]] static inline std::shared_ptr<flutter::DlMaskFilter>*
transmute(ipl_mask_filter_t* src) {
  validate(src);
  return reinterpret_cast<std::shared_ptr<flutter::DlMaskFilter>*>(src);
}

[[maybe_unused]] static inline const std::shared_ptr<flutter::DlMaskFilter>*
transmute(const ipl_mask_filter_t* src) {
  validate(src);
  return reinterpret_cast<const std::shared_ptr<flutter::DlMaskFilter>*>(src);
}

[[maybe_unused]] static inline ipl_mask_filter_t* transmute(
    std::shared_ptr<flutter::DlMaskFilter>* src) {
  validate(src);
  return reinterpret_cast<ipl_mask_filter_t*>(src);
}

[[maybe_unused]] static inline const ipl_mask_filter_t* transmute(
    const std::shared_ptr<flutter::DlMaskFilter>* src) {
  validate(src);
  return reinterpret_cast<const ipl_mask_filter_t*>(src);
}

static inline void validate(const ipl_const_mask_filter_t* src) {
  assert(src != nullptr);
  assert(reinterpret_cast<intptr_t>(src) % alignof(ipl_const_mask_filter_t) ==
         0);
}

static inline void validate(
    const std::shared_ptr<const flutter::DlMaskFilter>* src) {
  assert(src != nullptr);
  assert(reinterpret_cast<intptr_t>(src) %
             alignof(std::shared_ptr<const flutter::DlMaskFilter>) ==
         0);
}

[[maybe_unused]] static inline std::shared_ptr<const flutter::DlMaskFilter>*
transmute(ipl_const_mask_filter_t* src) {
  validate(src);
  return reinterpret_cast<std::shared_ptr<const flutter::DlMaskFilter>*>(src);
}

[[maybe_unused]] static inline const std::shared_ptr<
    const flutter::DlMaskFilter>*
transmute(const ipl_const_mask_filter_t* src) {
  validate(src);
  return reinterpret_cast<const std::shared_ptr<const flutter::DlMaskFilter>*>(
      src);
}

[[maybe_unused]] static inline ipl_const_mask_filter_t* transmute(
    std::shared_ptr<const flutter::DlMaskFilter>* src) {
  validate(src);
  return reinterpret_cast<ipl_const_mask_filter_t*>(src);
}

[[maybe_unused]] static inline const ipl_const_mask_filter_t* transmute(
    const std::shared_ptr<const flutter::DlMaskFilter>* src) {
  validate(src);
  return reinterpret_cast<const ipl_const_mask_filter_t*>(src);
}

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/display_list/dl_mask_filter.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/display_list/dl_image.h
// ---------------------------------------------------------------------------

// sk_sp<impeller::DlImageImpeller>
static_assert(sizeof(sk_sp<impeller::DlImageImpeller>) == sizeof(ipl_image_t));
static_assert(alignof(sk_sp<impeller::DlImageImpeller>) ==
              alignof(ipl_image_t));
// Manual check. `__builtin_is_cpp_trivially_relocatable` is overly
// conservative.
// static_assert(__builtin_is_cpp_trivially_relocatable(sk_sp<impeller::DlImageImpeller>));
static_assert(__builtin_is_cpp_trivially_relocatable(ipl_image_t));

static inline void validate(const ipl_image_t* src) {
  assert(src != nullptr);
  assert(reinterpret_cast<intptr_t>(src) % alignof(ipl_image_t) == 0);
}

static inline void validate(const sk_sp<impeller::DlImageImpeller>* src) {
  assert(src != nullptr);
  assert(reinterpret_cast<intptr_t>(src) %
             alignof(sk_sp<impeller::DlImageImpeller>) ==
         0);
}

[[maybe_unused]] static inline sk_sp<impeller::DlImageImpeller>* transmute(
    ipl_image_t* src) {
  validate(src);
  return reinterpret_cast<sk_sp<impeller::DlImageImpeller>*>(src);
}

[[maybe_unused]] static inline const sk_sp<impeller::DlImageImpeller>*
transmute(const ipl_image_t* src) {
  validate(src);
  return reinterpret_cast<const sk_sp<impeller::DlImageImpeller>*>(src);
}

[[maybe_unused]] static inline ipl_image_t* transmute(
    sk_sp<impeller::DlImageImpeller>* src) {
  validate(src);
  return reinterpret_cast<ipl_image_t*>(src);
}

[[maybe_unused]] static inline const ipl_image_t* transmute(
    const sk_sp<impeller::DlImageImpeller>* src) {
  validate(src);
  return reinterpret_cast<const ipl_image_t*>(src);
}

// sk_sp<const impeller::DlImageImpeller>
static_assert(sizeof(sk_sp<const impeller::DlImageImpeller>) ==
              sizeof(ipl_const_image_t));
static_assert(alignof(sk_sp<const impeller::DlImageImpeller>) ==
              alignof(ipl_const_image_t));
// Manual check. `__builtin_is_cpp_trivially_relocatable` is overly
// conservative.
// static_assert(__builtin_is_cpp_trivially_relocatable(sk_sp<const
// impeller::DlImageImpeller>));
static_assert(__builtin_is_cpp_trivially_relocatable(ipl_const_image_t));

static inline void validate(const ipl_const_image_t* src) {
  assert(src != nullptr);
  assert(reinterpret_cast<intptr_t>(src) % alignof(ipl_const_image_t) == 0);
}

static inline void validate(const sk_sp<const impeller::DlImageImpeller>* src) {
  assert(src != nullptr);
  assert(reinterpret_cast<intptr_t>(src) %
             alignof(sk_sp<const impeller::DlImageImpeller>) ==
         0);
}

[[maybe_unused]] static inline sk_sp<const impeller::DlImageImpeller>*
transmute(ipl_const_image_t* src) {
  validate(src);
  return reinterpret_cast<sk_sp<const impeller::DlImageImpeller>*>(src);
}

[[maybe_unused]] static inline const sk_sp<const impeller::DlImageImpeller>*
transmute(const ipl_const_image_t* src) {
  validate(src);
  return reinterpret_cast<const sk_sp<const impeller::DlImageImpeller>*>(src);
}

[[maybe_unused]] static inline ipl_const_image_t* transmute(
    sk_sp<const impeller::DlImageImpeller>* src) {
  validate(src);
  return reinterpret_cast<ipl_const_image_t*>(src);
}

[[maybe_unused]] static inline const ipl_const_image_t* transmute(
    const sk_sp<const impeller::DlImageImpeller>* src) {
  validate(src);
  return reinterpret_cast<const ipl_const_image_t*>(src);
}

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/display_list/dl_image.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/display_list/dl_paint.h
// ---------------------------------------------------------------------------

// flutter::DlDrawStyle
static_assert(std::is_same_v<std::underlying_type_t<flutter::DlDrawStyle>,
                             std::underlying_type_t<ipl_draw_style_t>>);

constexpr bool operator==(flutter::DlDrawStyle lhs, ipl_draw_style_t rhs) {
  return static_cast<ipl_draw_style_t>(lhs) == rhs;
}

static_assert(flutter::DlDrawStyle::kFill == IPL_DRAW_STYLE_FILL);
static_assert(flutter::DlDrawStyle::kStroke == IPL_DRAW_STYLE_STROKE);
static_assert(flutter::DlDrawStyle::kStrokeAndFill ==
              IPL_DRAW_STYLE_STROKE_AND_FILL);

[[maybe_unused]] static inline void validate(ipl_draw_style_t src) {
#ifndef NDEBUG
  switch (src) {
    case IPL_DRAW_STYLE_FILL:
    case IPL_DRAW_STYLE_STROKE:
    case IPL_DRAW_STYLE_STROKE_AND_FILL:
      break;
    default:
      assert(false);
  }
#endif
}

[[maybe_unused]] static inline void validate(flutter::DlDrawStyle src) {
#ifndef NDEBUG
  switch (src) {
    case flutter::DlDrawStyle::kFill:
    case flutter::DlDrawStyle::kStroke:
    case flutter::DlDrawStyle::kStrokeAndFill:
      break;
    default:
      assert(false);
  }
#endif
}

[[maybe_unused]] static inline flutter::DlDrawStyle transmute(
    ipl_draw_style_t src) {
  validate(src);
  return static_cast<flutter::DlDrawStyle>(src);
}

[[maybe_unused]] static inline ipl_draw_style_t transmute(
    flutter::DlDrawStyle src) {
  validate(src);
  return static_cast<ipl_draw_style_t>(src);
}

// flutter::DlStrokeCap
static_assert(std::is_same_v<std::underlying_type_t<flutter::DlStrokeCap>,
                             std::underlying_type_t<ipl_stroke_cap_t>>);

constexpr bool operator==(flutter::DlStrokeCap lhs, ipl_stroke_cap_t rhs) {
  return static_cast<ipl_stroke_cap_t>(lhs) == rhs;
}

static_assert(flutter::DlStrokeCap::kButt == IPL_STROKE_CAP_BUTT);
static_assert(flutter::DlStrokeCap::kRound == IPL_STROKE_CAP_ROUND);
static_assert(flutter::DlStrokeCap::kSquare == IPL_STROKE_CAP_SQUARE);

[[maybe_unused]] static inline void validate(ipl_stroke_cap_t src) {
#ifndef NDEBUG
  switch (src) {
    case IPL_STROKE_CAP_BUTT:
    case IPL_STROKE_CAP_ROUND:
    case IPL_STROKE_CAP_SQUARE:
      break;
    default:
      assert(false);
  }
#endif
}

[[maybe_unused]] static inline void validate(flutter::DlStrokeCap src) {
#ifndef NDEBUG
  switch (src) {
    case flutter::DlStrokeCap::kButt:
    case flutter::DlStrokeCap::kRound:
    case flutter::DlStrokeCap::kSquare:
      break;
    default:
      assert(false);
  }
#endif
}

[[maybe_unused]] static inline flutter::DlStrokeCap transmute(
    ipl_stroke_cap_t src) {
  validate(src);
  return static_cast<flutter::DlStrokeCap>(src);
}

[[maybe_unused]] static inline ipl_stroke_cap_t transmute(
    flutter::DlStrokeCap src) {
  validate(src);
  return static_cast<ipl_stroke_cap_t>(src);
}

// flutter::DlStrokeJoin
static_assert(std::is_same_v<std::underlying_type_t<flutter::DlStrokeJoin>,
                             std::underlying_type_t<ipl_stroke_join_t>>);

constexpr bool operator==(flutter::DlStrokeJoin lhs, ipl_stroke_join_t rhs) {
  return static_cast<ipl_stroke_join_t>(lhs) == rhs;
}

static_assert(flutter::DlStrokeJoin::kMiter == IPL_STROKE_JOIN_MITER);
static_assert(flutter::DlStrokeJoin::kRound == IPL_STROKE_JOIN_ROUND);
static_assert(flutter::DlStrokeJoin::kBevel == IPL_STROKE_JOIN_BEVEL);

[[maybe_unused]] static inline void validate(ipl_stroke_join_t src) {
#ifndef NDEBUG
  switch (src) {
    case IPL_STROKE_JOIN_MITER:
    case IPL_STROKE_JOIN_ROUND:
    case IPL_STROKE_JOIN_BEVEL:
      break;
    default:
      assert(false);
  }
#endif
}

[[maybe_unused]] static inline void validate(flutter::DlStrokeJoin src) {
#ifndef NDEBUG
  switch (src) {
    case flutter::DlStrokeJoin::kMiter:
    case flutter::DlStrokeJoin::kRound:
    case flutter::DlStrokeJoin::kBevel:
      break;
    default:
      assert(false);
  }
#endif
}

[[maybe_unused]] static inline flutter::DlStrokeJoin transmute(
    ipl_stroke_join_t src) {
  validate(src);
  return static_cast<flutter::DlStrokeJoin>(src);
}

[[maybe_unused]] static inline ipl_stroke_join_t transmute(
    flutter::DlStrokeJoin src) {
  validate(src);
  return static_cast<ipl_stroke_join_t>(src);
}

// flutter::DlPaint
static_assert(sizeof(flutter::DlPaint) == sizeof(ipl_paint_t));
static_assert(alignof(flutter::DlPaint) == alignof(ipl_paint_t));
// Manual check. `__builtin_is_cpp_trivially_relocatable` is overly
// conservative.
// static_assert(__builtin_is_cpp_trivially_relocatable(flutter::DlPaint));
static_assert(__builtin_is_cpp_trivially_relocatable(ipl_paint_t));

static inline void validate(const ipl_paint_t* src) {
  assert(src != nullptr);
  assert(reinterpret_cast<intptr_t>(src) % alignof(ipl_paint_t) == 0);
}

static inline void validate(const flutter::DlPaint* src) {
  assert(src != nullptr);
  assert(reinterpret_cast<intptr_t>(src) % alignof(flutter::DlPaint) == 0);
}

[[maybe_unused]] static inline flutter::DlPaint* transmute(ipl_paint_t* src) {
  validate(src);
  return reinterpret_cast<flutter::DlPaint*>(src);
}

[[maybe_unused]] static inline const flutter::DlPaint* transmute(
    const ipl_paint_t* src,
    bool is_nonnull = true) {
  if (is_nonnull) {
    validate(src);
  }
  return reinterpret_cast<const flutter::DlPaint*>(src);
}

[[maybe_unused]] static inline ipl_paint_t* transmute(flutter::DlPaint* src) {
  validate(src);
  return reinterpret_cast<ipl_paint_t*>(src);
}

[[maybe_unused]] static inline const ipl_paint_t* transmute(
    const flutter::DlPaint* src) {
  validate(src);
  return reinterpret_cast<const ipl_paint_t*>(src);
}

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/display_list/dl_paint.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/display_list/dl_path.h
// ---------------------------------------------------------------------------

// flutter::DlPathFillType
static_assert(std::is_same_v<std::underlying_type_t<flutter::DlPathFillType>,
                             std::underlying_type_t<ipl_path_fill_type_t>>);

constexpr bool operator==(flutter::DlPathFillType lhs,
                          ipl_path_fill_type_t rhs) {
  return static_cast<ipl_path_fill_type_t>(lhs) == rhs;
}

static_assert(flutter::DlPathFillType::kNonZero == IPL_PATH_FILL_TYPE_NON_ZERO);
static_assert(flutter::DlPathFillType::kOdd == IPL_PATH_FILL_TYPE_ODD);

[[maybe_unused]] static inline void validate(ipl_path_fill_type_t src) {
#ifndef NDEBUG
  switch (src) {
    case IPL_PATH_FILL_TYPE_NON_ZERO:
    case IPL_PATH_FILL_TYPE_ODD:
      break;
    default:
      assert(false);
  }
#endif
}

[[maybe_unused]] static inline void validate(flutter::DlPathFillType src) {
#ifndef NDEBUG
  switch (src) {
    case flutter::DlPathFillType::kNonZero:
    case flutter::DlPathFillType::kOdd:
      break;
    default:
      assert(false);
  }
#endif
}

[[maybe_unused]] static inline flutter::DlPathFillType transmute(
    ipl_path_fill_type_t src) {
  validate(src);
  return static_cast<flutter::DlPathFillType>(src);
}

[[maybe_unused]] static inline ipl_path_fill_type_t transmute(
    flutter::DlPathFillType src) {
  validate(src);
  return static_cast<ipl_path_fill_type_t>(src);
}

// flutter::DlPath
static_assert(std::is_standard_layout_v<ipl_path_t>);
static_assert(sizeof(flutter::DlPath) == sizeof(ipl_path_t));
static_assert(alignof(flutter::DlPath) == alignof(ipl_path_t));
// Manual check. `__builtin_is_cpp_trivially_relocatable` is overly
// conservative.
// static_assert(__builtin_is_cpp_trivially_relocatable(flutter::DlPath));
static_assert(__builtin_is_cpp_trivially_relocatable(ipl_path_t));

static inline void validate(const ipl_path_t* src) {
  assert(src != nullptr);
  assert(reinterpret_cast<intptr_t>(src) % alignof(ipl_path_t) == 0);
}

static inline void validate(const flutter::DlPath* src) {
  assert(src != nullptr);
  assert(reinterpret_cast<intptr_t>(src) % alignof(flutter::DlPath) == 0);
}

[[maybe_unused]] static inline flutter::DlPath* transmute(ipl_path_t* src) {
  validate(src);
  return reinterpret_cast<flutter::DlPath*>(src);
}

[[maybe_unused]] static inline const flutter::DlPath* transmute(
    const ipl_path_t* src) {
  validate(src);
  return reinterpret_cast<const flutter::DlPath*>(src);
}

[[maybe_unused]] static inline ipl_path_t* transmute(flutter::DlPath* src) {
  validate(src);
  return reinterpret_cast<ipl_path_t*>(src);
}

[[maybe_unused]] static inline const ipl_path_t* transmute(
    const flutter::DlPath* src) {
  validate(src);
  return reinterpret_cast<const ipl_path_t*>(src);
}

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/display_list/dl_path.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/display_list/dl_path_builder.h
// ---------------------------------------------------------------------------

// flutter::DlPathBuilder
static_assert(std::is_standard_layout_v<ipl_path_builder_t>);
static_assert(sizeof(flutter::DlPathBuilder) == sizeof(ipl_path_builder_t));
static_assert(alignof(flutter::DlPathBuilder) == alignof(ipl_path_builder_t));
// Manual check. `__builtin_is_cpp_trivially_relocatable` is overly
// conservative.
// static_assert(__builtin_is_cpp_trivially_relocatable(flutter::DlPathBuilder));
static_assert(__builtin_is_cpp_trivially_relocatable(ipl_path_builder_t));

static inline void validate(const ipl_path_builder_t* src) {
  assert(src != nullptr);
  assert(reinterpret_cast<intptr_t>(src) % alignof(ipl_path_builder_t) == 0);
}

static inline void validate(const flutter::DlPathBuilder* src) {
  assert(src != nullptr);
  assert(reinterpret_cast<intptr_t>(src) % alignof(flutter::DlPathBuilder) ==
         0);
}

[[maybe_unused]] static inline flutter::DlPathBuilder* transmute(
    ipl_path_builder_t* src) {
  validate(src);
  return reinterpret_cast<flutter::DlPathBuilder*>(src);
}

[[maybe_unused]] static inline const flutter::DlPathBuilder* transmute(
    const ipl_path_builder_t* src) {
  validate(src);
  return reinterpret_cast<const flutter::DlPathBuilder*>(src);
}

[[maybe_unused]] static inline ipl_path_builder_t* transmute(
    flutter::DlPathBuilder* src) {
  validate(src);
  return reinterpret_cast<ipl_path_builder_t*>(src);
}

[[maybe_unused]] static inline const ipl_path_builder_t* transmute(
    const flutter::DlPathBuilder* src) {
  validate(src);
  return reinterpret_cast<const ipl_path_builder_t*>(src);
}

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/display_list/dl_path_builder.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/display_list/dl_text.h
// ---------------------------------------------------------------------------

// std::shared_ptr<flutter::DlText>
static_assert(sizeof(std::shared_ptr<flutter::DlText>) == sizeof(ipl_text_t));
static_assert(alignof(std::shared_ptr<flutter::DlText>) == alignof(ipl_text_t));
// Manual check. `__builtin_is_cpp_trivially_relocatable` is overly
// conservative.
// static_assert(__builtin_is_cpp_trivially_relocatable(std::shared_ptr<flutter::DlText>));
static_assert(__builtin_is_cpp_trivially_relocatable(ipl_text_t));

static inline void validate(const ipl_text_t* src) {
  assert(src != nullptr);
  assert(reinterpret_cast<intptr_t>(src) % alignof(ipl_text_t) == 0);
}

static inline void validate(const std::shared_ptr<flutter::DlText>* src) {
  assert(src != nullptr);
  assert(reinterpret_cast<intptr_t>(src) %
             alignof(std::shared_ptr<flutter::DlText>) ==
         0);
}

[[maybe_unused]] static inline std::shared_ptr<flutter::DlText>* transmute(
    ipl_text_t* src) {
  validate(src);
  return reinterpret_cast<std::shared_ptr<flutter::DlText>*>(src);
}

[[maybe_unused]] static inline const std::shared_ptr<flutter::DlText>*
transmute(const ipl_text_t* src) {
  validate(src);
  return reinterpret_cast<const std::shared_ptr<flutter::DlText>*>(src);
}

[[maybe_unused]] static inline ipl_text_t* transmute(
    std::shared_ptr<flutter::DlText>* src) {
  validate(src);
  return reinterpret_cast<ipl_text_t*>(src);
}

[[maybe_unused]] static inline const ipl_text_t* transmute(
    const std::shared_ptr<flutter::DlText>* src) {
  validate(src);
  return reinterpret_cast<const ipl_text_t*>(src);
}

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/display_list/dl_text.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/display_list/display_list.h
// ---------------------------------------------------------------------------

// sk_sp<flutter::DisplayList>

static_assert(sizeof(sk_sp<flutter::DisplayList>) ==
              sizeof(ipl_display_list_t));
static_assert(alignof(sk_sp<flutter::DisplayList>) ==
              alignof(ipl_display_list_t));
// Manual check. `__builtin_is_cpp_trivially_relocatable` is overly
// conservative.
// static_assert(__builtin_is_cpp_trivially_relocatable(sk_sp<flutter::DisplayList>));
static_assert(__builtin_is_cpp_trivially_relocatable(ipl_display_list_t));

static inline void validate(const ipl_display_list_t* src) {
  assert(src != nullptr);
  assert(reinterpret_cast<intptr_t>(src) % alignof(ipl_display_list_t) == 0);
}

static inline void validate(const sk_sp<flutter::DisplayList>* src) {
  assert(src != nullptr);
  assert(reinterpret_cast<intptr_t>(src) %
             alignof(sk_sp<flutter::DisplayList>) ==
         0);
}

[[maybe_unused]] static inline sk_sp<flutter::DisplayList>* transmute(
    ipl_display_list_t* src) {
  validate(src);
  return reinterpret_cast<sk_sp<flutter::DisplayList>*>(src);
}

[[maybe_unused]] static inline const sk_sp<flutter::DisplayList>* transmute(
    const ipl_display_list_t* src) {
  validate(src);
  return reinterpret_cast<const sk_sp<flutter::DisplayList>*>(src);
}

[[maybe_unused]] static inline ipl_display_list_t* transmute(
    sk_sp<flutter::DisplayList>* src) {
  validate(src);
  return reinterpret_cast<ipl_display_list_t*>(src);
}

[[maybe_unused]] static inline const ipl_display_list_t* transmute(
    const sk_sp<flutter::DisplayList>* src) {
  validate(src);
  return reinterpret_cast<const ipl_display_list_t*>(src);
}

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/display_list/display_list.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/display_list/dl_builder.h
// ---------------------------------------------------------------------------

// sk_sp<flutter::DisplayListBuilder>
static_assert(sizeof(sk_sp<flutter::DisplayListBuilder>) ==
              sizeof(ipl_display_list_builder_t));
static_assert(alignof(sk_sp<flutter::DisplayListBuilder>) ==
              alignof(ipl_display_list_builder_t));
// Manual check. `__builtin_is_cpp_trivially_relocatable` is overly
// conservative.
// static_assert(__builtin_is_cpp_trivially_relocatable(sk_sp<flutter::DisplayListBuilder>));
static_assert(
    __builtin_is_cpp_trivially_relocatable(ipl_display_list_builder_t));

static inline void validate(const ipl_display_list_builder_t* src) {
  assert(src != nullptr);
  assert(reinterpret_cast<intptr_t>(src) %
             alignof(ipl_display_list_builder_t) ==
         0);
}

static inline void validate(const sk_sp<flutter::DisplayListBuilder>* src) {
  assert(src != nullptr);
  assert(reinterpret_cast<intptr_t>(src) %
             alignof(sk_sp<flutter::DisplayListBuilder>) ==
         0);
}

[[maybe_unused]] static inline sk_sp<flutter::DisplayListBuilder>* transmute(
    ipl_display_list_builder_t* src) {
  validate(src);
  return reinterpret_cast<sk_sp<flutter::DisplayListBuilder>*>(src);
}

[[maybe_unused]] static inline const sk_sp<flutter::DisplayListBuilder>*
transmute(const ipl_display_list_builder_t* src) {
  validate(src);
  return reinterpret_cast<const sk_sp<flutter::DisplayListBuilder>*>(src);
}

[[maybe_unused]] static inline ipl_display_list_builder_t* transmute(
    sk_sp<flutter::DisplayListBuilder>* src) {
  validate(src);
  return reinterpret_cast<ipl_display_list_builder_t*>(src);
}

[[maybe_unused]] static inline const ipl_display_list_builder_t* transmute(
    const sk_sp<flutter::DisplayListBuilder>* src) {
  validate(src);
  return reinterpret_cast<const ipl_display_list_builder_t*>(src);
}

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/display_list/dl_builder.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/txt/src/txt/font_style.h
// ---------------------------------------------------------------------------

// txt::FontStyle

static_assert(std::is_same_v<std::underlying_type_t<txt::FontStyle>,
                             std::underlying_type_t<ipl_font_style_t>>);

constexpr bool operator==(txt::FontStyle lhs, ipl_font_style_t rhs) {
  return static_cast<ipl_font_style_t>(lhs) == rhs;
}

static_assert(static_cast<int>(txt::FontStyle::normal) ==
              IPL_FONT_STYLE_NORMAL);
static_assert(static_cast<int>(txt::FontStyle::italic) ==
              IPL_FONT_STYLE_ITALIC);

[[maybe_unused]] static inline void validate(ipl_font_style_t src) {
#ifndef NDEBUG
  switch (src) {
    case IPL_FONT_STYLE_NORMAL:
    case IPL_FONT_STYLE_ITALIC:
      break;
    default:
      assert(false);
  }
#endif
}

[[maybe_unused]] static inline void validate(txt::FontStyle src) {
#ifndef NDEBUG
  switch (src) {
    case txt::FontStyle::normal:
    case txt::FontStyle::italic:
      break;
    default:
      assert(false);
  }
#endif
}

[[maybe_unused]] static inline txt::FontStyle transmute(ipl_font_style_t src) {
  validate(src);
  return static_cast<txt::FontStyle>(src);
}

[[maybe_unused]] static inline ipl_font_style_t transmute(txt::FontStyle src) {
  validate(src);
  return static_cast<ipl_font_style_t>(src);
}

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/txt/src/txt/font_style.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/txt/src/txt/paragraph_style.h
// ---------------------------------------------------------------------------

// txt::TextAlign
static_assert(std::is_same_v<std::underlying_type_t<txt::TextAlign>,
                             std::underlying_type_t<ipl_text_align_t>>);

constexpr bool operator==(txt::TextAlign lhs, ipl_text_align_t rhs) {
  return static_cast<ipl_text_align_t>(lhs) == rhs;
}

static_assert(txt::TextAlign::left == IPL_TEXT_ALIGN_LEFT);
static_assert(txt::TextAlign::right == IPL_TEXT_ALIGN_RIGHT);
static_assert(txt::TextAlign::center == IPL_TEXT_ALIGN_CENTER);
static_assert(txt::TextAlign::justify == IPL_TEXT_ALIGN_JUSTIFY);
static_assert(txt::TextAlign::start == IPL_TEXT_ALIGN_START);
static_assert(txt::TextAlign::end == IPL_TEXT_ALIGN_END);

[[maybe_unused]] static inline void validate(ipl_text_align_t src) {
#ifndef NDEBUG
  switch (src) {
    case IPL_TEXT_ALIGN_LEFT:
    case IPL_TEXT_ALIGN_RIGHT:
    case IPL_TEXT_ALIGN_CENTER:
    case IPL_TEXT_ALIGN_JUSTIFY:
    case IPL_TEXT_ALIGN_START:
    case IPL_TEXT_ALIGN_END:
      break;
    default:
      assert(false);
  }
#endif
}

[[maybe_unused]] static inline void validate(txt::TextAlign src) {
#ifndef NDEBUG
  switch (src) {
    case txt::TextAlign::left:
    case txt::TextAlign::right:
    case txt::TextAlign::center:
    case txt::TextAlign::justify:
    case txt::TextAlign::start:
    case txt::TextAlign::end:
      break;
    default:
      assert(false);
  }
#endif
}

[[maybe_unused]] static inline txt::TextAlign transmute(ipl_text_align_t src) {
  validate(src);
  return static_cast<txt::TextAlign>(src);
}

[[maybe_unused]] static inline ipl_text_align_t transmute(txt::TextAlign src) {
  validate(src);
  return static_cast<ipl_text_align_t>(src);
}

// txt::TextDirection
static_assert(std::is_same_v<std::underlying_type_t<txt::TextDirection>,
                             std::underlying_type_t<ipl_text_direction_t>>);

constexpr bool operator==(txt::TextDirection lhs, ipl_text_direction_t rhs) {
  return static_cast<ipl_text_direction_t>(lhs) == rhs;
}

static_assert(txt::TextDirection::rtl == IPL_TEXT_DIRECTION_RTL);
static_assert(txt::TextDirection::ltr == IPL_TEXT_DIRECTION_LTR);

[[maybe_unused]] static inline void validate(ipl_text_direction_t src) {
#ifndef NDEBUG
  switch (src) {
    case IPL_TEXT_DIRECTION_RTL:
    case IPL_TEXT_DIRECTION_LTR:
      break;
    default:
      assert(false);
  }
#endif
}

[[maybe_unused]] static inline void validate(txt::TextDirection src) {
#ifndef NDEBUG
  switch (src) {
    case txt::TextDirection::rtl:
    case txt::TextDirection::ltr:
      break;
    default:
      assert(false);
  }
#endif
}

[[maybe_unused]] static inline txt::TextDirection transmute(
    ipl_text_direction_t src) {
  validate(src);
  return static_cast<txt::TextDirection>(src);
}

[[maybe_unused]] static inline ipl_text_direction_t transmute(
    txt::TextDirection src) {
  validate(src);
  return static_cast<ipl_text_direction_t>(src);
}

// txt::TextHeightBehavior
static_assert(
    std::is_same_v<std::underlying_type_t<txt::TextHeightBehavior>,
                   std::underlying_type_t<ipl_text_height_behavior_t>>);

constexpr bool operator==(txt::TextHeightBehavior lhs,
                          ipl_text_height_behavior_t rhs) {
  return static_cast<ipl_text_height_behavior_t>(lhs) == rhs;
}

static_assert(txt::TextHeightBehavior::kAll == IPL_TEXT_HEIGHT_BEHAVIOR_ALL);
static_assert(txt::TextHeightBehavior::kDisableFirstAscent ==
              IPL_TEXT_HEIGHT_BEHAVIOR_DISABLE_FIRST_ASCENT);
static_assert(txt::TextHeightBehavior::kDisableLastDescent ==
              IPL_TEXT_HEIGHT_BEHAVIOR_DISABLE_LAST_DESCENT);
static_assert(txt::TextHeightBehavior::kDisableAll ==
              IPL_TEXT_HEIGHT_BEHAVIOR_DISABLE_ALL);

[[maybe_unused]] static inline void validate(ipl_text_height_behavior_t src) {
#ifndef NDEBUG
  switch (src) {
    case IPL_TEXT_HEIGHT_BEHAVIOR_ALL:
    case IPL_TEXT_HEIGHT_BEHAVIOR_DISABLE_FIRST_ASCENT:
    case IPL_TEXT_HEIGHT_BEHAVIOR_DISABLE_LAST_DESCENT:
    case IPL_TEXT_HEIGHT_BEHAVIOR_DISABLE_ALL:
      break;
    default:
      assert(false);
  }
#endif
}

[[maybe_unused]] static inline void validate(txt::TextHeightBehavior src) {
#ifndef NDEBUG
  switch (src) {
    case txt::TextHeightBehavior::kAll:
    case txt::TextHeightBehavior::kDisableFirstAscent:
    case txt::TextHeightBehavior::kDisableLastDescent:
    case txt::TextHeightBehavior::kDisableAll:
      break;
    default:
      assert(false);
  }
#endif
}

[[maybe_unused]] static inline txt::TextHeightBehavior transmute(
    ipl_text_height_behavior_t src) {
  validate(src);
  return static_cast<txt::TextHeightBehavior>(src);
}

[[maybe_unused]] static inline ipl_text_height_behavior_t transmute(
    txt::TextHeightBehavior src) {
  validate(src);
  return static_cast<ipl_text_height_behavior_t>(src);
}

// txt::ParagraphStyle
static_assert(sizeof(txt::ParagraphStyle) == sizeof(ipl_paragraph_style_t));
static_assert(alignof(txt::ParagraphStyle) == alignof(ipl_paragraph_style_t));
// Manual check. `__builtin_is_cpp_trivially_relocatable` is overly
// conservative.
// static_assert(__builtin_is_cpp_trivially_relocatable(txt::ParagraphStyle));
static_assert(__builtin_is_cpp_trivially_relocatable(ipl_paragraph_style_t));

static inline void validate(const ipl_paragraph_style_t* src) {
  assert(src != nullptr);
  assert(reinterpret_cast<intptr_t>(src) % alignof(ipl_paragraph_style_t) == 0);
}

static inline void validate(const txt::ParagraphStyle* src) {
  assert(src != nullptr);
  assert(reinterpret_cast<intptr_t>(src) % alignof(txt::ParagraphStyle) == 0);
}

[[maybe_unused]] static inline txt::ParagraphStyle* transmute(
    ipl_paragraph_style_t* src) {
  validate(src);
  return reinterpret_cast<txt::ParagraphStyle*>(src);
}

[[maybe_unused]] static inline const txt::ParagraphStyle* transmute(
    const ipl_paragraph_style_t* src) {
  validate(src);
  return reinterpret_cast<const txt::ParagraphStyle*>(src);
}

[[maybe_unused]] static inline ipl_paragraph_style_t* transmute(
    txt::ParagraphStyle* src) {
  validate(src);
  return reinterpret_cast<ipl_paragraph_style_t*>(src);
}

[[maybe_unused]] static inline const ipl_paragraph_style_t* transmute(
    const txt::ParagraphStyle* src) {
  validate(src);
  return reinterpret_cast<const ipl_paragraph_style_t*>(src);
}

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/txt/src/txt/paragraph_style.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/txt/src/txt/text_decoration.h
// ---------------------------------------------------------------------------

// txt::TextDecoration
static_assert(sizeof(txt::TextDecoration) == sizeof(ipl_text_decoration_t));
static_assert(alignof(txt::TextDecoration) == alignof(ipl_text_decoration_t));

static inline void validate(const ipl_text_decoration_t* src) {
  assert(src != nullptr);
  assert(reinterpret_cast<intptr_t>(src) % alignof(ipl_text_decoration_t) == 0);
}

static inline void validate(const txt::TextDecoration* src) {
  assert(src != nullptr);
  assert(reinterpret_cast<intptr_t>(src) % alignof(txt::TextDecoration) == 0);
}

[[maybe_unused]] static inline txt::TextDecoration* transmute(
    ipl_text_decoration_t* src) {
  validate(src);
  return reinterpret_cast<txt::TextDecoration*>(src);
}

[[maybe_unused]] static inline const txt::TextDecoration* transmute(
    const ipl_text_decoration_t* src) {
  validate(src);
  return reinterpret_cast<const txt::TextDecoration*>(src);
}

[[maybe_unused]] static inline ipl_text_decoration_t* transmute(
    txt::TextDecoration* src) {
  validate(src);
  return reinterpret_cast<ipl_text_decoration_t*>(src);
}

[[maybe_unused]] static inline const ipl_text_decoration_t* transmute(
    const txt::TextDecoration* src) {
  validate(src);
  return reinterpret_cast<const ipl_text_decoration_t*>(src);
}

// txt::TextDecorationStyle
static_assert(
    std::is_same_v<std::underlying_type_t<txt::TextDecorationStyle>,
                   std::underlying_type_t<ipl_text_decoration_style_t>>);

constexpr bool operator==(txt::TextDecorationStyle lhs,
                          ipl_text_decoration_style_t rhs) {
  return static_cast<ipl_text_decoration_style_t>(lhs) == rhs;
}

static_assert(txt::TextDecorationStyle::kSolid == IPL_DECORATION_STYLE_SOLID);
static_assert(txt::TextDecorationStyle::kDouble == IPL_DECORATION_STYLE_DOUBLE);
static_assert(txt::TextDecorationStyle::kDotted == IPL_DECORATION_STYLE_DOTTED);
static_assert(txt::TextDecorationStyle::kDashed == IPL_DECORATION_STYLE_DASHED);
static_assert(txt::TextDecorationStyle::kWavy == IPL_DECORATION_STYLE_WAVY);

[[maybe_unused]] static inline void validate(ipl_text_decoration_style_t src) {
#ifndef NDEBUG
  switch (src) {
    case IPL_DECORATION_STYLE_SOLID:
    case IPL_DECORATION_STYLE_DOUBLE:
    case IPL_DECORATION_STYLE_DOTTED:
    case IPL_DECORATION_STYLE_DASHED:
    case IPL_DECORATION_STYLE_WAVY:
      break;
    default:
      assert(false);
  }
#endif
}

[[maybe_unused]] static inline void validate(txt::TextDecorationStyle src) {
#ifndef NDEBUG
  switch (src) {
    case txt::TextDecorationStyle::kSolid:
    case txt::TextDecorationStyle::kDouble:
    case txt::TextDecorationStyle::kDotted:
    case txt::TextDecorationStyle::kDashed:
    case txt::TextDecorationStyle::kWavy:
      break;
    default:
      assert(false);
  }
#endif
}

[[maybe_unused]] static inline txt::TextDecorationStyle transmute(
    ipl_text_decoration_style_t src) {
  validate(src);
  return static_cast<txt::TextDecorationStyle>(src);
}

[[maybe_unused]] static inline ipl_text_decoration_style_t transmute(
    txt::TextDecorationStyle src) {
  validate(src);
  return static_cast<ipl_text_decoration_style_t>(src);
}

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/txt/src/txt/text_decoration.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/txt/src/txt/text_baseline.h
// ---------------------------------------------------------------------------

// txt::TextBaseline
static_assert(std::is_same_v<std::underlying_type_t<txt::TextBaseline>,
                             std::underlying_type_t<ipl_text_baseline_t>>);

constexpr bool operator==(txt::TextBaseline lhs, ipl_text_baseline_t rhs) {
  return static_cast<ipl_text_baseline_t>(lhs) == rhs;
}

static_assert(txt::TextBaseline::kAlphabetic == IPL_TEXT_BASELINE_ALPHABETIC);
static_assert(txt::TextBaseline::kIdeographic == IPL_TEXT_BASELINE_IDEOGRAPHIC);

[[maybe_unused]] static inline void validate(ipl_text_baseline_t src) {
#ifndef NDEBUG
  switch (src) {
    case IPL_TEXT_BASELINE_ALPHABETIC:
    case IPL_TEXT_BASELINE_IDEOGRAPHIC:
      break;
    default:
      assert(false);
  }
#endif
}

[[maybe_unused]] static inline void validate(txt::TextBaseline src) {
#ifndef NDEBUG
  switch (src) {
    case txt::TextBaseline::kAlphabetic:
    case txt::TextBaseline::kIdeographic:
      break;
    default:
      assert(false);
  }
#endif
}

[[maybe_unused]] static inline txt::TextBaseline transmute(
    ipl_text_baseline_t src) {
  validate(src);
  return static_cast<txt::TextBaseline>(src);
}

[[maybe_unused]] static inline ipl_text_baseline_t transmute(
    txt::TextBaseline src) {
  validate(src);
  return static_cast<ipl_text_baseline_t>(src);
}

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/txt/src/txt/text_baseline.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/txt/src/txt/text_shadow.h
// ---------------------------------------------------------------------------

// txt::TextShadow
static_assert(sizeof(txt::TextShadow) == sizeof(ipl_text_shadow_t));
static_assert(alignof(txt::TextShadow) == alignof(ipl_text_shadow_t));
// Manual check. `__builtin_is_cpp_trivially_relocatable` is overly
// conservative.
// static_assert(__builtin_is_cpp_trivially_relocatable(txt::TextShadow));
static_assert(__builtin_is_cpp_trivially_relocatable(ipl_text_shadow_t));

static inline void validate(const ipl_text_shadow_t* src) {
  assert(src != nullptr);
  assert(reinterpret_cast<intptr_t>(src) % alignof(ipl_text_shadow_t) == 0);
}

static inline void validate(const txt::TextShadow* src) {
  assert(src != nullptr);
  assert(reinterpret_cast<intptr_t>(src) % alignof(txt::TextShadow) == 0);
}

[[maybe_unused]] static inline txt::TextShadow* transmute(
    ipl_text_shadow_t* src) {
  validate(src);
  return reinterpret_cast<txt::TextShadow*>(src);
}

[[maybe_unused]] static inline const txt::TextShadow* transmute(
    const ipl_text_shadow_t* src) {
  validate(src);
  return reinterpret_cast<const txt::TextShadow*>(src);
}

[[maybe_unused]] static inline ipl_text_shadow_t* transmute(
    txt::TextShadow* src) {
  validate(src);
  return reinterpret_cast<ipl_text_shadow_t*>(src);
}

[[maybe_unused]] static inline const ipl_text_shadow_t* transmute(
    const txt::TextShadow* src) {
  validate(src);
  return reinterpret_cast<const ipl_text_shadow_t*>(src);
}

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/txt/src/txt/text_shadow.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/txt/src/txt/font_features.h
// ---------------------------------------------------------------------------

// txt::FontFeatures*
static_assert(sizeof(txt::FontFeatures*) == sizeof(ipl_font_features_t));
static_assert(alignof(txt::FontFeatures*) == alignof(ipl_font_features_t));
static_assert(__builtin_is_cpp_trivially_relocatable(txt::FontFeatures*));
static_assert(__builtin_is_cpp_trivially_relocatable(ipl_font_features_t));

static inline void validate(const ipl_font_features_t src) {
  assert(src != nullptr);
}

static inline void validate(txt::FontFeatures* src) {
  assert(src != nullptr);
}

[[maybe_unused]] static inline txt::FontFeatures* transmute(
    ipl_font_features_t src) {
  validate(src);
  return reinterpret_cast<txt::FontFeatures*>(src);
}

[[maybe_unused]] static inline ipl_font_features_t transmute(
    txt::FontFeatures* src) {
  validate(src);
  return reinterpret_cast<ipl_font_features_t>(src);
}

// std::shared_ptr<txt::FontVariations>

static inline void validate(ipl_font_variations_t src) {
  assert(src != nullptr);
}

static inline void validate(const txt::FontVariations* src) {
  assert(src != nullptr);
}

[[maybe_unused]] static inline txt::FontVariations* transmute(
    ipl_font_variations_t src) {
  validate(src);
  return reinterpret_cast<txt::FontVariations*>(src);
}

[[maybe_unused]] static inline ipl_font_variations_t transmute(
    txt::FontVariations* src) {
  validate(src);
  return reinterpret_cast<ipl_font_variations_t>(src);
}

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/txt/src/txt/font_features.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/txt/src/txt/placeholder_run.h
// ---------------------------------------------------------------------------

// txt::PlaceholderAlignment
static_assert(
    std::is_same_v<std::underlying_type_t<txt::PlaceholderAlignment>,
                   std::underlying_type_t<ipl_placeholder_alignment_t>>);

constexpr bool operator==(txt::PlaceholderAlignment lhs,
                          ipl_placeholder_alignment_t rhs) {
  return static_cast<ipl_placeholder_alignment_t>(lhs) == rhs;
}

static_assert(txt::PlaceholderAlignment::kBaseline ==
              IPL_PLACEHOLDER_ALIGNMENT_BASELINE);
static_assert(txt::PlaceholderAlignment::kAboveBaseline ==
              IPL_PLACEHOLDER_ALIGNMENT_ABOVE_BASELINE);
static_assert(txt::PlaceholderAlignment::kBelowBaseline ==
              IPL_PLACEHOLDER_ALIGNMENT_BELOW_BASELINE);
static_assert(txt::PlaceholderAlignment::kTop == IPL_PLACEHOLDER_ALIGNMENT_TOP);
static_assert(txt::PlaceholderAlignment::kBottom ==
              IPL_PLACEHOLDER_ALIGNMENT_BOTTOM);
static_assert(txt::PlaceholderAlignment::kMiddle ==
              IPL_PLACEHOLDER_ALIGNMENT_MIDDLE);

[[maybe_unused]] static inline void validate(ipl_placeholder_alignment_t src) {
#ifndef NDEBUG
  switch (src) {
    case IPL_PLACEHOLDER_ALIGNMENT_BASELINE:
    case IPL_PLACEHOLDER_ALIGNMENT_ABOVE_BASELINE:
    case IPL_PLACEHOLDER_ALIGNMENT_BELOW_BASELINE:
    case IPL_PLACEHOLDER_ALIGNMENT_TOP:
    case IPL_PLACEHOLDER_ALIGNMENT_BOTTOM:
    case IPL_PLACEHOLDER_ALIGNMENT_MIDDLE:
      break;
    default:
      assert(false);
  }
#endif
}

[[maybe_unused]] static inline void validate(txt::PlaceholderAlignment src) {
#ifndef NDEBUG
  switch (src) {
    case txt::PlaceholderAlignment::kBaseline:
    case txt::PlaceholderAlignment::kAboveBaseline:
    case txt::PlaceholderAlignment::kBelowBaseline:
    case txt::PlaceholderAlignment::kTop:
    case txt::PlaceholderAlignment::kBottom:
    case txt::PlaceholderAlignment::kMiddle:
      break;
    default:
      assert(false);
  }
#endif
}

[[maybe_unused]] static inline txt::PlaceholderAlignment transmute(
    ipl_placeholder_alignment_t src) {
  validate(src);
  return static_cast<txt::PlaceholderAlignment>(src);
}

[[maybe_unused]] static inline ipl_placeholder_alignment_t transmute(
    txt::PlaceholderAlignment src) {
  validate(src);
  return static_cast<ipl_placeholder_alignment_t>(src);
}

// txt::PlaceholderRun
static_assert(sizeof(txt::PlaceholderRun) == sizeof(ipl_placehoder_run_t));
static_assert(alignof(txt::PlaceholderRun) == alignof(ipl_placehoder_run_t));
// Manual check. `__builtin_is_cpp_trivially_relocatable` is overly
// conservative.
// static_assert(__builtin_is_cpp_trivially_relocatable(txt::PlaceholderRun));
static_assert(__builtin_is_cpp_trivially_relocatable(ipl_placehoder_run_t));

static inline void validate(const ipl_placehoder_run_t* src) {
  assert(src != nullptr);
  assert(reinterpret_cast<intptr_t>(src) % alignof(ipl_placehoder_run_t) == 0);
}

static inline void validate(const txt::PlaceholderRun* src) {
  assert(src != nullptr);
  assert(reinterpret_cast<intptr_t>(src) % alignof(txt::PlaceholderRun) == 0);
}

[[maybe_unused]] static inline txt::PlaceholderRun* transmute(
    ipl_placehoder_run_t* src) {
  validate(src);
  return reinterpret_cast<txt::PlaceholderRun*>(src);
}

[[maybe_unused]] static inline const txt::PlaceholderRun* transmute(
    const ipl_placehoder_run_t* src) {
  validate(src);
  return reinterpret_cast<const txt::PlaceholderRun*>(src);
}

[[maybe_unused]] static inline ipl_placehoder_run_t* transmute(
    txt::PlaceholderRun* src) {
  validate(src);
  return reinterpret_cast<ipl_placehoder_run_t*>(src);
}

[[maybe_unused]] static inline const ipl_placehoder_run_t* transmute(
    const txt::PlaceholderRun* src) {
  validate(src);
  return reinterpret_cast<const ipl_placehoder_run_t*>(src);
}

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/txt/src/txt/placeholder_run.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/txt/src/txt/text_style.h
// ---------------------------------------------------------------------------

// txt::TextStyle
static_assert(sizeof(txt::TextStyle) == sizeof(ipl_text_style_t));
static_assert(alignof(txt::TextStyle) == alignof(ipl_text_style_t));
// Manual check. `__builtin_is_cpp_trivially_relocatable` is overly
// conservative.
// static_assert(__builtin_is_cpp_trivially_relocatable(txt::TextStyle));
static_assert(__builtin_is_cpp_trivially_relocatable(ipl_text_style_t));

static inline void validate(const ipl_text_style_t* src) {
  assert(src != nullptr);
  assert(reinterpret_cast<intptr_t>(src) % alignof(ipl_text_style_t) == 0);
}

static inline void validate(const txt::TextStyle* src) {
  assert(src != nullptr);
  assert(reinterpret_cast<intptr_t>(src) % alignof(txt::TextStyle) == 0);
}

[[maybe_unused]] static inline txt::TextStyle* transmute(
    ipl_text_style_t* src) {
  validate(src);
  return reinterpret_cast<txt::TextStyle*>(src);
}

[[maybe_unused]] static inline const txt::TextStyle* transmute(
    const ipl_text_style_t* src) {
  validate(src);
  return reinterpret_cast<const txt::TextStyle*>(src);
}

[[maybe_unused]] static inline ipl_text_style_t* transmute(
    txt::TextStyle* src) {
  validate(src);
  return reinterpret_cast<ipl_text_style_t*>(src);
}

[[maybe_unused]] static inline const ipl_text_style_t* transmute(
    const txt::TextStyle* src) {
  validate(src);
  return reinterpret_cast<const ipl_text_style_t*>(src);
}

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/txt/src/txt/text_style.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/txt/src/txt/font_collection.h
// ---------------------------------------------------------------------------

// std::shared_ptr<txt::FontCollection>
static_assert(sizeof(std::shared_ptr<txt::FontCollection>) ==
              sizeof(ipl_font_collection_t));
static_assert(alignof(std::shared_ptr<txt::FontCollection>) ==
              alignof(ipl_font_collection_t));
// Manual check. `__builtin_is_cpp_trivially_relocatable` is overly
// conservative.
// static_assert(__builtin_is_cpp_trivially_relocatable(std::shared_ptr<txt::FontCollection>));
static_assert(__builtin_is_cpp_trivially_relocatable(ipl_font_collection_t));

static inline void validate(const ipl_font_collection_t* src) {
  assert(src != nullptr);
  assert(reinterpret_cast<intptr_t>(src) % alignof(ipl_font_collection_t) == 0);
}

static inline void validate(const std::shared_ptr<txt::FontCollection>* src) {
  assert(src != nullptr);
  assert(reinterpret_cast<intptr_t>(src) %
             alignof(std::shared_ptr<txt::FontCollection>) ==
         0);
}

[[maybe_unused]] static inline std::shared_ptr<txt::FontCollection>* transmute(
    ipl_font_collection_t* src) {
  validate(src);
  return reinterpret_cast<std::shared_ptr<txt::FontCollection>*>(src);
}

[[maybe_unused]] static inline const std::shared_ptr<txt::FontCollection>*
transmute(const ipl_font_collection_t* src) {
  validate(src);
  return reinterpret_cast<const std::shared_ptr<txt::FontCollection>*>(src);
}

[[maybe_unused]] static inline ipl_font_collection_t* transmute(
    std::shared_ptr<txt::FontCollection>* src) {
  validate(src);
  return reinterpret_cast<ipl_font_collection_t*>(src);
}

[[maybe_unused]] static inline const ipl_font_collection_t* transmute(
    const std::shared_ptr<txt::FontCollection>* src) {
  validate(src);
  return reinterpret_cast<const ipl_font_collection_t*>(src);
}

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/txt/src/txt/font_collection.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/txt/src/txt/paragraph.h
// ---------------------------------------------------------------------------

// std::unique_ptr<txt::Paragraph>
static_assert(sizeof(std::unique_ptr<txt::Paragraph>) ==
              sizeof(ipl_paragraph_t));
static_assert(alignof(std::unique_ptr<txt::Paragraph>) ==
              alignof(ipl_paragraph_t));
// Manual check. `__builtin_is_cpp_trivially_relocatable` is overly
// conservative.
// static_assert(__builtin_is_cpp_trivially_relocatable(std::unique_ptr<txt::Paragraph>));
static_assert(__builtin_is_cpp_trivially_relocatable(ipl_paragraph_t));

static inline void validate(const ipl_paragraph_t* src) {
  assert(src != nullptr);
  assert(reinterpret_cast<intptr_t>(src) % alignof(ipl_paragraph_t) == 0);
}

static inline void validate(const std::unique_ptr<txt::Paragraph>* src) {
  assert(src != nullptr);
  assert(reinterpret_cast<intptr_t>(src) %
             alignof(std::unique_ptr<txt::Paragraph>) ==
         0);
}

[[maybe_unused]] static inline std::unique_ptr<txt::Paragraph>* transmute(
    ipl_paragraph_t* src) {
  validate(src);
  return reinterpret_cast<std::unique_ptr<txt::Paragraph>*>(src);
}

[[maybe_unused]] static inline const std::unique_ptr<txt::Paragraph>* transmute(
    const ipl_paragraph_t* src) {
  validate(src);
  return reinterpret_cast<const std::unique_ptr<txt::Paragraph>*>(src);
}

[[maybe_unused]] static inline ipl_paragraph_t* transmute(
    std::unique_ptr<txt::Paragraph>* src) {
  validate(src);
  return reinterpret_cast<ipl_paragraph_t*>(src);
}

[[maybe_unused]] static inline const ipl_paragraph_t* transmute(
    const std::unique_ptr<txt::Paragraph>* src) {
  validate(src);
  return reinterpret_cast<const ipl_paragraph_t*>(src);
}

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/txt/src/txt/paragraph.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/txt/src/skia/paragraph_builder_skia.h
// ---------------------------------------------------------------------------

// std::unique_ptr<txt::ParagraphBuilder>
static_assert(sizeof(std::unique_ptr<txt::ParagraphBuilder>) ==
              sizeof(ipl_paragraph_builder_t));
static_assert(alignof(std::unique_ptr<txt::ParagraphBuilder>) ==
              alignof(ipl_paragraph_builder_t));
// Manual check. `__builtin_is_cpp_trivially_relocatable` is overly
// conservative.
// static_assert(__builtin_is_cpp_trivially_relocatable(std::unique_ptr<txt::ParagraphBuilder>));
static_assert(__builtin_is_cpp_trivially_relocatable(ipl_paragraph_builder_t));

static inline void validate(const ipl_paragraph_builder_t* src) {
  assert(src != nullptr);
  assert(reinterpret_cast<intptr_t>(src) % alignof(ipl_paragraph_builder_t) ==
         0);
}

static inline void validate(const std::unique_ptr<txt::ParagraphBuilder>* src) {
  assert(src != nullptr);
  assert(reinterpret_cast<intptr_t>(src) %
             alignof(std::unique_ptr<txt::ParagraphBuilder>) ==
         0);
}

[[maybe_unused]] static inline std::unique_ptr<txt::ParagraphBuilder>*
transmute(ipl_paragraph_builder_t* src) {
  validate(src);
  return reinterpret_cast<std::unique_ptr<txt::ParagraphBuilder>*>(src);
}

[[maybe_unused]] static inline const std::unique_ptr<txt::ParagraphBuilder>*
transmute(const ipl_paragraph_builder_t* src) {
  validate(src);
  return reinterpret_cast<const std::unique_ptr<txt::ParagraphBuilder>*>(src);
}

[[maybe_unused]] static inline ipl_paragraph_builder_t* transmute(
    std::unique_ptr<txt::ParagraphBuilder>* src) {
  validate(src);
  return reinterpret_cast<ipl_paragraph_builder_t*>(src);
}

[[maybe_unused]] static inline const ipl_paragraph_builder_t* transmute(
    const std::unique_ptr<txt::ParagraphBuilder>* src) {
  validate(src);
  return reinterpret_cast<const ipl_paragraph_builder_t*>(src);
}

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/txt/src/skia/paragraph_builder_skia.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/impeller/typographer/typographer_context.h
// ---------------------------------------------------------------------------

static_assert(sizeof(std::shared_ptr<impeller::TypographerContext>) ==
              sizeof(ipl_typographer_context_t));
static_assert(alignof(std::shared_ptr<impeller::TypographerContext>) ==
              alignof(ipl_typographer_context_t));
// Manual check. `__builtin_is_cpp_trivially_relocatable` is overly
// conservative.
// static_assert(__builtin_is_cpp_trivially_relocatable(std::shared_ptr<impeller::TypographerContext>));
static_assert(
    __builtin_is_cpp_trivially_relocatable(ipl_typographer_context_t));

static inline void validate(const ipl_typographer_context_t* src) {
  assert(src != nullptr);
  assert(reinterpret_cast<intptr_t>(src) % alignof(ipl_typographer_context_t) ==
         0);
}

static inline void validate(
    const std::shared_ptr<impeller::TypographerContext>* src) {
  assert(src != nullptr);
  assert(reinterpret_cast<intptr_t>(src) %
             alignof(std::shared_ptr<impeller::TypographerContext>) ==
         0);
}

[[maybe_unused]] static inline std::shared_ptr<impeller::TypographerContext>*
transmute(ipl_typographer_context_t* src) {
  validate(src);
  return reinterpret_cast<std::shared_ptr<impeller::TypographerContext>*>(src);
}

[[maybe_unused]] static inline const std::shared_ptr<
    impeller::TypographerContext>*
transmute(const ipl_typographer_context_t* src) {
  validate(src);
  return reinterpret_cast<const std::shared_ptr<impeller::TypographerContext>*>(
      src);
}

[[maybe_unused]] static inline ipl_typographer_context_t* transmute(
    std::shared_ptr<impeller::TypographerContext>* src) {
  validate(src);
  return reinterpret_cast<ipl_typographer_context_t*>(src);
}

[[maybe_unused]] static inline const ipl_typographer_context_t* transmute(
    const std::shared_ptr<impeller::TypographerContext>* src) {
  validate(src);
  return reinterpret_cast<const ipl_typographer_context_t*>(src);
}

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/impeller/typographer/typographer_context.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/impeller/renderer/context.h
// ---------------------------------------------------------------------------

static_assert(sizeof(std::shared_ptr<impeller::Context>) ==
              sizeof(ipl_context_t));
static_assert(alignof(std::shared_ptr<impeller::Context>) ==
              alignof(ipl_context_t));
// Manual check. `__builtin_is_cpp_trivially_relocatable` is overly
// conservative.
// static_assert(__builtin_is_cpp_trivially_relocatable(std::shared_ptr<impeller::Context>));
static_assert(__builtin_is_cpp_trivially_relocatable(ipl_context_t));

static inline void validate(const ipl_context_t* src) {
  assert(src != nullptr);
  assert(reinterpret_cast<intptr_t>(src) % alignof(ipl_context_t) == 0);
}

static inline void validate(const std::shared_ptr<impeller::Context>* src) {
  assert(src != nullptr);
  assert(reinterpret_cast<intptr_t>(src) %
             alignof(std::shared_ptr<impeller::Context>) ==
         0);
}

[[maybe_unused]] static inline std::shared_ptr<impeller::Context>* transmute(
    ipl_context_t* src) {
  validate(src);
  return reinterpret_cast<std::shared_ptr<impeller::Context>*>(src);
}

[[maybe_unused]] static inline const std::shared_ptr<impeller::Context>*
transmute(const ipl_context_t* src) {
  validate(src);
  return reinterpret_cast<const std::shared_ptr<impeller::Context>*>(src);
}

[[maybe_unused]] static inline ipl_context_t* transmute(
    std::shared_ptr<impeller::Context>* src) {
  validate(src);
  return reinterpret_cast<ipl_context_t*>(src);
}

[[maybe_unused]] static inline const ipl_context_t* transmute(
    const std::shared_ptr<impeller::Context>* src) {
  validate(src);
  return reinterpret_cast<const ipl_context_t*>(src);
}

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/impeller/renderer/context.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/impeller/renderer/surface.h
// ---------------------------------------------------------------------------

static_assert(sizeof(std::unique_ptr<impeller::Surface>) ==
              sizeof(ipl_surface_t));
static_assert(alignof(std::unique_ptr<impeller::Surface>) ==
              alignof(ipl_surface_t));
// Manual check. `__builtin_is_cpp_trivially_relocatable` is overly
// conservative.
// static_assert(__builtin_is_cpp_trivially_relocatable(std::unique_ptr<impeller::Surface>));
static_assert(__builtin_is_cpp_trivially_relocatable(ipl_surface_t));

static inline void validate(const ipl_surface_t* src) {
  assert(src != nullptr);
  assert(reinterpret_cast<intptr_t>(src) % alignof(ipl_surface_t) == 0);
}

static inline void validate(const std::unique_ptr<impeller::Surface>* src) {
  assert(src != nullptr);
  assert(reinterpret_cast<intptr_t>(src) %
             alignof(std::unique_ptr<impeller::Surface>) ==
         0);
}

[[maybe_unused]] static inline std::unique_ptr<impeller::Surface>* transmute(
    ipl_surface_t* src) {
  validate(src);
  return reinterpret_cast<std::unique_ptr<impeller::Surface>*>(src);
}

[[maybe_unused]] static inline const std::unique_ptr<impeller::Surface>*
transmute(const ipl_surface_t* src) {
  validate(src);
  return reinterpret_cast<const std::unique_ptr<impeller::Surface>*>(src);
}

[[maybe_unused]] static inline ipl_surface_t* transmute(
    std::unique_ptr<impeller::Surface>* src) {
  validate(src);
  return reinterpret_cast<ipl_surface_t*>(src);
}

[[maybe_unused]] static inline const ipl_surface_t* transmute(
    const std::unique_ptr<impeller::Surface>* src) {
  validate(src);
  return reinterpret_cast<const ipl_surface_t*>(src);
}

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/impeller/renderer/surface.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/impeller/renderer/backend/vulkan/context_vk.h
// ---------------------------------------------------------------------------

static_assert(sizeof(std::shared_ptr<impeller::ContextVK>) ==
              sizeof(ipl_vk_context_t));
static_assert(alignof(std::shared_ptr<impeller::ContextVK>) ==
              alignof(ipl_vk_context_t));
// Manual check. `__builtin_is_cpp_trivially_relocatable` is overly
// conservative.
// static_assert(__builtin_is_cpp_trivially_relocatable(std::shared_ptr<impeller::ContextVK>));
static_assert(__builtin_is_cpp_trivially_relocatable(ipl_vk_context_t));

static inline void validate(const ipl_vk_context_t* src) {
  assert(src != nullptr);
  assert(reinterpret_cast<intptr_t>(src) % alignof(ipl_vk_context_t) == 0);
}

static inline void validate(const std::shared_ptr<impeller::ContextVK>* src) {
  assert(src != nullptr);
  assert(reinterpret_cast<intptr_t>(src) %
             alignof(std::shared_ptr<impeller::ContextVK>) ==
         0);
}

[[maybe_unused]] static inline std::shared_ptr<impeller::ContextVK>* transmute(
    ipl_vk_context_t* src) {
  validate(src);
  return reinterpret_cast<std::shared_ptr<impeller::ContextVK>*>(src);
}

[[maybe_unused]] static inline const std::shared_ptr<impeller::ContextVK>*
transmute(const ipl_vk_context_t* src) {
  validate(src);
  return reinterpret_cast<const std::shared_ptr<impeller::ContextVK>*>(src);
}

[[maybe_unused]] static inline ipl_vk_context_t* transmute(
    std::shared_ptr<impeller::ContextVK>* src) {
  validate(src);
  return reinterpret_cast<ipl_vk_context_t*>(src);
}

[[maybe_unused]] static inline const ipl_vk_context_t* transmute(
    const std::shared_ptr<impeller::ContextVK>* src) {
  validate(src);
  return reinterpret_cast<const ipl_vk_context_t*>(src);
}

static_assert(sizeof(impeller::ContextVK::Settings) ==
              sizeof(ipl_vk_context_settings_t));
static_assert(alignof(impeller::ContextVK::Settings) ==
              alignof(ipl_vk_context_settings_t));
// Manual check. `__builtin_is_cpp_trivially_relocatable` is overly
// conservative.
// static_assert(__builtin_is_cpp_trivially_relocatable(impeller::ContextVK::Settings));
static_assert(
    __builtin_is_cpp_trivially_relocatable(ipl_vk_context_settings_t));

static inline void validate(const ipl_vk_context_settings_t* src) {
  assert(src != nullptr);
  assert(reinterpret_cast<intptr_t>(src) % alignof(ipl_vk_context_settings_t) ==
         0);
}

static inline void validate(const impeller::ContextVK::Settings* src) {
  assert(src != nullptr);
  assert(reinterpret_cast<intptr_t>(src) %
             alignof(impeller::ContextVK::Settings) ==
         0);
}

[[maybe_unused]] static inline impeller::ContextVK::Settings* transmute(
    ipl_vk_context_settings_t* src) {
  validate(src);
  return reinterpret_cast<impeller::ContextVK::Settings*>(src);
}

[[maybe_unused]] static inline const impeller::ContextVK::Settings* transmute(
    const ipl_vk_context_settings_t* src) {
  validate(src);
  return reinterpret_cast<const impeller::ContextVK::Settings*>(src);
}

[[maybe_unused]] static inline ipl_vk_context_settings_t* transmute(
    impeller::ContextVK::Settings* src) {
  validate(src);
  return reinterpret_cast<ipl_vk_context_settings_t*>(src);
}

[[maybe_unused]] static inline const ipl_vk_context_settings_t* transmute(
    const impeller::ContextVK::Settings* src) {
  validate(src);
  return reinterpret_cast<const ipl_vk_context_settings_t*>(src);
}

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/impeller/renderer/backend/vulkan/context_vk.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN]
// engine/src/flutter/impeller/renderer/backend/vulkan/swapchain/swapchain_vk.h
// ---------------------------------------------------------------------------

static_assert(sizeof(std::shared_ptr<impeller::SwapchainVK>) ==
              sizeof(ipl_vk_swapchain_t));
static_assert(alignof(std::shared_ptr<impeller::SwapchainVK>) ==
              alignof(ipl_vk_swapchain_t));
// Manual check. `__builtin_is_cpp_trivially_relocatable` is overly
// conservative.
// static_assert(__builtin_is_cpp_trivially_relocatable(std::shared_ptr<impeller::SwapchainVK>));
static_assert(__builtin_is_cpp_trivially_relocatable(ipl_vk_swapchain_t));

static inline void validate(const ipl_vk_swapchain_t* src) {
  assert(src != nullptr);
  assert(reinterpret_cast<intptr_t>(src) % alignof(ipl_vk_swapchain_t) == 0);
}

static inline void validate(const std::shared_ptr<impeller::SwapchainVK>* src) {
  assert(src != nullptr);
  assert(reinterpret_cast<intptr_t>(src) %
             alignof(std::shared_ptr<impeller::SwapchainVK>) ==
         0);
}

[[maybe_unused]] static inline std::shared_ptr<impeller::SwapchainVK>*
transmute(ipl_vk_swapchain_t* src) {
  validate(src);
  return reinterpret_cast<std::shared_ptr<impeller::SwapchainVK>*>(src);
}

[[maybe_unused]] static inline const std::shared_ptr<impeller::SwapchainVK>*
transmute(const ipl_vk_swapchain_t* src) {
  validate(src);
  return reinterpret_cast<const std::shared_ptr<impeller::SwapchainVK>*>(src);
}

[[maybe_unused]] static inline ipl_vk_swapchain_t* transmute(
    std::shared_ptr<impeller::SwapchainVK>* src) {
  validate(src);
  return reinterpret_cast<ipl_vk_swapchain_t*>(src);
}

[[maybe_unused]] static inline const ipl_vk_swapchain_t* transmute(
    const std::shared_ptr<impeller::SwapchainVK>* src) {
  validate(src);
  return reinterpret_cast<const ipl_vk_swapchain_t*>(src);
}

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

// impeller::RenderTarget*
static_assert(sizeof(impeller::RenderTarget*) == sizeof(ipl_render_target_t));
static_assert(alignof(impeller::RenderTarget*) == alignof(ipl_render_target_t));
static_assert(__builtin_is_cpp_trivially_relocatable(impeller::RenderTarget*));
static_assert(__builtin_is_cpp_trivially_relocatable(ipl_render_target_t));

static inline void validate(const ipl_render_target_t src) {
  assert(src != nullptr);
}

static inline void validate(impeller::RenderTarget* src) {
  assert(src != nullptr);
}

[[maybe_unused]] static inline impeller::RenderTarget* transmute(
    ipl_render_target_t src) {
  validate(src);
  return reinterpret_cast<impeller::RenderTarget*>(src);
}

[[maybe_unused]] static inline ipl_render_target_t transmute(
    impeller::RenderTarget* src) {
  validate(src);
  return reinterpret_cast<ipl_render_target_t>(src);
}

// const impeller::RenderTarget*
static_assert(sizeof(const impeller::RenderTarget*) ==
              sizeof(ipl_const_render_target_t));
static_assert(alignof(const impeller::RenderTarget*) ==
              alignof(ipl_const_render_target_t));
static_assert(
    __builtin_is_cpp_trivially_relocatable(const impeller::RenderTarget*));
static_assert(
    __builtin_is_cpp_trivially_relocatable(ipl_const_render_target_t));

static inline void validate(const ipl_const_render_target_t src) {
  assert(src != nullptr);
}

static inline void validate(const impeller::RenderTarget* src) {
  assert(src != nullptr);
}

[[maybe_unused]] static inline const impeller::RenderTarget* transmute(
    ipl_const_render_target_t src) {
  validate(src);
  return reinterpret_cast<const impeller::RenderTarget*>(src);
}

[[maybe_unused]] static inline ipl_const_render_target_t transmute(
    const impeller::RenderTarget* src) {
  validate(src);
  return reinterpret_cast<ipl_const_render_target_t>(src);
}

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/impeller/entity/contents/content_context.h
// ---------------------------------------------------------------------------

static_assert(sizeof(std::unique_ptr<impeller::ContentContext>) ==
              sizeof(ipl_content_context_t));
static_assert(alignof(std::unique_ptr<impeller::ContentContext>) ==
              alignof(ipl_content_context_t));
// Manual check. `__builtin_is_cpp_trivially_relocatable` is overly
// conservative.
// static_assert(__builtin_is_cpp_trivially_relocatable(std::unique_ptr<impeller::ContentContext>));
static_assert(__builtin_is_cpp_trivially_relocatable(ipl_content_context_t));

static inline void validate(const ipl_content_context_t* src) {
  assert(src != nullptr);
  assert(reinterpret_cast<intptr_t>(src) % alignof(ipl_content_context_t) == 0);
}

static inline void validate(
    const std::unique_ptr<impeller::ContentContext>* src) {
  assert(src != nullptr);
  assert(reinterpret_cast<intptr_t>(src) %
             alignof(std::unique_ptr<impeller::ContentContext>) ==
         0);
}

[[maybe_unused]] static inline std::unique_ptr<impeller::ContentContext>*
transmute(ipl_content_context_t* src) {
  validate(src);
  return reinterpret_cast<std::unique_ptr<impeller::ContentContext>*>(src);
}

[[maybe_unused]] static inline const std::unique_ptr<impeller::ContentContext>*
transmute(const ipl_content_context_t* src) {
  validate(src);
  return reinterpret_cast<const std::unique_ptr<impeller::ContentContext>*>(
      src);
}

[[maybe_unused]] static inline ipl_content_context_t* transmute(
    std::unique_ptr<impeller::ContentContext>* src) {
  validate(src);
  return reinterpret_cast<ipl_content_context_t*>(src);
}

[[maybe_unused]] static inline const ipl_content_context_t* transmute(
    const std::unique_ptr<impeller::ContentContext>* src) {
  validate(src);
  return reinterpret_cast<const ipl_content_context_t*>(src);
}

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/impeller/entity/contents/content_context.h
// ---------------------------------------------------------------------------

// ===========================================================================
// [END] Type Checking And Type Conversion
// ===========================================================================

// ===========================================================================
// [BEGIN] Function Definition
// ===========================================================================

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/impeller/core/allocator.h
// ---------------------------------------------------------------------------

// std::shared_ptr<impeller::Allocator> destructor
void ipl_allocator_drop(ipl_allocator_t* self) {
  std::destroy_at(transmute(self));
}

// std::shared_ptr<impeller::Allocator> copy constructor
void ipl_allocator_clone(const ipl_allocator_t* self, ipl_allocator_t* out) {
  std::construct_at(transmute(out), *transmute(self));
}

// impeller::Allocator::CreateBuffer
bool ipl_allocator_create_buffer(const ipl_allocator_t* self,
                                 const ipl_device_buffer_descriptor_t* desc,
                                 ipl_device_buffer_t* out) {
  auto* device_buffer = std::construct_at(
      transmute(out), transmute(self)->get()->CreateBuffer(*transmute(desc)));
  return *device_buffer != nullptr;
}

// impeller::Allocator::CreateTexture
bool ipl_allocator_create_texture(const ipl_allocator_t* self,
                                  const ipl_texture_descriptor_t* desc,
                                  bool threadsafe,
                                  ipl_texture_t* out) {
  auto* texture = std::construct_at(
      transmute(out), transmute(self)->get()->CreateTexture(*transmute(desc)));
  return *texture != nullptr;
}

// impeller::Allocator::MinimumBytesPerRow
uint16_t ipl_allocator_minimum_bytes_per_row(const ipl_allocator_t* self,
                                             ipl_pixel_format_t format) {
  return transmute(self)->get()->MinimumBytesPerRow(transmute(format));
}

// impeller::Allocator::CreateBufferWithCopy
bool ipl_allocator_create_buffer_with_copy(const ipl_allocator_t* self,
                                           const uint8_t* buffer,
                                           size_t length,
                                           ipl_device_buffer_t* out) {
  assert(buffer != nullptr || length == 0);
  auto* device_buffer = std::construct_at(
      transmute(out),
      transmute(self)->get()->CreateBufferWithCopy(buffer, length));
  return *device_buffer != nullptr;
}

// impeller::Allocator::GetMaxTextureSizeSupported
void ipl_allocator_get_max_texture_size_supported(const ipl_allocator_t* self,
                                                  ipl_i64_size_t* out) {
  std::construct_at(transmute(out),
                    transmute(self)->get()->GetMaxTextureSizeSupported());
}

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/impeller/core/allocator.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/impeller/core/buffer_view.h
// ---------------------------------------------------------------------------

void ipl_buffer_view_drop(ipl_buffer_view_t* out) {
  std::destroy_at(transmute(out));
}

void ipl_buffer_view_get_range(const ipl_buffer_view_t* self,
                               ipl_range_t* out) {
  std::construct_at(transmute(out), transmute(self)->GetRange());
}

bool ipl_buffer_view_take_buffer(ipl_buffer_view_t* self,
                                 ipl_const_device_buffer_t* out) {
  auto* device_buffer =
      std::construct_at(transmute(out), transmute(self)->TakeBuffer());
  return *device_buffer != nullptr;
}

const ipl_device_buffer_descriptor_t*
ipl_buffer_view_get_device_buffer_descriptor(const ipl_buffer_view_t* self) {
  return transmute(&transmute(self)->GetBuffer()->GetDeviceBufferDescriptor());
}

uint8_t* ipl_buffer_view_on_get_contents(const ipl_buffer_view_t* self) {
  return transmute(self)->GetBuffer()->OnGetContents();
}

void ipl_buffer_view_flush(const ipl_buffer_view_t* self,
                           const ipl_range_t* range) {
  transmute(self)->GetBuffer()->Flush(
      range == nullptr ? std::nullopt : std::make_optional(*transmute(range)));
}

void ipl_buffer_view_invalidate(const ipl_buffer_view_t* self,
                                const ipl_range_t* range) {
  transmute(self)->GetBuffer()->Invalidate(
      range == nullptr ? std::nullopt : std::make_optional(*transmute(range)));
}

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/impeller/core/buffer_view.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/impeller/core/device_buffer.h
// ---------------------------------------------------------------------------

bool ipl_device_buffer_copy_host_buffer(const ipl_device_buffer_t* self,
                                        const uint8_t* source,
                                        const ipl_range_t* source_range,
                                        size_t offset) {
  return transmute(self)->get()->CopyHostBuffer(
      source, *transmute(source_range), offset);
}

bool ipl_device_buffer_set_label(const ipl_device_buffer_t* self,
                                 const char* ptr,
                                 size_t len) {
  return transmute(self)->get()->SetLabel(std::string_view{ptr, len});
}

void ipl_device_buffer_as_buffer_view(const ipl_device_buffer_t* self,
                                      ipl_buffer_view_t* out) {
  std::construct_at(transmute(out),
                    impeller::DeviceBuffer::AsBufferView(*transmute(self)));
}

const ipl_device_buffer_descriptor_t*
ipl_device_buffer_get_device_buffer_descriptor(
    const ipl_device_buffer_t* self) {
  return transmute(&transmute(self)->get()->GetDeviceBufferDescriptor());
}

uint8_t* ipl_device_buffer_on_get_contents(const ipl_device_buffer_t* self) {
  return transmute(self)->get()->OnGetContents();
}

void ipl_device_buffer_flush(const ipl_device_buffer_t* self,
                             const ipl_range_t* range) {
  transmute(self)->get()->Flush(
      range == nullptr ? std::nullopt : std::make_optional(*transmute(range)));
}

void ipl_device_buffer_invalidate(const ipl_device_buffer_t* self,
                                  const ipl_range_t* range) {
  transmute(self)->get()->Invalidate(
      range == nullptr ? std::nullopt : std::make_optional(*transmute(range)));
}

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/impeller/core/device_buffer.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/impeller/core/host_buffer.h
// ---------------------------------------------------------------------------

void ipl_host_buffer_drop(ipl_host_buffer_t* self) {
  std::destroy_at(transmute(self));
}

bool ipl_host_buffer_emplace(const ipl_host_buffer_t* self,
                             const void* buffer,
                             size_t length,
                             size_t align,
                             ipl_buffer_view_t* out) {
  auto* buffer_view = std::construct_at(
      transmute(out), transmute(self)->get()->Emplace(buffer, length, align));
  return static_cast<bool>(buffer_view);
}

size_t ipl_host_buffer_get_minimum_uniform_alignment(
    const ipl_host_buffer_t* self) {
  return transmute(self)->get()->GetMinimumUniformAlignment();
}

void ipl_host_buffer_reset(const ipl_host_buffer_t* self) {
  transmute(self)->get()->Reset();
}

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/impeller/core/host_buffer.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/impeller/core/texture.h
// ---------------------------------------------------------------------------

void ipl_texture_drop(ipl_texture_t* self) {
  std::destroy_at(transmute(self));
}

void ipl_texture_clone(const ipl_texture_t* self, ipl_texture_t* out) {
  std::construct_at(transmute(out), *transmute(self));
}

void ipl_texture_set_label(const ipl_texture_t* self,
                           const char* ptr,
                           size_t len) {
  transmute(self)->get()->SetLabel(std::string_view{ptr, len});
}

void ipl_texture_get_size(const ipl_texture_t* self, ipl_i64_size_t* out) {
  std::construct_at(transmute(out), transmute(self)->get()->GetSize());
}

bool ipl_texture_is_opaque(const ipl_texture_t* self) {
  return transmute(self)->get()->IsOpaque();
}

size_t ipl_texture_get_mip_count(const ipl_texture_t* self) {
  return transmute(self)->get()->GetMipCount();
}

const ipl_texture_descriptor_t* ipl_texture_get_texture_descriptor(
    const ipl_texture_t* self) {
  return transmute(&transmute(self)->get()->GetTextureDescriptor());
}

bool ipl_texture_needs_mipmap_generation(const ipl_texture_t* self) {
  return transmute(self)->get()->NeedsMipmapGeneration();
}

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
                   ipl_color_t* out) {
  std::construct_at(transmute(out), alpha, red, green, blue,
                    transmute(color_space));
}

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/display_list/dl_color.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/display_list/effects/dl_color_filter.h
// ---------------------------------------------------------------------------

bool ipl_color_filter_new_blend(const ipl_color_t* color,
                                ipl_blend_mode_t mode,
                                ipl_const_color_filter_t* out) {
  return std::construct_at(
      transmute(out),
      flutter::DlColorFilter::MakeBlend(*transmute(color), transmute(mode)));
}

bool ipl_color_filter_new_matrix(const float matrix[20],
                                 ipl_const_color_filter_t* out) {
  return std::construct_at(transmute(out),
                           flutter::DlColorFilter::MakeMatrix(matrix));
}

void ipl_color_filter_new_srgb_to_linear_gamma(ipl_const_color_filter_t* out) {
  std::construct_at(transmute(out),
                    flutter::DlColorFilter::MakeSrgbToLinearGamma());
}

void ipl_color_filter_new_linear_to_srgb_gamma(ipl_const_color_filter_t* out) {
  std::construct_at(transmute(out),
                    flutter::DlColorFilter::MakeLinearToSrgbGamma());
}

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/display_list/effects/dl_color_filter.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/display_list/effects/dl_color_source.h
// ---------------------------------------------------------------------------

void ipl_color_source_drop(ipl_color_source_t* self) {
  std::destroy_at(transmute(self));
}

bool ipl_color_source_new_image(const ipl_const_image_t* image,
                                ipl_tile_mode_t horizontal_tile_mode,
                                ipl_tile_mode_t vertical_tile_mode,
                                ipl_image_sampling_t sampling,
                                const ipl_matrix_t* matrix,
                                ipl_color_source_t* out) {
  auto* color_source = std::construct_at(
      transmute(out), flutter::DlColorSource::MakeImage(
                          *transmute(image), transmute(horizontal_tile_mode),
                          transmute(vertical_tile_mode), transmute(sampling),
                          transmute(matrix, false)));
  return *color_source != nullptr;
}

bool ipl_color_source_new_linear(const ipl_f32_point_t* start_point,
                                 const ipl_f32_point_t* end_point,
                                 uint32_t stop_count,
                                 const ipl_color_t* colors,
                                 const float* stops,
                                 ipl_tile_mode_t tile_mode,
                                 const ipl_matrix_t* matrix,
                                 ipl_color_source_t* out) {
  auto* color_source = std::construct_at(
      transmute(out), flutter::DlColorSource::MakeLinear(
                          *transmute(start_point), *transmute(end_point),
                          stop_count, transmute(colors), stops,
                          transmute(tile_mode), transmute(matrix, false)));
  return *color_source != nullptr;
}

bool ipl_color_source_new_radial(const ipl_f32_point_t* center,
                                 float radius,
                                 uint32_t stop_count,
                                 const ipl_color_t* colors,
                                 const float* stops,
                                 ipl_tile_mode_t tile_mode,
                                 const ipl_matrix_t* matrix,
                                 ipl_color_source_t* out) {
  auto* color_source = std::construct_at(
      transmute(out),
      flutter::DlColorSource::MakeRadial(
          *transmute(center), radius, stop_count, transmute(colors), stops,
          transmute(tile_mode), transmute(matrix, false)));
  return *color_source != nullptr;
}

bool ipl_color_source_new_conical(const ipl_f32_point_t* start_center,
                                  float start_radius,
                                  const ipl_f32_point_t* end_center,
                                  float end_radius,
                                  uint32_t stop_count,
                                  const ipl_color_t* colors,
                                  const float* stops,
                                  ipl_tile_mode_t tile_mode,
                                  const ipl_matrix_t* matrix,
                                  ipl_color_source_t* out) {
  auto* color_source = std::construct_at(
      transmute(out),
      flutter::DlColorSource::MakeConical(
          *transmute(start_center), start_radius, *transmute(end_center),
          end_radius, stop_count, transmute(colors), stops,
          transmute(tile_mode), transmute(matrix, false)));
  return *color_source != nullptr;
}

bool ipl_color_source_new_sweep(const ipl_f32_point_t* center,
                                float start,
                                float end,
                                uint32_t stop_count,
                                const ipl_color_t* colors,
                                const float* stops,
                                ipl_tile_mode_t tile_mode,
                                const ipl_matrix_t* matrix,
                                ipl_color_source_t* out) {
  auto* color_source = std::construct_at(
      transmute(out),
      flutter::DlColorSource::MakeSweep(
          *transmute(center), start, end, stop_count, transmute(colors), stops,
          transmute(tile_mode), transmute(matrix, false)));
  return *color_source != nullptr;
}

// flutter::DlColorSource::MakeRuntimeEffect

bool ipl_color_source_is_opaque(const ipl_color_source_t* self) {
  return transmute(self)->get()->is_opaque();
}

void ipl_const_color_source_drop(ipl_const_color_source_t* self) {
  std::destroy_at(transmute(self));
}

bool ipl_const_color_source_is_opaque(const ipl_const_color_source_t* self) {
  return transmute(self)->get()->is_opaque();
}

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/display_list/effects/dl_color_source.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/display_list/dl_image_filter.h
// ---------------------------------------------------------------------------

void ipl_image_filter_drop(ipl_image_filter_t* self) {
  std::destroy_at(transmute(self));
}

bool ipl_image_filter_new_blur(float sigma_x,
                               float sigma_y,
                               ipl_tile_mode_t tile_mode,
                               ipl_image_filter_t* out) {
  auto* image_filter = std::construct_at(
      transmute(out),
      flutter::DlImageFilter::MakeBlur(sigma_x, sigma_y, transmute(tile_mode)));
  return *image_filter != nullptr;
}

bool ipl_image_filter_new_dilate(float radius_x,
                                 float radius_y,
                                 ipl_image_filter_t* out) {
  auto* image_filter = std::construct_at(
      transmute(out), flutter::DlImageFilter::MakeDilate(radius_x, radius_y));
  return *image_filter != nullptr;
}

bool ipl_image_filter_new_erode(float radius_x,
                                float radius_y,
                                ipl_image_filter_t* out) {
  auto* image_filter = std::construct_at(
      transmute(out), flutter::DlImageFilter::MakeErode(radius_x, radius_y));
  return *image_filter != nullptr;
}

bool ipl_image_filter_new_matrix(const ipl_matrix_t* matrix,
                                 ipl_image_sampling_t sampling,
                                 ipl_image_filter_t* out) {
  auto* image_filter = std::construct_at(
      transmute(out), flutter::DlImageFilter::MakeMatrix(*transmute(matrix),
                                                         transmute(sampling)));
  return *image_filter != nullptr;
}

// flutter::DlImageFilter::MakeRuntimeEffect

bool ipl_image_filter_new_color_filter(const ipl_const_color_filter_t* filter,
                                       ipl_image_filter_t* out) {
  auto* image_filter = std::construct_at(
      transmute(out),
      flutter::DlImageFilter::MakeColorFilter(*transmute(filter)));
  return *image_filter != nullptr;
}

bool ipl_image_filter_new_compose(const ipl_image_filter_t* outer,
                                  const ipl_image_filter_t* inner,
                                  ipl_image_filter_t* out) {
  auto* image_filter = std::construct_at(
      transmute(out), flutter::DlImageFilter::MakeCompose(*transmute(outer),
                                                          *transmute(inner)));
  return *image_filter != nullptr;
}

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/display_list/dl_image_filter.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/display_list/dl_mask_filter.h
// ---------------------------------------------------------------------------

void ipl_mask_filter_drop(ipl_mask_filter_t* self) {
  std::destroy_at(transmute(self));
}

bool ipl_mask_filter_new_blur(ipl_blur_style_t style,
                              float sigma,
                              bool respect_ctm,
                              ipl_mask_filter_t* out) {
  auto* mask_filter = std::construct_at(
      transmute(out),
      flutter::DlBlurMaskFilter::Make(transmute(style), sigma, respect_ctm));
  return *mask_filter != nullptr;
}

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/display_list/dl_mask_filter.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/display_list/dl_image.h
// ---------------------------------------------------------------------------

void ipl_image_drop(ipl_image_t* self) {
  std::destroy_at(transmute(self));
}

bool ipl_image_new(const ipl_texture_t* texture, ipl_image_t* out) {
  auto* image = std::construct_at(
      transmute(out), impeller::DlImageImpeller::Make(*transmute(texture)));
  return *image == nullptr;
}

// DlImageImpeller::GetImpellerTexture

ipl_color_space_t ipl_image_get_color_space(const ipl_image_t* self) {
  return transmute(transmute(self)->get()->GetColorSpace());
}

bool ipl_image_is_opaque(const ipl_image_t* self) {
  return transmute(self)->get()->isOpaque();
}

void ipl_image_get_size(const ipl_image_t* self, ipl_i64_size_t* out) {
  std::construct_at(transmute(out), transmute(self)->get()->GetSize());
}

size_t ipl_image_get_approximate_byte_size(const ipl_image_t* self) {
  return transmute(self)->get()->GetApproximateByteSize();
}

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/display_list/dl_image.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/display_list/dl_paint.h
// ---------------------------------------------------------------------------

void ipl_paint_drop(ipl_paint_t* self) {
  std::destroy_at(transmute(self));
}

void ipl_paint_new(const ipl_color_t* color, ipl_paint_t* out) {
  std::construct_at(transmute(out), *transmute(color));
}

bool ipl_paint_is_anti_alias(const ipl_paint_t* self) {
  return transmute(self)->isAntiAlias();
}

void ipl_paint_set_anti_alias(ipl_paint_t* self, bool is_anti_alias) {
  transmute(self)->setAntiAlias(is_anti_alias);
}

bool ipl_paint_is_invert_colors(const ipl_paint_t* self) {
  return transmute(self)->isInvertColors();
}

void ipl_paint_set_invert_colors(ipl_paint_t* self, bool is_invert_colors) {
  transmute(self)->setInvertColors(is_invert_colors);
}

void ipl_paint_get_color(const ipl_paint_t* self, ipl_color_t* out) {
  std::construct_at(transmute(out), transmute(self)->getColor());
}

void ipl_paint_set_color(ipl_paint_t* self, const ipl_color_t* color) {
  transmute(self)->setColor(*transmute(color));
}

uint8_t ipl_paint_get_alpha(const ipl_paint_t* self) {
  return transmute(self)->getAlpha();
}

void ipl_paint_set_alpha(ipl_paint_t* self, uint8_t alpha) {
  transmute(self)->setAlpha(alpha);
}

float ipl_paint_get_opacity(const ipl_paint_t* self) {
  return transmute(self)->getOpacity();
}

void ipl_paint_set_opacity(ipl_paint_t* self, float opacity) {
  transmute(self)->setOpacity(opacity);
}

ipl_blend_mode_t ipl_paint_get_blend_mode(const ipl_paint_t* self) {
  return transmute(transmute(self)->getBlendMode());
}

void ipl_paint_set_blend_mode(ipl_paint_t* self, ipl_blend_mode_t mode) {
  transmute(self)->setBlendMode(transmute(mode));
}

ipl_draw_style_t ipl_paint_get_draw_style(const ipl_paint_t* self) {
  return transmute(transmute(self)->getDrawStyle());
}

void ipl_paint_set_draw_style(ipl_paint_t* self, ipl_draw_style_t style) {
  transmute(self)->setDrawStyle(transmute(style));
}

ipl_stroke_cap_t ipl_paint_get_stroke_cap(const ipl_paint_t* self) {
  return transmute(transmute(self)->getStrokeCap());
}

void ipl_paint_set_stroke_cap(ipl_paint_t* self, ipl_stroke_cap_t cap) {
  transmute(self)->setStrokeCap(transmute(cap));
}

ipl_stroke_join_t ipl_paint_get_stroke_join(const ipl_paint_t* self) {
  return transmute(transmute(self)->getStrokeJoin());
}

void ipl_paint_set_stroke_join(ipl_paint_t* self, ipl_stroke_join_t join) {
  transmute(self)->setStrokeJoin(transmute(join));
}

float ipl_paint_get_stroke_width(const ipl_paint_t* self) {
  return transmute(self)->getStrokeWidth();
}

void ipl_paint_set_stroke_width(ipl_paint_t* self, float width) {
  transmute(self)->setStrokeWidth(width);
}

float ipl_paint_get_stroke_miter(const ipl_paint_t* self) {
  return transmute(self)->getStrokeMiter();
}

void ipl_paint_set_stroke_miter(ipl_paint_t* self, float miter) {
  transmute(self)->setStrokeMiter(miter);
}

const ipl_const_color_source_t* ipl_paint_get_color_source(
    const ipl_paint_t* self) {
  return transmute(&transmute(self)->getColorSource());
}

void ipl_paint_set_color_source(ipl_paint_t* self,
                                const ipl_const_color_source_t* source) {
  transmute(self)->setColorSource(*transmute(source));
}

const ipl_const_color_filter_t* ipl_paint_get_color_filter(
    const ipl_paint_t* self) {
  return transmute(&transmute(self)->getColorFilter());
}

void ipl_paint_set_color_filter(ipl_paint_t* self,
                                const ipl_const_color_filter_t* filter) {
  transmute(self)->setColorFilter(*transmute(filter));
}

const ipl_image_filter_t* ipl_paint_get_image_filter(const ipl_paint_t* self) {
  return transmute(&transmute(self)->getImageFilter());
}

void ipl_paint_set_image_filter(ipl_paint_t* self,
                                const ipl_image_filter_t* filter) {
  transmute(self)->setImageFilter(*transmute(filter));
}

const ipl_const_mask_filter_t* ipl_paint_get_mask_filter(
    const ipl_paint_t* self) {
  return transmute(&transmute(self)->getMaskFilter());
}

void ipl_paint_set_mask_filter(ipl_paint_t* self,
                               const ipl_mask_filter_t* filter) {
  transmute(self)->setMaskFilter(*transmute(filter));
}

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/display_list/dl_paint.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/display_list/dl_path.h
// ---------------------------------------------------------------------------

void ipl_path_drop(ipl_path_t* self) {
  std::destroy_at(transmute(self));
}

void ipl_path_new_rec(const ipl_f32_rect_t* rect, ipl_path_t* out) {
  std::construct_at(transmute(out),
                    flutter::DlPath::MakeRect(*transmute(rect)));
}

void ipl_path_new_rect_ltrb(float left,
                            float top,
                            float right,
                            float bottom,
                            ipl_path_t* out) {
  std::construct_at(transmute(out),
                    flutter::DlPath::MakeRectLTRB(left, top, right, bottom));
}

void ipl_path_new_rect_xywh(float x,
                            float y,
                            float width,
                            float height,
                            ipl_path_t* out) {
  std::construct_at(transmute(out),
                    flutter::DlPath::MakeRectXYWH(x, y, width, height));
}

void ipl_path_new_oval(const ipl_f32_rect_t* bounds, ipl_path_t* out) {
  std::construct_at(transmute(out),
                    flutter::DlPath::MakeOval(*transmute(bounds)));
}

void ipl_path_new_oval_ltrb(float left,
                            float top,
                            float right,
                            float bottom,
                            ipl_path_t* out) {
  std::construct_at(transmute(out),
                    flutter::DlPath::MakeOvalLTRB(left, top, right, bottom));
}

void ipl_path_new_circle(const ipl_f32_point_t* center,
                         float radius,
                         ipl_path_t* out) {
  std::construct_at(transmute(out),
                    flutter::DlPath::MakeCircle(*transmute(center), radius));
}

void ipl_path_new_round_rect(const ipl_round_rect_t* rrect, ipl_path_t* out) {
  std::construct_at(transmute(out),
                    flutter::DlPath::MakeRoundRect(*transmute(rrect)));
}

void ipl_path_new_round_rect_xy(const ipl_f32_rect_t* rect,
                                float x_radius,
                                float y_radius,
                                bool counter_clock_wise,
                                ipl_path_t* out) {
  std::construct_at(transmute(out), flutter::DlPath::MakeRoundRectXY(
                                        *transmute(rect), x_radius, y_radius));
}

// flutter::DlPath::MakeRoundSuperellipse

void ipl_path_new_line(const ipl_f32_point_t* a,
                       const ipl_f32_point_t* b,
                       ipl_path_t* out) {
  std::construct_at(transmute(out),
                    flutter::DlPath::MakeLine(*transmute(a), *transmute(b)));
}

void ipl_path_new_poly(const ipl_f32_point_t* pts,
                       int count,
                       bool close,
                       ipl_path_fill_type_t fill_type,
                       ipl_path_t* out) {
  std::construct_at(transmute(out),
                    flutter::DlPath::MakePoly(transmute(pts), count, close,
                                              transmute(fill_type)));
}

void ipl_path_new_arc(const ipl_f32_rect_t* bounds,
                      float start,
                      float sweep,
                      bool use_center,
                      ipl_path_t* out) {
  std::construct_at(
      transmute(out),
      flutter::DlPath::MakeArc(*transmute(bounds), flutter::DlDegrees(start),
                               flutter::DlDegrees(sweep), use_center));
}

void ipl_path_with_offset(const ipl_path_t* self,
                          const ipl_f32_point_t* offset,
                          ipl_path_t* out) {
  std::construct_at(transmute(out),
                    transmute(self)->WithOffset(*transmute(offset)));
}

void ipl_path_with_fill_type(const ipl_path_t* self,
                             ipl_path_fill_type_t type,
                             ipl_path_t* out) {
  std::construct_at(transmute(out),
                    transmute(self)->WithFillType(transmute(type)));
}

bool ipl_path_is_empty(const ipl_path_t* self) {
  return transmute(self)->IsEmpty();
}

bool ipl_path_is_rect(const ipl_path_t* self,
                      ipl_f32_rect_t* rect,
                      bool* is_closed) {
  return transmute(self)->IsRect(transmute(rect, false), is_closed);
}

bool ipl_path_is_oval(const ipl_path_t* self, ipl_f32_rect_t* bounds) {
  return transmute(self)->IsOval(transmute(bounds));
}

bool ipl_path_is_line(const ipl_path_t* self,
                      ipl_f32_point_t* start,
                      ipl_f32_point_t* end) {
  return transmute(self)->IsLine(transmute(start, false),
                                 transmute(end, false));
}

bool ipl_path_is_round_rect(const ipl_path_t* self, ipl_round_rect_t* rrect) {
  return transmute(self)->IsRoundRect(transmute(rrect, false));
}

bool ipl_path_contains(const ipl_path_t* self, const ipl_f32_point_t* point) {
  return transmute(self)->Contains(*transmute(point));
}

void ipl_path_get_bounds(const ipl_path_t* self, ipl_f32_rect_t* out) {
  std::construct_at(transmute(out), transmute(self)->GetBounds());
}

ipl_path_fill_type_t ipl_path_get_fill_type(const ipl_path_t* self) {
  return transmute(transmute(self)->GetFillType());
}

bool ipl_path_operator_equal(const ipl_path_t* self, const ipl_path_t* other) {
  return *transmute(self) == *transmute(other);
}

bool ipl_path_is_volatile(const ipl_path_t* self) {
  return transmute(self)->IsVolatile();
}

bool ipl_path_is_convex(const ipl_path_t* self) {
  return transmute(self)->IsConvex();
}

void ipl_path_operator_add(const ipl_path_t* self,
                           const ipl_path_t* other,
                           ipl_path_t* out) {
  std::construct_at(transmute(out), *transmute(self) + *transmute(other));
}

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/display_list/dl_path.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/display_list/dl_text.h
// ---------------------------------------------------------------------------

void ipl_text_drop(ipl_text_t* self) {
  std::destroy_at(transmute(self));
}

void ipl_text_get_bounds(const ipl_text_t* self, ipl_f32_rect_t* out) {
  std::construct_at(transmute(out), transmute(self)->get()->GetBounds());
}

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/display_list/dl_text.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/display_list/display_list.h
// ---------------------------------------------------------------------------

void ipl_display_list_drop(ipl_display_list_t* self) {
  std::destroy_at(transmute(self));
}

void ipl_display_list_get_bounds(const ipl_display_list_t* self,
                                 ipl_f32_rect_t* out) {
  std::construct_at(transmute(out), transmute(self)->get()->GetBounds());
}

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/display_list/display_list.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/display_list/dl_path_builder.h
// ---------------------------------------------------------------------------

void ipl_path_builder_drop(ipl_path_builder_t* self) {
  std::destroy_at(transmute(self));
}

ipl_path_builder_t* ipl_path_builder_set_fill_type(
    ipl_path_builder_t* self,
    ipl_path_fill_type_t fill_type) {
  transmute(self)->SetFillType(transmute(fill_type));
  return self;
}

ipl_path_builder_t* ipl_path_builder_move_to(ipl_path_builder_t* self,
                                             const ipl_f32_point_t* p2) {
  transmute(self)->MoveTo(*transmute(p2));
  return self;
}

ipl_path_builder_t* ipl_path_builder_line_to(ipl_path_builder_t* self,
                                             const ipl_f32_point_t* p2) {
  transmute(self)->LineTo(*transmute(p2));
  return self;
}

ipl_path_builder_t* ipl_path_builder_quadratic_curve_to(
    ipl_path_builder_t* self,
    const ipl_f32_point_t* cp,
    const ipl_f32_point_t* p2) {
  transmute(self)->QuadraticCurveTo(*transmute(cp), *transmute(p2));
  return self;
}

ipl_path_builder_t* ipl_path_builder_conic_curve_to(ipl_path_builder_t* self,
                                                    const ipl_f32_point_t* cp,
                                                    const ipl_f32_point_t* p2,
                                                    float weight) {
  transmute(self)->ConicCurveTo(*transmute(cp), *transmute(p2), weight);
  return self;
}

ipl_path_builder_t* ipl_path_builder_cubic_curve_to(ipl_path_builder_t* self,
                                                    const ipl_f32_point_t* cp1,
                                                    const ipl_f32_point_t* cp2,
                                                    const ipl_f32_point_t* p2) {
  transmute(self)->CubicCurveTo(*transmute(cp1), *transmute(cp2),
                                *transmute(p2));
  return self;
}

ipl_path_builder_t* ipl_path_builder_close(ipl_path_builder_t* self) {
  transmute(self)->Close();
  return self;
}

ipl_path_builder_t* ipl_path_builder_add_rect(ipl_path_builder_t* self,
                                              const ipl_f32_rect_t* rect) {
  transmute(self)->AddRect(*transmute(rect));
  return self;
}

ipl_path_builder_t* ipl_path_builder_add_oval(ipl_path_builder_t* self,
                                              const ipl_f32_rect_t* bounds) {
  transmute(self)->AddOval(*transmute(bounds));
  return self;
}

ipl_path_builder_t* ipl_path_builder_add_circle(ipl_path_builder_t* self,
                                                const ipl_f32_point_t* center,
                                                float radius) {
  transmute(self)->AddCircle(*transmute(center), radius);
  return self;
}

ipl_path_builder_t* ipl_path_builder_add_round_rect(
    ipl_path_builder_t* self,
    const ipl_round_rect_t* round_rect) {
  transmute(self)->AddRoundRect(*transmute(round_rect));
  return self;
}

// flutter::DlPathBuilder::AddRoundSuperellipse

ipl_path_builder_t* ipl_path_builder_add_arc(ipl_path_builder_t* self,
                                             const ipl_f32_rect_t* bounds,
                                             float start,
                                             float sweep,
                                             bool use_center) {
  transmute(self)->AddArc(*transmute(bounds), flutter::DlDegrees(start),
                          flutter::DlDegrees(sweep), use_center);
  return self;
}

ipl_path_builder_t* ipl_path_builder_add_path(ipl_path_builder_t* self,
                                              const ipl_path_t* path) {
  transmute(self)->AddPath(*transmute(path));
  return self;
}

void ipl_path_builder_copy_path(ipl_path_builder_t* self, ipl_path_t* out) {
  std::construct_at(transmute(out), transmute(self)->CopyPath());
}

void ipl_path_builder_take_path(ipl_path_builder_t* self, ipl_path_t* out) {
  std::construct_at(transmute(out), transmute(self)->TakePath());
}

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/display_list/dl_path_builder.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/display_list/dl_builder.h
// ---------------------------------------------------------------------------

void ipl_display_list_builder_drop(ipl_display_list_builder_t* self) {
  std::destroy_at(transmute(self));
}

void ipl_display_list_builder_new(const ipl_f32_rect_t* cull_rect,
                                  bool prepare_rtree,
                                  ipl_display_list_builder_t* out) {
  std::construct_at(transmute(out), sk_make_sp<flutter::DisplayListBuilder>(
                                        *transmute(cull_rect), prepare_rtree));
}

void ipl_display_list_builder_get_base_layer_dimensions(
    const ipl_display_list_builder_t* self,
    ipl_i64_size_t* out) {
  std::construct_at(transmute(out),
                    transmute(self)->get()->GetBaseLayerDimensions());
}

// flutter::DisplayListBuilder::GetRecordCount
size_t ipl_display_list_builder_get_record_count(
    const ipl_display_list_builder_t* self) {
  return transmute(self)->get()->GetRecordCount();
}

// flutter::DisplayListBuilder::IsEmpty
bool ipl_display_list_builder_is_empty(const ipl_display_list_builder_t* self) {
  return transmute(self)->get()->IsEmpty();
}

// flutter::DisplayListBuilder::Save
void ipl_display_list_builder_save(const ipl_display_list_builder_t* self) {
  transmute(self)->get()->Save();
}

void ipl_display_list_builder_save_layer(const ipl_display_list_builder_t* self,
                                         const ipl_f32_rect_t* bounds,
                                         const ipl_paint_t* paint,
                                         const ipl_image_filter_t* backdrop,
                                         const int64_t* backdrop_id) {
  transmute(self)->get()->SaveLayer(
      *transmute(bounds), transmute(paint, false),
      backdrop == nullptr ? nullptr : transmute(backdrop)->get(),
      backdrop_id == nullptr ? std::nullopt : std::make_optional(*backdrop_id));
}

// flutter::DisplayListBuilder::Restore
void ipl_display_list_builder_restore(const ipl_display_list_builder_t* self) {
  transmute(self)->get()->Restore();
}

// flutter::DisplayListBuilder::GetSaveCount
int ipl_display_list_builder_get_save_count(
    const ipl_display_list_builder_t* self) {
  return transmute(self)->get()->GetSaveCount();
}

// flutter::DisplayListBuilder::RestoreToCount
void ipl_display_list_builder_restore_to_count(
    const ipl_display_list_builder_t* self,
    int restore_count) {
  transmute(self)->get()->RestoreToCount(restore_count);
}

// flutter::DisplayListBuilder::Translate
void ipl_display_list_builder_translate(const ipl_display_list_builder_t* self,
                                        float tx,
                                        float ty) {
  transmute(self)->get()->Translate(tx, ty);
}

// flutter::DisplayListBuilder::Scale
void ipl_display_list_builder_scale(const ipl_display_list_builder_t* self,
                                    float sx,
                                    float sy) {
  transmute(self)->get()->Scale(sx, sy);
}

// flutter::DisplayListBuilder::Rotate
void ipl_display_list_builder_rotate(const ipl_display_list_builder_t* self,
                                     float degrees) {
  transmute(self)->get()->Rotate(degrees);
}

// flutter::DisplayListBuilder::Skew
void ipl_display_list_builder_skew(const ipl_display_list_builder_t* self,
                                   float sx,
                                   float sy) {
  transmute(self)->get()->Skew(sx, sy);
}

// flutter::DisplayListBuilder::Transform2DAffine
void ipl_display_list_builder_transform_2d_affine(
    const ipl_display_list_builder_t* self,
    float mxx,
    float mxy,
    float mxt,
    float myx,
    float myy,
    float myt) {
  transmute(self)->get()->Transform2DAffine(mxx, mxy, mxt, myx, myy, myt);
}

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
    float mwt) {
  transmute(self)->get()->TransformFullPerspective(mxx, mxy, mxz, mxt, myx, myy,
                                                   myz, myt, mzx, mzy, mzz, mzt,
                                                   mwx, mwy, mwz, mwt);
}

// flutter::DisplayListBuilder::TransformReset
void ipl_display_list_builder_transform_reset(
    const ipl_display_list_builder_t* self) {
  transmute(self)->get()->TransformReset();
}

// flutter::DisplayListBuilder::Transform
void ipl_display_list_builder_transform(const ipl_display_list_builder_t* self,
                                        const ipl_matrix_t* matrix) {
  transmute(self)->get()->Transform(*transmute(matrix));
}

// flutter::DisplayListBuilder::SetTransform
void ipl_display_list_builder_set_transform(
    const ipl_display_list_builder_t* self,
    const ipl_matrix_t* matrix) {
  transmute(self)->get()->SetTransform(*transmute(matrix));
}

// flutter::DisplayListBuilder::GetMatrix
void ipl_display_list_builder_get_matrix(const ipl_display_list_builder_t* self,
                                         ipl_matrix_t* out) {
  std::construct_at(transmute(out), transmute(self)->get()->GetMatrix());
}

void ipl_display_list_builder_clip_rect(const ipl_display_list_builder_t* self,
                                        const ipl_f32_rect_t* rect,
                                        ipl_clip_op_t clip_op,
                                        bool is_aa) {
  transmute(self)->get()->ClipRect(*transmute(rect), transmute(clip_op), is_aa);
}

void ipl_display_list_builder_clip_oval(const ipl_display_list_builder_t* self,
                                        const ipl_f32_rect_t* bounds,
                                        ipl_clip_op_t clip_op,
                                        bool is_aa) {
  transmute(self)->get()->ClipOval(*transmute(bounds), transmute(clip_op),
                                   is_aa);
}

void ipl_display_list_builder_clip_round_rect(
    const ipl_display_list_builder_t* self,
    const ipl_round_rect_t* rrect,
    ipl_clip_op_t clip_op,
    bool is_aa) {
  transmute(self)->get()->ClipRoundRect(*transmute(rrect), transmute(clip_op),
                                        is_aa);
}

// DisplayListBuilder::ClipRoundSuperellipse

void ipl_display_list_builder_clip_path(const ipl_display_list_builder_t* self,
                                        const ipl_path_t* path,
                                        ipl_clip_op_t clip_op,
                                        bool is_aa) {
  transmute(self)->get()->ClipPath(*transmute(path), transmute(clip_op), is_aa);
}

void ipl_display_list_builder_get_destination_clip_coverage(
    const ipl_display_list_builder_t* self,
    ipl_f32_rect_t* out) {
  std::construct_at(transmute(out),
                    transmute(self)->get()->GetDestinationClipCoverage());
}

void ipl_display_list_builder_get_local_clip_coverage(
    const ipl_display_list_builder_t* self,
    ipl_f32_rect_t* out) {
  std::construct_at(transmute(out),
                    transmute(self)->get()->GetLocalClipCoverage());
}

bool ipl_display_list_builder_quick_reject(
    const ipl_display_list_builder_t* self,
    const ipl_f32_rect_t* bounds) {
  return transmute(self)->get()->QuickReject(*transmute(bounds));
}

// flutter::DisplayListBuilder::DrawPaint
void ipl_display_list_builder_draw_paint(const ipl_display_list_builder_t* self,
                                         const ipl_paint_t* paint) {
  transmute(self)->get()->DrawPaint(*transmute(paint));
}

// flutter::DisplayListBuilder::DrawColor
void ipl_display_list_builder_draw_color(const ipl_display_list_builder_t* self,
                                         const ipl_color_t* color,
                                         ipl_blend_mode_t mode) {
  transmute(self)->get()->DrawColor(*transmute(color), transmute(mode));
}

// flutter::DisplayListBuilder::DrawLine
void ipl_display_list_builder_draw_line(const ipl_display_list_builder_t* self,
                                        const ipl_f32_point_t* p0,
                                        const ipl_f32_point_t* p1,
                                        const ipl_paint_t* paint) {
  transmute(self)->get()->DrawLine(*transmute(p0), *transmute(p1),
                                   *transmute(paint));
}

// flutter::DisplayListBuilder::DrawDashedLine
void ipl_display_list_builder_draw_dashed_line(
    const ipl_display_list_builder_t* self,
    const ipl_f32_point_t* p0,
    const ipl_f32_point_t* p1,
    float on_length,
    float off_length,
    const ipl_paint_t* paint) {
  transmute(self)->get()->DrawDashedLine(
      *transmute(p0), *transmute(p1), on_length, off_length, *transmute(paint));
}

// flutter::DisplayListBuilder::DrawRect
void ipl_display_list_builder_draw_rect(const ipl_display_list_builder_t* self,
                                        const ipl_f32_rect_t* rect,
                                        const ipl_paint_t* paint) {
  transmute(self)->get()->DrawRect(*transmute(rect), *transmute(paint));
}

// flutter::DisplayListBuilder::DrawOval
void ipl_display_list_builder_draw_oval(const ipl_display_list_builder_t* self,
                                        const ipl_f32_rect_t* bounds,
                                        const ipl_paint_t* paint) {
  transmute(self)->get()->DrawOval(*transmute(bounds), *transmute(paint));
}

// flutter::DisplayListBuilder::DrawCircle
void ipl_display_list_builder_draw_circle(
    const ipl_display_list_builder_t* self,
    const ipl_f32_point_t* center,
    float radius,
    const ipl_paint_t* paint) {
  transmute(self)->get()->DrawCircle(*transmute(center), radius,
                                     *transmute(paint));
}

// flutter::DisplayListBuilder::DrawRoundRect
void ipl_display_list_builder_draw_round_rect(
    const ipl_display_list_builder_t* self,
    const ipl_round_rect_t* rrect,
    const ipl_paint_t* paint) {
  transmute(self)->get()->DrawRoundRect(*transmute(rrect), *transmute(paint));
}

// flutter::DisplayListBuilder::DrawDiffRoundRect
void ipl_display_list_builder_draw_diff_round_rect(
    const ipl_display_list_builder_t* self,
    const ipl_round_rect_t* outer,
    const ipl_round_rect_t* inner,
    const ipl_paint_t* paint) {
  transmute(self)->get()->DrawDiffRoundRect(
      *transmute(outer), *transmute(inner), *transmute(paint));
}

// flutter::DisplayListBuilder::DrawRoundSuperellipse

// flutter::DisplayListBuilder::DrawPath
void ipl_display_list_builder_draw_path(const ipl_display_list_builder_t* self,
                                        const ipl_path_t* path,
                                        const ipl_paint_t* paint) {
  transmute(self)->get()->DrawPath(*transmute(path), *transmute(paint));
}

// flutter::DisplayListBuilder::DrawArc
void ipl_display_list_builder_draw_arc(const ipl_display_list_builder_t* self,
                                       const ipl_f32_rect_t* bounds,
                                       float start,
                                       float sweep,
                                       bool use_center,
                                       const ipl_paint_t* paint) {
  transmute(self)->get()->DrawArc(*transmute(bounds), start, sweep, use_center,
                                  *transmute(paint));
}

// flutter::DisplayListBuilder::DrawPoints
void ipl_display_list_builder_draw_points(
    const ipl_display_list_builder_t* self,
    ipl_point_mode_t mode,
    uint32_t count,
    const ipl_f32_point_t pts[],
    const ipl_paint_t* paint) {
  transmute(self)->get()->DrawPoints(transmute(mode), count, transmute(pts),
                                     *transmute(paint));
}

// flutter::DisplayListBuilder::DrawVertices

// flutter::DisplayListBuilder::DrawImage
void ipl_display_list_builder_draw_image(const ipl_display_list_builder_t* self,
                                         const ipl_image_t* image,
                                         const ipl_f32_point_t* point,
                                         ipl_image_sampling_t sampling,
                                         const ipl_paint_t* paint) {
  transmute(self)->get()->DrawImage(*transmute(image), *transmute(point),
                                    transmute(sampling),
                                    transmute(paint, false));
}

// flutter::DisplayListBuilder::DrawImageRect
void ipl_display_list_builder_draw_image_rect(
    const ipl_display_list_builder_t* self,
    const ipl_image_t* image,
    const ipl_f32_rect_t* src,
    const ipl_f32_rect_t* dst,
    ipl_image_sampling_t sampling,
    const ipl_paint_t* paint,
    ipl_src_rect_constraint_t constraint) {
  transmute(self)->get()->DrawImageRect(
      *transmute(image), *transmute(src), *transmute(dst), transmute(sampling),
      transmute(paint, false), transmute(constraint));
}

// flutter::DisplayListBuilder::DrawImageNine
void ipl_display_list_builder_draw_image_nine(
    const ipl_display_list_builder_t* self,
    const ipl_image_t* image,
    const ipl_i32_rect_t* center,
    const ipl_f32_rect_t* dst,
    ipl_filter_mode_t filter,
    const ipl_paint_t* paint) {
  transmute(self)->get()->DrawImageNine(*transmute(image), *transmute(center),
                                        *transmute(dst), transmute(filter),
                                        transmute(paint, false));
}

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
                                         const ipl_paint_t* paint) {
  transmute(self)->get()->DrawAtlas(
      *transmute(atlas), transmute(xform), transmute(tex), transmute(colors),
      count, transmute(mode), transmute(sampling), transmute(cull_rect, false),
      transmute(paint, false));
}

// flutter::DisplayListBuilder::DrawDisplayList
void ipl_display_list_builder_draw_display_list(
    const ipl_display_list_builder_t* self,
    const ipl_display_list_t* display_list,
    float opacity) {
  transmute(self)->get()->DrawDisplayList(*transmute(display_list), opacity);
}

// flutter::DisplayListBuilder::DrawText
void ipl_display_list_builder_draw_text(const ipl_display_list_builder_t* self,
                                        const ipl_text_t* text,
                                        float x,
                                        float y,
                                        const ipl_paint_t* paint) {
  transmute(self)->get()->DrawText(*transmute(text), x, y, *transmute(paint));
}

// flutter::DisplayListBuilder::DrawShadow
void ipl_display_list_builder_draw_shadow(
    const ipl_display_list_builder_t* self,
    const ipl_path_t* path,
    const ipl_color_t* color,
    float elevation,
    bool transparent_occluder,
    float dpr) {
  transmute(self)->get()->DrawShadow(*transmute(path), *transmute(color),
                                     elevation, transparent_occluder, dpr);
}

// flutter::DisplayListBuilder::Flush
void ipl_display_list_builder_flush(const ipl_display_list_builder_t* self) {
  transmute(self)->get()->Flush();
}

// flutter::DisplayListBuilder::Build
void ipl_display_list_builder_build(const ipl_display_list_builder_t* self,
                                    ipl_display_list_t* out) {
  auto* display_list =
      std::construct_at(transmute(out), transmute(self)->get()->Build());
  assert(*display_list != nullptr);
}

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/display_list/dl_builder.h
// ----------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/txt/src/txt/paragraph_style.h
// ---------------------------------------------------------------------------

void ipl_paragraph_style_new(ipl_paragraph_style_t* out) {
  std::construct_at(transmute(out));
}

void ipl_paragraph_style_drop(ipl_paragraph_style_t* self) {
  std::destroy_at(transmute(self));
}

void ipl_paragraph_style_set(ipl_paragraph_style_t* self, int font_weight) {
  transmute(self)->font_weight = font_weight;
}

void ipl_paragraph_style_set_font_weight(ipl_paragraph_style_t* self,
                                         int font_weight) {
  transmute(self)->font_weight = font_weight;
}

int ipl_paragraph_style_get_font_weight(const ipl_paragraph_style_t* self) {
  return transmute(self)->font_weight;
}

void ipl_paragraph_style_set_font_style(ipl_paragraph_style_t* self,
                                        ipl_font_style_t font_style) {
  transmute(self)->font_style = transmute(font_style);
}

ipl_font_style_t ipl_paragraph_style_get_font_style(
    const ipl_paragraph_style_t* self) {
  return transmute(transmute(self)->font_style);
}

void ipl_paragraph_style_set_font_family(ipl_paragraph_style_t* self,
                                         const char* ptr,
                                         size_t len) {
  transmute(self)->font_family = std::string(ptr, len);
}

void ipl_paragraph_style_get_font_family(const ipl_paragraph_style_t* self,
                                         const char** ptr,
                                         size_t* len) {
  *ptr = transmute(self)->font_family.c_str();
  *len = transmute(self)->font_family.size();
}

void ipl_paragraph_style_set_font_size(ipl_paragraph_style_t* self,
                                       double font_size) {
  transmute(self)->font_size = font_size;
}

double ipl_paragraph_style_get_font_size(const ipl_paragraph_style_t* self) {
  return transmute(self)->font_size;
}

void ipl_paragraph_style_set_height(ipl_paragraph_style_t* self,
                                    double height) {
  transmute(self)->height = height;
}

double ipl_paragraph_style_get_height(const ipl_paragraph_style_t* self) {
  return transmute(self)->height;
}

void ipl_paragraph_style_set_has_height_override(ipl_paragraph_style_t* self,
                                                 bool has_height_override) {
  transmute(self)->has_height_override = has_height_override;
}

bool ipl_paragraph_style_get_has_height_override(
    const ipl_paragraph_style_t* self) {
  return transmute(self)->has_height_override;
}

void ipl_paragraph_style_set_text_height_behavior(
    ipl_paragraph_style_t* self,
    ipl_text_height_behavior_t text_height_behavior) {
  transmute(self)->text_height_behavior = transmute(text_height_behavior);
}

ipl_text_height_behavior_t ipl_paragraph_style_get_text_height_behavior(
    const ipl_paragraph_style_t* self) {
  return transmute(static_cast<txt::TextHeightBehavior>(
      transmute(self)->text_height_behavior));
}

void ipl_paragraph_style_set_strut_enabled(ipl_paragraph_style_t* self,
                                           bool strut_enabled) {
  transmute(self)->strut_enabled = strut_enabled;
}

bool ipl_paragraph_style_get_strut_enabled(const ipl_paragraph_style_t* self) {
  return transmute(self)->strut_enabled;
}

void ipl_paragraph_style_set_strut_font_weight(ipl_paragraph_style_t* self,
                                               int strut_font_weight) {
  transmute(self)->strut_font_weight = strut_font_weight;
}

int ipl_paragraph_style_get_strut_font_weight(
    const ipl_paragraph_style_t* self) {
  return transmute(self)->strut_font_weight;
}

void ipl_paragraph_style_set_strut_font_style(
    ipl_paragraph_style_t* self,
    ipl_font_style_t strut_font_style) {
  transmute(self)->strut_font_style = transmute(strut_font_style);
}

ipl_font_style_t ipl_paragraph_style_get_strut_font_style(
    const ipl_paragraph_style_t* self) {
  return transmute(transmute(self)->strut_font_style);
}

void ipl_paragraph_style_set_strut_font_size(ipl_paragraph_style_t* self,
                                             double strut_font_size) {
  transmute(self)->strut_font_size = strut_font_size;
}

double ipl_paragraph_style_get_strut_font_size(
    const ipl_paragraph_style_t* self) {
  return transmute(self)->strut_font_size;
}

void ipl_paragraph_style_set_strut_height(ipl_paragraph_style_t* self,
                                          double strut_height) {
  transmute(self)->strut_height = strut_height;
}

double ipl_paragraph_style_get_strut_height(const ipl_paragraph_style_t* self) {
  return transmute(self)->strut_height;
}

void ipl_paragraph_style_set_strut_has_height_override(
    ipl_paragraph_style_t* self,
    bool strut_has_height_override) {
  transmute(self)->strut_has_height_override = strut_has_height_override;
}

bool ipl_paragraph_style_get_strut_has_height_override(
    const ipl_paragraph_style_t* self) {
  return transmute(self)->strut_has_height_override;
}

void ipl_paragraph_style_set_strut_half_leading(ipl_paragraph_style_t* self,
                                                bool strut_half_leading) {
  transmute(self)->strut_half_leading = strut_half_leading;
}

bool ipl_paragraph_style_get_strut_half_leading(
    const ipl_paragraph_style_t* self) {
  return transmute(self)->strut_half_leading;
}

void ipl_paragraph_style_set_strut_leading(ipl_paragraph_style_t* self,
                                           double strut_leading) {
  transmute(self)->strut_leading = strut_leading;
}

double ipl_paragraph_style_get_strut_leading(
    const ipl_paragraph_style_t* self) {
  return transmute(self)->strut_leading;
}

void ipl_paragraph_style_set_force_strut_height(ipl_paragraph_style_t* self,
                                                bool force_strut_height) {
  transmute(self)->force_strut_height = force_strut_height;
}

bool ipl_paragraph_style_get_force_strut_height(
    const ipl_paragraph_style_t* self) {
  return transmute(self)->force_strut_height;
}

void ipl_paragraph_style_set_text_align(ipl_paragraph_style_t* self,
                                        ipl_text_align_t text_align) {
  transmute(self)->text_align = transmute(text_align);
}

ipl_text_align_t ipl_paragraph_style_get_text_align(
    const ipl_paragraph_style_t* self) {
  return transmute(transmute(self)->text_align);
}

void ipl_paragraph_style_set_text_direction(
    ipl_paragraph_style_t* self,
    ipl_text_direction_t text_direction) {
  transmute(self)->text_direction = transmute(text_direction);
}

ipl_text_direction_t ipl_paragraph_style_get_text_direction(
    const ipl_paragraph_style_t* self) {
  return transmute(transmute(self)->text_direction);
}

void ipl_paragraph_style_set_max_lines(ipl_paragraph_style_t* self,
                                       size_t max_lines) {
  transmute(self)->max_lines = max_lines;
}

size_t ipl_paragraph_style_get_max_lines(const ipl_paragraph_style_t* self) {
  return transmute(self)->max_lines;
}

void ipl_paragraph_style_set_ellipsis(ipl_paragraph_style_t* self,
                                      const char16_t* ptr,
                                      size_t len) {
  transmute(self)->ellipsis = std::u16string(ptr, len);
}

void ipl_paragraph_style_get_ellipsis(const ipl_paragraph_style_t* self,
                                      const char16_t** ptr,
                                      size_t* len) {
  *ptr = transmute(self)->ellipsis.c_str();
  *len = transmute(self)->ellipsis.size();
}

void ipl_paragraph_style_set_locale(ipl_paragraph_style_t* self,
                                    const char* ptr,
                                    size_t len) {
  transmute(self)->locale = std::string(ptr, len);
}

void ipl_paragraph_style_get_locale(const ipl_paragraph_style_t* self,
                                    const char** ptr,
                                    size_t* len) {
  *ptr = transmute(self)->locale.c_str();
  *len = transmute(self)->locale.size();
}

void ipl_paragraph_style_get_text_style(const ipl_paragraph_style_t* self,
                                        ipl_text_style_t* out) {
  std::construct_at(transmute(out), transmute(self)->GetTextStyle());
}

bool ipl_paragraph_style_unlimited_lines(const ipl_paragraph_style_t* self) {
  return transmute(self)->unlimited_lines();
}

bool ipl_paragraph_style_ellipsized(const ipl_paragraph_style_t* self) {
  return transmute(self)->ellipsized();
}

ipl_text_align_t ipl_paragraph_style_effective_align(
    const ipl_paragraph_style_t* self) {
  return transmute(transmute(self)->effective_align());
}

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/txt/src/txt/paragraph_style.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/txt/src/txt/font_features.h
// ---------------------------------------------------------------------------

void ipl_font_features_drop(ipl_font_features_t self) {
  std::destroy_at(transmute(self));
}

void ipl_font_features_set_feature(ipl_font_features_t self,
                                   const char* ptr,
                                   size_t len,
                                   int value) {
  transmute(self)->SetFeature(std::string(ptr, len), value);
}

void ipl_font_variations_drop(ipl_font_variations_t self) {
  std::destroy_at(transmute(self));
}

void ipl_font_variations_set_axis_value(ipl_font_variations_t self,
                                        const char* ptr,
                                        size_t len,
                                        float value) {
  transmute(self)->SetAxisValue(std::string(ptr, len), value);
}

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/txt/src/txt/font_features.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/txt/src/txt/text_style.h
// ---------------------------------------------------------------------------

void ipl_text_style_new(ipl_text_style_t* out) {
  std::construct_at(transmute(out));
}

void ipl_text_style_drop(ipl_text_style_t* self) {
  std::destroy_at(transmute(self));
}

// void ipl_text_style_set_color(ipl_text_style_t* self, const ipl_color_t*
// color) {
//     transmute(self)->color = *transmute(color);
// }

// void ipl_text_style_get_color(const ipl_text_style_t* self, ipl_color_t* out)
// {
//     std::construct_at(transmute(out), transmute(self)->color);
// }

int ipl_text_style_get_decoration(const ipl_text_style_t* self) {
  return static_cast<int>(transmute(self)->decoration);
}

void ipl_text_style_set_decoration(ipl_text_style_t* self, int decoration) {
  transmute(self)->decoration = txt::TextDecoration(decoration);
}

// void ipl_text_style_get_decoration_color(const ipl_text_style_t* self,
//                                          ipl_color_t* out) {
//     std::construct_at(transmute(out), transmute(self)->decoration_color);
// }

// void ipl_text_style_set_decoration_color(ipl_text_style_t* self,
//                                          const ipl_color_t* color) {
//     transmute(self)->decoration_color = *transmute(color);
// }

ipl_text_decoration_style_t ipl_text_style_get_decoration_style(
    const ipl_text_style_t* self) {
  return transmute(transmute(self)->decoration_style);
}

void ipl_text_style_set_decoration_style(ipl_text_style_t* self,
                                         ipl_text_decoration_style_t style) {
  transmute(self)->decoration_style = transmute(style);
}

double ipl_text_style_get_decoration_thickness_multiplier(
    const ipl_text_style_t* self) {
  return transmute(self)->decoration_thickness_multiplier;
}

void ipl_text_style_set_decoration_thickness_multiplier(ipl_text_style_t* self,
                                                        double multiplier) {
  transmute(self)->decoration_thickness_multiplier = multiplier;
}

int ipl_text_style_get_font_weight(const ipl_text_style_t* self) {
  return transmute(self)->font_weight;
}

void ipl_text_style_set_font_weight(ipl_text_style_t* self, int font_weight) {
  transmute(self)->font_weight = font_weight;
}

ipl_font_style_t ipl_text_style_get_font_style(const ipl_text_style_t* self) {
  return transmute(transmute(self)->font_style);
}

void ipl_text_style_set_font_style(ipl_text_style_t* self,
                                   ipl_font_style_t font_style) {
  transmute(self)->font_style = transmute(font_style);
}

ipl_text_baseline_t ipl_text_style_get_text_baseline(
    const ipl_text_style_t* self) {
  return transmute(
      static_cast<txt::TextBaseline>(transmute(self)->text_baseline));
}

void ipl_text_style_set_text_baseline(ipl_text_style_t* self,
                                      ipl_text_baseline_t text_baseline) {
  transmute(self)->text_baseline =
      static_cast<txt::TextBaseline>(transmute(text_baseline));
}

bool ipl_text_style_get_half_leading(const ipl_text_style_t* self) {
  return transmute(self)->half_leading;
}

void ipl_text_style_set_half_leading(ipl_text_style_t* self,
                                     bool half_leading) {
  transmute(self)->half_leading = half_leading;
}

void ipl_text_style_set_font_families(ipl_text_style_t* self,
                                      const char* const* ptrs,
                                      const size_t* lens,
                                      size_t count) {
  std::vector<std::string> families;
  families.reserve(count);
  for (size_t i = 0; i < count; ++i) {
    families.emplace_back(ptrs[i], lens[i]);
  }
  transmute(self)->font_families = std::move(families);
}

void ipl_text_style_get_font_families(const ipl_text_style_t* self,
                                      const char*** ptrs,
                                      size_t** lens,
                                      size_t* count) {
  static std::vector<const char*> ptrs_vec;
  static std::vector<size_t> lens_vec;
  ptrs_vec.clear();
  lens_vec.clear();
  for (const auto& family : transmute(self)->font_families) {
    ptrs_vec.push_back(family.c_str());
    lens_vec.push_back(family.size());
  }
  *ptrs = ptrs_vec.data();
  *lens = lens_vec.data();
  *count = ptrs_vec.size();
}

void ipl_text_style_set_font_size(ipl_text_style_t* self, double font_size) {
  transmute(self)->font_size = font_size;
}

double ipl_text_style_get_font_size(const ipl_text_style_t* self) {
  return transmute(self)->font_size;
}

void ipl_text_style_set_letter_spacing(ipl_text_style_t* self,
                                       double letter_spacing) {
  transmute(self)->letter_spacing = letter_spacing;
}

double ipl_text_style_get_letter_spacing(const ipl_text_style_t* self) {
  return transmute(self)->letter_spacing;
}

void ipl_text_style_set_word_spacing(ipl_text_style_t* self,
                                     double word_spacing) {
  transmute(self)->word_spacing = word_spacing;
}

double ipl_text_style_get_word_spacing(const ipl_text_style_t* self) {
  return transmute(self)->word_spacing;
}

void ipl_text_style_set_height(ipl_text_style_t* self, double height) {
  transmute(self)->height = height;
}

double ipl_text_style_get_height(const ipl_text_style_t* self) {
  return transmute(self)->height;
}

void ipl_text_style_set_has_height_override(ipl_text_style_t* self,
                                            bool has_height_override) {
  transmute(self)->has_height_override = has_height_override;
}

bool ipl_text_style_get_has_height_override(const ipl_text_style_t* self) {
  return transmute(self)->has_height_override;
}

void ipl_text_style_set_locale(ipl_text_style_t* self,
                               const char* ptr,
                               size_t len) {
  transmute(self)->locale = std::string(ptr, len);
}

void ipl_text_style_get_locale(const ipl_text_style_t* self,
                               const char** ptr,
                               size_t* len) {
  *ptr = transmute(self)->locale.c_str();
  *len = transmute(self)->locale.size();
}

bool ipl_text_style_has_background(const ipl_text_style_t* self) {
  return transmute(self)->background.has_value();
}

void ipl_text_style_get_background(const ipl_text_style_t* self,
                                   ipl_paint_t* out) {
  std::construct_at(transmute(out), transmute(self)->background.value());
}

void ipl_text_style_set_background(ipl_text_style_t* self,
                                   const ipl_paint_t* paint) {
  transmute(self)->background = *transmute(paint);
}

void ipl_text_style_clear_background(ipl_text_style_t* self) {
  transmute(self)->background = std::nullopt;
}

bool ipl_text_style_has_foreground(const ipl_text_style_t* self) {
  return transmute(self)->foreground.has_value();
}

void ipl_text_style_get_foreground(const ipl_text_style_t* self,
                                   ipl_paint_t* out) {
  std::construct_at(transmute(out), transmute(self)->foreground.value());
}

void ipl_text_style_set_foreground(ipl_text_style_t* self,
                                   const ipl_paint_t* paint) {
  transmute(self)->foreground = *transmute(paint);
}

void ipl_text_style_clear_foreground(ipl_text_style_t* self) {
  transmute(self)->foreground = std::nullopt;
}

void ipl_text_style_set_text_shadows(ipl_text_style_t* self,
                                     const ipl_text_shadow_t* shadows,
                                     size_t count) {
  std::vector<txt::TextShadow> text_shadows;
  text_shadows.reserve(count);
  for (size_t i = 0; i < count; ++i) {
    text_shadows.push_back(*transmute(&shadows[i]));
  }
  transmute(self)->text_shadows = std::move(text_shadows);
}

void ipl_text_style_get_text_shadows(const ipl_text_style_t* self,
                                     ipl_text_shadow_t* out,
                                     size_t* count) {
  const auto& text_shadows = transmute(self)->text_shadows;
  for (size_t i = 0; i < text_shadows.size(); ++i) {
    std::construct_at(transmute(&out[i]), text_shadows[i]);
  }
  *count = text_shadows.size();
}

// ipl_font_features_t ipl_text_style_get_font_features(
//     const ipl_text_style_t* self) {
//     return transmute(&transmute(self)->font_features);
// }

// void ipl_text_style_set_font_features(ipl_text_style_t* self,
//                                       const ipl_font_features_t*
//                                       font_features) {
//     transmute(self)->font_features = *transmute(font_features);
// }

// const ipl_font_variations_t* ipl_text_style_get_font_variations(
//     const ipl_text_style_t* self) {
//     return transmute(&transmute(self)->font_variations);
// }

// void ipl_text_style_set_font_variations(
//     ipl_text_style_t* self,
//     const ipl_font_variations_t* font_variations) {
//     transmute(self)->font_variations = *transmute(font_variations);
// }

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/txt/src/txt/text_style.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/txt/src/txt/font_collection.h
// ---------------------------------------------------------------------------

void ipl_font_collection_new(ipl_font_collection_t* out) {
  std::construct_at(transmute(out), std::make_shared<txt::FontCollection>());
}

void ipl_font_collection_drop(ipl_font_collection_t* self) {
  std::destroy_at(transmute(self));
}

void ipl_font_collection_setup_default_font_manager(
    const ipl_font_collection_t* self,
    uint32_t font_initialization_data) {
  transmute(self)->get()->SetupDefaultFontManager(font_initialization_data);
}

void ipl_font_collection_disable_font_fallback(
    const ipl_font_collection_t* self) {
  transmute(self)->get()->DisableFontFallback();
}

void ipl_font_collection_clear_font_family_cache(
    const ipl_font_collection_t* self) {
  transmute(self)->get()->ClearFontFamilyCache();
}

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/txt/src/txt/font_collection.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/txt/src/txt/paragraph.h
// ---------------------------------------------------------------------------

void ipl_paragraph_drop(ipl_paragraph_t* self) {
  std::destroy_at(transmute(self));
}

// flutter::Paragraph::GetMaxWidth
double ipl_paragraph_get_max_width(const ipl_paragraph_t* self) {
  return transmute(self)->get()->GetMaxWidth();
}

// flutter::Paragraph::GetHeight
double ipl_paragraph_get_height(const ipl_paragraph_t* self) {
  return transmute(self)->get()->GetHeight();
}

// flutter::Paragraph::GetLongestLine
double ipl_paragraph_get_longest_line(const ipl_paragraph_t* self) {
  return transmute(self)->get()->GetLongestLine();
}

// flutter::Paragraph::GetMinIntrinsicWidth
double ipl_paragraph_get_min_intrinsic_width(const ipl_paragraph_t* self) {
  return transmute(self)->get()->GetMinIntrinsicWidth();
}

// flutter::Paragraph::GetMaxIntrinsicWidth
double ipl_paragraph_get_max_intrinsic_width(const ipl_paragraph_t* self) {
  return transmute(self)->get()->GetMaxIntrinsicWidth();
}

// flutter::Paragraph::GetAlphabeticBaseline
double ipl_paragraph_get_alphabetic_baseline(const ipl_paragraph_t* self) {
  return transmute(self)->get()->GetAlphabeticBaseline();
}

// flutter::Paragraph::GetIdeographicBaseline
double ipl_paragraph_get_ideographic_baseline(const ipl_paragraph_t* self) {
  return transmute(self)->get()->GetIdeographicBaseline();
}

// flutter::Paragraph::DidExceedMaxLines
bool ipl_paragraph_did_exceed_max_lines(const ipl_paragraph_t* self) {
  return transmute(self)->get()->DidExceedMaxLines();
}

// flutter::Paragraph::Layout
void ipl_paragraph_layout(const ipl_paragraph_t* self, double width) {
  transmute(self)->get()->Layout(width);
}

// flutter::Paragraph::Paint
bool ipl_paragraph_paint(const ipl_paragraph_t* self,
                         const ipl_display_list_builder_t* builder,
                         double x,
                         double y) {
  return transmute(self)->get()->Paint(transmute(builder)->get(), x, y);
}

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/txt/src/txt/paragraph.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/txt/src/skia/paragraph_builder_skia.h
// ---------------------------------------------------------------------------

void ipl_paragraph_builder_new(const ipl_paragraph_style_t* style,
                               const ipl_font_collection_t* font_collection,
                               ipl_paragraph_builder_t* out) {
  std::construct_at(transmute(out),
                    txt::ParagraphBuilder::CreateSkiaBuilder(
                        *transmute(style), *transmute(font_collection), true));
}

void ipl_paragraph_builder_drop(ipl_paragraph_builder_t* self) {
  std::destroy_at(transmute(self));
}

void ipl_paragraph_builder_push_style(const ipl_paragraph_builder_t* self,
                                      const ipl_text_style_t* style) {
  transmute(self)->get()->PushStyle(*transmute(style));
}

void ipl_paragraph_builder_pop(const ipl_paragraph_builder_t* self) {
  transmute(self)->get()->Pop();
}

const ipl_text_style_t* ipl_paragraph_builder_peek_style(
    const ipl_paragraph_builder_t* self) {
  return transmute(&transmute(self)->get()->PeekStyle());
}

void ipl_paragraph_builder_add_text(const ipl_paragraph_builder_t* self,
                                    const uint8_t* utf8_data,
                                    size_t byte_length) {
  transmute(self)->get()->AddText(utf8_data, byte_length);
}

void ipl_paragraph_builder_add_placeholder(const ipl_paragraph_builder_t* self,
                                           ipl_placehoder_run_t* span) {
  transmute(self)->get()->AddPlaceholder(*transmute(span));
}

void ipl_paragraph_builder_build(const ipl_paragraph_builder_t* self,
                                 ipl_paragraph_t* out) {
  std::construct_at(transmute(out), transmute(self)->get()->Build());
}

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/txt/src/skia/paragraph_builder_skia.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/impeller/typographer/typographer_context.h
// ---------------------------------------------------------------------------

void ipl_typographer_context_drop(ipl_typographer_context_t* self) {
  std::destroy_at(transmute(self));
}

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/impeller/typographer/typographer_context.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/impeller/renderer/context.h
// ---------------------------------------------------------------------------

void ipl_context_drop(ipl_context_t* self) {
  std::destroy_at(transmute(self));
}

void ipl_context_clone(const ipl_context_t* self, ipl_context_t* out) {
  std::construct_at(transmute(out), *transmute(self));
}

void ipl_context_from_vk_context(const ipl_vk_context_t* vk_context,
                                 ipl_context_t* out) {
  std::construct_at(transmute(out), *transmute(vk_context));
}

void ipl_context_reset_thread_local_state(const ipl_context_t* self) {
  transmute(self)->get()->ResetThreadLocalState();
}

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/impeller/renderer/context.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/impeller/renderer/surface.h
// ---------------------------------------------------------------------------

void ipl_surface_drop(ipl_surface_t* self) {
  std::destroy_at(transmute(self));
}

void ipl_surface_get_size(const ipl_surface_t* self, ipl_i64_size_t* out) {
  std::construct_at(transmute(out), transmute(self)->get()->GetSize());
}

ipl_const_render_target_t ipl_surface_get_render_target(
    const ipl_surface_t* self) {
  return transmute(&transmute(self)->get()->GetRenderTarget());
}

bool ipl_surface_present(const ipl_surface_t* self) {
  return transmute(self)->get()->Present();
}

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/impeller/renderer/surface.h
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// [BEGIN] engine/src/flutter/impeller/renderer/backend/vulkan/context_vk.h
// ---------------------------------------------------------------------------

void ipl_vk_context_settings_new(ipl_vk_context_settings_t* out) {
  std::construct_at(transmute(out));
}

void ipl_vk_context_settings_drop(ipl_vk_context_settings_t* self) {
  std::destroy_at(transmute(self));
}

void ipl_vk_context_settings_set_proc_address_callback(
    ipl_vk_context_settings_t* self,
    void* (*proc_address_callback)(VkInstance, const char*)) {
  transmute(self)->proc_address_callback =
      reinterpret_cast<PFN_vkGetInstanceProcAddr>(proc_address_callback);
}

void ipl_vk_context_settings_set_enable_validation(
    ipl_vk_context_settings_t* self,
    bool enable_validation) {
  transmute(self)->enable_validation = enable_validation;
}

void ipl_vk_context_settings_set_flags(ipl_vk_context_settings_t* self,
                                       const ipl_flags_t* flags) {
  transmute(self)->flags = *transmute(flags);
}

bool ipl_vk_context_new(ipl_vk_context_settings_t* settings,
                        ipl_vk_context_t* out) {
  std::construct_at(transmute(out), impeller::ContextVK::Create(
                                        std::move(*transmute(settings))));
  return true;
}

void ipl_vk_context_drop(ipl_vk_context_t* self) {
  std::destroy_at(transmute(self));
}

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
                          ipl_vk_swapchain_t* out) {
  auto* context_sp = transmute(context);
  auto surface_khr = impeller::vk::UniqueSurfaceKHR(
      impeller::vk::SurfaceKHR(surface),
      impeller::ContextVK::Cast(*context_sp->get()).GetInstance());
  auto* swapchin = std::construct_at(
      transmute(out),
      impeller::SwapchainVK::Create(*context_sp, std::move(surface_khr),
                                    *transmute(size)));
  return *swapchin != nullptr;
}

void ipl_vk_swapchain_drop(ipl_vk_swapchain_t* self) {
  std::destroy_at(transmute(self));
}

bool ipl_vk_swapchain_acquire_next_drawable(const ipl_vk_swapchain_t* self,
                                            ipl_surface_t* out) {
  auto* surface = std::construct_at(
      transmute(out), transmute(self)->get()->AcquireNextDrawable());
  return *surface == nullptr;
}

void ipl_vk_swapchain_update_surface_size(const ipl_vk_swapchain_t* self,
                                          const ipl_i64_size_t* size) {
  transmute(self)->get()->UpdateSurfaceSize(*transmute(size));
}

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
    ipl_content_context_t* out) {
  auto* content_context = std::construct_at(
      transmute(out),
      std::make_unique<impeller::ContentContext>(
          *transmute(context), *transmute(typographer_context)));
  return *content_context != nullptr;
}

void ipl_content_context_drop(ipl_content_context_t* self) {
  std::destroy_at(transmute(self));
}

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
                                       bool is_onscreen) {
  return impeller::RenderToTarget(
      *transmute(context)->get(), *transmute(render_target), *transmute(self),
      *transmute(cull_rect), reset_host_buffer, is_onscreen);
}

// ---------------------------------------------------------------------------
// [END] engine/src/flutter/impeller/display_list/dl_dispatcher.h
// ---------------------------------------------------------------------------

// ===========================================================================
// [END] Function Definition
// ===========================================================================
