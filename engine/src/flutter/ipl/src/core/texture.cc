#include <cassert>
#include <memory>
#include <string_view>

#include "core/texture.h"
#include "impeller/core/texture.h"
#include "ipl/src/core/texture.h"
#include "ipl/src/core/texture_descriptor.h"
#include "ipl/src/geometry/size.h"

static_assert(sizeof(std::shared_ptr<impeller::Texture>) == IPL_TEXTURE_SIZE);
static_assert(alignof(std::shared_ptr<impeller::Texture>) == IPL_TEXTURE_ALIGN);

void ipl_texture_drop(ipl_texture_t* self) {
  std::destroy_at(ipl::transmute(self));
}

void ipl_texture_clone(const ipl_texture_t* self, ipl_texture_t* out) {
  auto* texture = ipl::transmute(self);
  assert(*texture != nullptr);
  std::construct_at(ipl::transmute(out), *texture);
}

void ipl_texture_set_label(const ipl_texture_t* self,
                           const char* ptr,
                           size_t len) {
  auto* texture = ipl::transmute(self);
  assert(*texture != nullptr);
  texture->get()->SetLabel(std::string_view{ptr, len});
}

void ipl_texture_get_size(const ipl_texture_t* self, ipl_isize_t* out) {
  auto* texture = ipl::transmute(self);
  assert(*texture != nullptr);
  std::construct_at(ipl::transmute(out),
                    ipl::transmute(self)->get()->GetSize());
}

bool ipl_texture_is_opaque(const ipl_texture_t* self) {
  auto* texture = ipl::transmute(self);
  assert(*texture != nullptr);
  return texture->get()->IsOpaque();
}

size_t ipl_texture_get_mip_count(const ipl_texture_t* self) {
  auto* texture = ipl::transmute(self);
  assert(*texture != nullptr);
  return texture->get()->GetMipCount();
}

const ipl_texture_descriptor_t* ipl_texture_get_texture_descriptor(
    const ipl_texture_t* self) {
  return ipl::transmute(&ipl::transmute(self)->get()->GetTextureDescriptor());
}

bool ipl_texture_needs_mipmap_generation(const ipl_texture_t* self) {
  auto* texture = ipl::transmute(self);
  assert(*texture != nullptr);
  return texture->get()->NeedsMipmapGeneration();
}
