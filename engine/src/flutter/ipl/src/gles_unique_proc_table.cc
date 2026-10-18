#include <memory>
#include <type_traits>

#include "impeller/renderer/backend/gles/proc_table_gles.h"
#include "ipl/include/gles_unique_proc_table.h"
#include "ipl/src/gles_unique_proc_table.h"

static_assert(
    std::is_standard_layout_v<std::unique_ptr<impeller::ProcTableGLES>>);
static_assert(std::is_standard_layout_v<IplGlesUniqueProcTable>);
static_assert(sizeof(std::unique_ptr<impeller::ProcTableGLES>) ==
              sizeof(IplGlesUniqueProcTable));
static_assert(alignof(std::unique_ptr<impeller::ProcTableGLES>) ==
              alignof(IplGlesUniqueProcTable));

void ipl_gles_unique_proc_table_drop(IplGlesUniqueProcTable* self) {
  std::destroy_at(transmute(self));
}
