#include "ipl/src/base/string_list.h"
#include <cassert>
#include <memory>
#include <string>
#include <vector>

#include "base/string_list.h"

static_assert(sizeof(std::vector<std::string>) == sizeof(ipl_string_list_t));
static_assert(alignof(std::vector<std::string>) == alignof(ipl_string_list_t));

void ipl_string_list_new(ipl_string_list_t* out) {
  std::construct_at(ipl::transmute(out));
}

void ipl_string_list_drop(ipl_string_list_t* self) {
  std::destroy_at(ipl::transmute(self));
}

void ipl_string_list_reserve(ipl_string_list_t* self, size_t n) {
  ipl::transmute(self)->reserve(n);
}

void ipl_string_list_push(ipl_string_list_t* self,
                          const char* ptr,
                          size_t len) {
  assert(ptr != nullptr || len == 0);
  ipl::transmute(self)->emplace_back(ptr, len);
}
