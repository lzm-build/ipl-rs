#include <cassert>
#include <cstddef>
#include <type_traits>

#include "base/flags.h"
#include "impeller/base/flags.h"

static_assert(sizeof(impeller::Flags) == sizeof(ipl_flags_t));
static_assert(alignof(impeller::Flags) == alignof(ipl_flags_t));

static_assert(std::is_standard_layout_v<impeller::Flags>);
static_assert(std::is_standard_layout_v<ipl_flags_t>);

static_assert(offsetof(impeller::Flags, antialiased_lines) ==
              offsetof(ipl_flags_t, antialiased_lines));
static_assert(offsetof(impeller::Flags, use_sdfs) ==
              offsetof(ipl_flags_t, use_sdfs));
