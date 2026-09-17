#ifndef FLUTTER_IPL_INCLUDE_CORE_BUFFER_VIEW_H_
#define FLUTTER_IPL_INCLUDE_CORE_BUFFER_VIEW_H_

#include <stdalign.h>
#include <stdbool.h>

#include "core/device_buffer.h"

#ifdef __cplusplus
extern "C" {
#endif

#if defined(__i386__) || defined(__arm__) || defined(_M_IX86)
#define IPL_BUFFER_VIEW_SIZE 20
#define IPL_BUFFER_VIEW_ALIGN 4
#else
#define IPL_BUFFER_VIEW_SIZE 40
#define IPL_BUFFER_VIEW_ALIGN 8
#endif

typedef struct {
  alignas(IPL_BUFFER_VIEW_ALIGN) char data[IPL_BUFFER_VIEW_SIZE];
} ipl_buffer_view_t;

void ipl_buffer_view_drop(ipl_buffer_view_t* self);

bool ipl_buffer_view_take_buffer(ipl_buffer_view_t* self,
                                 ipl_const_device_buffer_t* out);

#ifdef __cplusplus
}
#endif

#endif  // FLUTTER_IPL_INCLUDE_CORE_BUFFER_VIEW_H_
