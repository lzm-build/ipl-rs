#include <memory>

#include "impeller/renderer/surface.h"
#include "ipl/src/geometry/size.h"
#include "ipl/src/renderer/surface.h"
#include "renderer/surface.h"

static_assert(sizeof(std::unique_ptr<impeller::Surface>) ==
              sizeof(ipl_surface_t));
static_assert(alignof(std::unique_ptr<impeller::Surface>) ==
              alignof(ipl_surface_t));

void ipl_surface_drop(ipl_surface_t* self) {
  std::destroy_at(ipl::transmute(self));
}

void ipl_surface_get_size(const ipl_surface_t* self, ipl_isize_t* out) {
  std::construct_at(ipl::transmute(out),
                    ipl::transmute(self)->get()->GetSize());
}

bool ipl_surface_present(const ipl_surface_t* self) {
  return ipl::transmute(self)->get()->Present();
}
