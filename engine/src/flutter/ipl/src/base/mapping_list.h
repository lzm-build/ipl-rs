
#ifndef FLUTTER_IPL_SRC_BASE_MAPPING_LIST_H_
#define FLUTTER_IPL_SRC_BASE_MAPPING_LIST_H_

#include <cassert>
#include <cstdint>
#include <memory>
#include <vector>

#include "base/mapping_list.h"
#include "fml/mapping.h"

namespace ipl {

static inline std::vector<std::shared_ptr<fml::Mapping>>* transmute(
    ipl_mapping_list_t* self) {
  assert(self != nullptr);
  assert(reinterpret_cast<intptr_t>(self) % alignof(ipl_mapping_list_t) == 0);
  return reinterpret_cast<std::vector<std::shared_ptr<fml::Mapping>>*>(self);
}

}  // namespace ipl

#endif  // FLUTTER_IPL_SRC_BASE_MAPPING_LIST_H_
