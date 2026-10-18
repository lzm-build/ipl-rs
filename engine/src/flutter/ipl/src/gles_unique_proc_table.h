#ifndef FLUTTER_IPL_SRC_GLES_UNIQUE_PROC_TABLE_H_
#define FLUTTER_IPL_SRC_GLES_UNIQUE_PROC_TABLE_H_

#include <memory>

#include "impeller/renderer/backend/gles/proc_table_gles.h"
#include "ipl/include/gles_unique_proc_table.h"

std::unique_ptr<impeller::ProcTableGLES>* transmute(
    IplGlesUniqueProcTable* src) {
  return reinterpret_cast<std::unique_ptr<impeller::ProcTableGLES>*>(src);
}

const std::unique_ptr<impeller::ProcTableGLES>* transmute(
    const IplGlesUniqueProcTable* src) {
  return reinterpret_cast<const std::unique_ptr<impeller::ProcTableGLES>*>(src);
}

IplGlesUniqueProcTable* transmute(
    std::unique_ptr<impeller::ProcTableGLES>* src) {
  return reinterpret_cast<IplGlesUniqueProcTable*>(src);
}

const IplGlesUniqueProcTable* transmute(
    const std::unique_ptr<impeller::ProcTableGLES>* src) {
  return reinterpret_cast<const IplGlesUniqueProcTable*>(src);
}

#endif  // FLUTTER_IPL_SRC_GLES_UNIQUE_PROC_TABLE_H_
