#ifndef FLUTTER_IPL_INCLUDE_BASE_STRING_LIST_H_
#define FLUTTER_IPL_INCLUDE_BASE_STRING_LIST_H_

#include <stdalign.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#if defined(__i386__) || defined(__arm__) || defined(_M_IX86)
#define IPL_STRING_LIST_SIZE 12
#define IPL_STRING_LIST_ALIGN 4
#else
#define IPL_STRING_LIST_SIZE 24
#define IPL_STRING_LIST_ALIGN 8
#endif

typedef struct {
  alignas(IPL_STRING_LIST_ALIGN) char data[IPL_STRING_LIST_SIZE];
} ipl_string_list_t;

void ipl_string_list_new(ipl_string_list_t* out);

void ipl_string_list_drop(ipl_string_list_t* self);

void ipl_string_list_reserve(ipl_string_list_t* self, size_t n);

void ipl_string_list_push(ipl_string_list_t* self, const char* ptr, size_t len);

#ifdef __cplusplus
}
#endif

#endif  // FLUTTER_IPL_INCLUDE_BASE_STRING_LIST_H_
