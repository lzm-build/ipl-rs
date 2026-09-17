#ifndef FLUTTER_IPL_INCLUDE_BASE_FLAGS_H_
#define FLUTTER_IPL_INCLUDE_BASE_FLAGS_H_

#include <stdalign.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
  bool antialiased_lines;
  bool use_sdfs;
} ipl_flags_t;

#ifdef __cplusplus
}
#endif

#endif  // FLUTTER_IPL_INCLUDE_BASE_FLAGS_H_
