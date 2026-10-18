#include <memory>

#include "impeller/renderer/backend/gles/proc_table_gles.h"
#include "ipl/include/gles_proc_table.h"
#include "ipl/src/gles_unique_proc_table.h"

bool ipl_gles_proc_table_create(void* user_data,
                                IplGlesProcTableResolver resolver,
                                IplGlesUniqueProcTable* out) {
  auto proc_table = std::construct_at(
      transmute(out),
      std::make_unique<impeller::ProcTableGLES>(
          [user_data, resolver](const char* function_name) -> void* {
            return resolver(user_data, function_name);
          }));
  return *proc_table != nullptr;
}
