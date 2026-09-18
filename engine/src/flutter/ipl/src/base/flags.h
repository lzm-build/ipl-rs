#ifndef FLUTTER_IPL_SRC_BASE_FLAGS_H_
#define FLUTTER_IPL_SRC_BASE_FLAGS_H_

#include "base/flags.h"
#include "impeller/base/flags.h"

namespace ipl {

static inline impeller::Flags* transmute(ipl_flags_t* self) {
  return reinterpret_cast<impeller::Flags*>(self);
}

static inline const impeller::Flags* transmute(const ipl_flags_t* self) {
  return reinterpret_cast<const impeller::Flags*>(self);
}

static inline const ipl_flags_t* transmute(const impeller::Flags* self) {
  return reinterpret_cast<const ipl_flags_t*>(self);
}

}  // namespace ipl

#endif  // FLUTTER_IPL_SRC_BASE_FLAGS_H_
