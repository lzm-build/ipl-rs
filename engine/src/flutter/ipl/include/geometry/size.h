#ifndef FLUTTER_IPL_INCLUDE_GEOMETRY_SIZE_H_
#define FLUTTER_IPL_INCLUDE_GEOMETRY_SIZE_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
  int64_t width;
  int64_t height;
} ipl_isize64_t;

typedef ipl_isize64_t ipl_isize_t;

#ifdef __cplusplus
}
#endif

#endif  // FLUTTER_IPL_INCLUDE_GEOMETRY_SIZE_H_
