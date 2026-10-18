#ifndef FLUTTER_IPL_INCLUDE_GLES_PROC_TABLE_H_
#define FLUTTER_IPL_INCLUDE_GLES_PROC_TABLE_H_

#include "ipl/include/gles_unique_proc_table.h"

typedef struct IplGlesProcTable IplGlesProcTable;

typedef void* (*IplGlesProcTableResolver)(void* user_data,
                                          const char* function_name);

#ifdef __cplusplus
extern "C" {
#endif

bool ipl_gles_proc_table_create(void* user_data,
                                IplGlesProcTableResolver resolver,
                                IplGlesUniqueProcTable* out);

#ifdef __cplusplus
}
#endif

#endif  // FLUTTER_IPL_INCLUDE_GLES_PROC_TABLE_H_
