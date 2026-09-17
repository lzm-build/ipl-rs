#include <cstddef>
#include <type_traits>

#include "geometry/size.h"
#include "impeller/geometry/size.h"

static_assert(std::is_standard_layout_v<impeller::ISize>);
static_assert(std::is_standard_layout_v<ipl_isize_t>);

static_assert(sizeof(impeller::ISize) == sizeof(ipl_isize_t));
static_assert(alignof(impeller::ISize) == alignof(ipl_isize_t));

static_assert(offsetof(impeller::ISize, width) == offsetof(ipl_isize_t, width));
static_assert(offsetof(impeller::ISize, height) ==
              offsetof(ipl_isize_t, height));
