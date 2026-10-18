#ifndef FLUTTER_IPL_SRC_GLES_PROC_TABLE_H_
#define FLUTTER_IPL_SRC_GLES_PROC_TABLE_H_

#include "impeller/renderer/backend/gles/proc_table_gles.h"
#include "ipl/include/gles_proc_table.h"

impeller::ProcTableGLES* transmute(IplGlesProcTable* src) {
  return reinterpret_cast<impeller::ProcTableGLES*>(src);
}

const impeller::ProcTableGLES* transmute(const IplGlesProcTable* src) {
  return reinterpret_cast<const impeller::ProcTableGLES*>(src);
}

IplGlesProcTable* transmute(impeller::ProcTableGLES* src) {
  return reinterpret_cast<IplGlesProcTable*>(src);
}

const IplGlesProcTable* transmute(const impeller::ProcTableGLES* src) {
  return reinterpret_cast<const IplGlesProcTable*>(src);
}

#endif  // FLUTTER_IPL_SRC_GLES_PROC_TABLE_H_
