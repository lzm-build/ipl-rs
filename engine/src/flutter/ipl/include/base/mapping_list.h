#ifndef FLUTTER_IPL_INCLUDE_BASE_MAPPING_LIST_H_
#define FLUTTER_IPL_INCLUDE_BASE_MAPPING_LIST_H_

#include <stdalign.h>
#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#if defined(__i386__) || defined(__arm__) || defined(_M_IX86)
#define IPL_MAPPING_LIST_SIZE 12
#define IPL_MAPPING_LIST_ALIGN 4
#else
#define IPL_MAPPING_LIST_SIZE 24
#define IPL_MAPPING_LIST_ALIGN 8
#endif

typedef struct {
  alignas(IPL_MAPPING_LIST_ALIGN) char data[IPL_MAPPING_LIST_SIZE];
} ipl_mapping_list_t;

void ipl_mapping_list_new(ipl_mapping_list_t* out);

void ipl_mapping_list_drop(ipl_mapping_list_t* self);

void ipl_mapping_list_reserve(ipl_mapping_list_t* self, size_t n);

void ipl_mapping_list_push(ipl_mapping_list_t* self,
                           const uint8_t* ptr,
                           size_t len);

#ifdef __cplusplus
}
#endif

#endif  // FLUTTER_IPL_INCLUDE_BASE_MAPPING_LIST_H_
