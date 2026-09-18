#ifndef FLUTTER_IPL_INCLUDE_RENDERER_SURFACE_H_
#define FLUTTER_IPL_INCLUDE_RENDERER_SURFACE_H_

#include <stdalign.h>
#include <stdbool.h>

#include "geometry/size.h"

#ifdef __cplusplus
extern "C" {
#endif

#if defined(__i386__) || defined(__arm__) || defined(_M_IX86)
#define IPL_SURFACE_SIZE 4
#define IPL_SURFACE_ALIGN 4
#else
#define IPL_SURFACE_SIZE 8
#define IPL_SURFACE_ALIGN 8
#endif

typedef struct {
  alignas(IPL_SURFACE_ALIGN) char data[IPL_SURFACE_SIZE];
} ipl_surface_t;

void ipl_surface_drop(ipl_surface_t* self);

void ipl_surface_get_size(const ipl_surface_t* self, ipl_isize_t* out);

bool ipl_surface_present(const ipl_surface_t* self);

#ifdef __cplusplus
}
#endif

#endif  // FLUTTER_IPL_INCLUDE_RENDERER_SURFACE_H_
