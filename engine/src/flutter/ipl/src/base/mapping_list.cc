#include <memory>
#include <vector>

#include "base/mapping_list.h"
#include "fml/mapping.h"
#include "ipl/src/base/mapping_list.h"

static_assert(sizeof(std::vector<std::shared_ptr<fml::Mapping>>) ==
              sizeof(ipl_mapping_list_t));
static_assert(alignof(std::vector<std::shared_ptr<fml::Mapping>>) ==
              alignof(ipl_mapping_list_t));

void ipl_mapping_list_new(ipl_mapping_list_t* out) {
  std::construct_at(ipl::transmute(out));
}

void ipl_mapping_list_drop(ipl_mapping_list_t* self) {
  std::destroy_at(ipl::transmute(self));
}

void ipl_mapping_list_reserve(ipl_mapping_list_t* self, size_t n) {
  ipl::transmute(self)->reserve(n);
}

void ipl_mapping_list_push(ipl_mapping_list_t* self,
                           const uint8_t* ptr,
                           size_t len) {
  ipl::transmute(self)->emplace_back(
      std::make_shared<fml::NonOwnedMapping>(ptr, len));
}
