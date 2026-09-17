#ifndef FLUTTER_IPL_SRC_BASE_STRING_LIST_H_
#define FLUTTER_IPL_SRC_BASE_STRING_LIST_H_

#include <cassert>
#include <cstdint>
#include <string>
#include <vector>
#include "base/string_list.h"
namespace ipl {

static inline std::vector<std::string>* transmute(ipl_string_list_t* self) {
  assert(self != nullptr);
  assert(reinterpret_cast<intptr_t>(self) % alignof(ipl_string_list_t) == 0);
  return reinterpret_cast<std::vector<std::string>*>(self);
}

}  // namespace ipl

#endif  // FLUTTER_IPL_SRC_BASE_STRING_LIST_H_
