#ifndef FLUTTER_IPL_INCLUDE_CORE_DEVICE_BUFFER_H_
#define FLUTTER_IPL_INCLUDE_CORE_DEVICE_BUFFER_H_

#include <stdalign.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "core/device_buffer_descriptor.h"

#ifdef __cplusplus
extern "C" {
#endif

#if defined(__i386__) || defined(_M_IX86) || defined(__arm__)
#define IPL_DEVICE_BUFFER_SIZE 8
#define IPL_DEVICE_BUFFER_ALGIN 4
#else
#define IPL_DEVICE_BUFFER_SIZE 16
#define IPL_DEVICE_BUFFER_ALGIN 8
#endif

typedef struct {
  alignas(IPL_DEVICE_BUFFER_ALGIN) char data[IPL_DEVICE_BUFFER_SIZE];
} ipl_device_buffer_t;

void ipl_device_buffer_drop(ipl_device_buffer_t* self);

void ipl_device_buffer_clone(const ipl_device_buffer_t* self,
                             ipl_device_buffer_t* out);

bool ipl_device_buffer_copy_host_buffer(const ipl_device_buffer_t* self,
                                        const uint8_t* source,
                                        size_t source_offset,
                                        size_t source_length,
                                        size_t offset);

bool ipl_device_buffer_set_label(const ipl_device_buffer_t* self,
                                 const char* ptr,
                                 size_t len);

const ipl_device_buffer_descriptor_t*
ipl_device_buffer_get_device_buffer_descriptor(const ipl_device_buffer_t* self);

uint8_t* ipl_device_buffer_on_get_contents(const ipl_device_buffer_t* self);

void ipl_device_buffer_flush(const ipl_device_buffer_t* self,
                             size_t offset,
                             size_t length);

void ipl_device_buffer_invalidate(const ipl_device_buffer_t* self,
                                  size_t offset,
                                  size_t length);

#if defined(__i386__) || defined(_M_IX86) || defined(__arm__)
#define IPL_CONST_DEVICE_BUFFER_SIZE 8
#define IPL_CONST_DEVICE_BUFFER_ALGIN 4
#else
#define IPL_CONST_DEVICE_BUFFER_SIZE 16
#define IPL_CONST_DEVICE_BUFFER_ALGIN 8
#endif

typedef struct {
  alignas(
      IPL_CONST_DEVICE_BUFFER_ALGIN) char data[IPL_CONST_DEVICE_BUFFER_SIZE];
} ipl_const_device_buffer_t;

void ipl_const_device_buffer_drop(ipl_const_device_buffer_t* self);

void ipl_const_device_buffer_clone(const ipl_const_device_buffer_t* self,
                                   ipl_const_device_buffer_t* out);

const ipl_device_buffer_descriptor_t*
ipl_const_device_buffer_get_device_buffer_descriptor(
    const ipl_const_device_buffer_t* self);

uint8_t* ipl_const_device_buffer_on_get_contents(
    const ipl_const_device_buffer_t* self);

void ipl_const_device_buffer_flush(const ipl_const_device_buffer_t* self,
                                   size_t offset,
                                   size_t length);

void ipl_const_device_buffer_invalidate(const ipl_const_device_buffer_t* self,
                                        size_t offset,
                                        size_t length);

void ipl_device_buffer_into_const_device_buffer(ipl_device_buffer_t* self,
                                                ipl_const_device_buffer_t* out);

#ifdef __cplusplus
}
#endif

#endif  // FLUTTER_IPL_INCLUDE_CORE_DEVICE_BUFFER_H_
