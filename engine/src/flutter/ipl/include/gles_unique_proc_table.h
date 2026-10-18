#ifndef FLUTTER_IPL_INCLUDE_GLES_UNIQUE_PROC_TABLE_H_
#define FLUTTER_IPL_INCLUDE_GLES_UNIQUE_PROC_TABLE_H_

typedef struct IplGlesProcTable IplGlesProcTable;

typedef struct IplGlesUniqueProcTable {
  IplGlesProcTable* ptr;
} IplGlesUniqueProcTable;

#ifdef __cplusplus
extern "C" {
#endif

void ipl_gles_unique_proc_table_drop(IplGlesUniqueProcTable* self);

#ifdef __cplusplus
}
#endif

#endif  // FLUTTER_IPL_INCLUDE_GLES_UNIQUE_PROC_TABLE_H_
