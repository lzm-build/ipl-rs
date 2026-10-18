#include <cstddef>
#include <type_traits>

#include "impeller/base/flags.h"
#include "ipl/include/flags.h"

static_assert(std::is_standard_layout_v<impeller::Flags>);
static_assert(std::is_standard_layout_v<IplFlags>);
static_assert(sizeof(impeller::Flags) == sizeof(IplFlags));
static_assert(alignof(impeller::Flags) == alignof(IplFlags));
static_assert(offsetof(impeller::Flags, use_sdfs) ==
              offsetof(IplFlags, use_sdfs));
static_assert(offsetof(impeller::Flags, top_left_default_framebuffer_origin) ==
              offsetof(IplFlags, top_left_default_framebuffer_origin));
static_assert(__is_layout_compatible(impeller::Flags, IplFlags));
static_assert(__builtin_is_cpp_trivially_relocatable(impeller::Flags));
static_assert(__builtin_is_cpp_trivially_relocatable(IplFlags));
