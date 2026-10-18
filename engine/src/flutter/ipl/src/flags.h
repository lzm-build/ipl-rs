#ifndef FLUTTER_IPL_SRC_FLAGS_H_
#define FLUTTER_IPL_SRC_FLAGS_H_

#include "impeller/base/flags.h"
#include "ipl/include/flags.h"

const impeller::Flags* transmute(const IplFlags* src) {
  return reinterpret_cast<const impeller::Flags*>(src);
}

const IplFlags* transmute(const impeller::Flags* src) {
  return reinterpret_cast<const IplFlags*>(src);
}

#endif  // FLUTTER_IPL_SRC_FLAGS_H_
