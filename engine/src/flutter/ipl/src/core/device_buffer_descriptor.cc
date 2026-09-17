#include <cstddef>
#include <type_traits>

#include "core/device_buffer_descriptor.h"
#include "impeller/core/device_buffer_descriptor.h"

static_assert(sizeof(impeller::DeviceBufferDescriptor) ==
              sizeof(ipl_device_buffer_descriptor_t));
static_assert(alignof(impeller::DeviceBufferDescriptor) ==
              alignof(ipl_device_buffer_descriptor_t));

static_assert(std::is_standard_layout_v<impeller::DeviceBufferDescriptor>);
static_assert(std::is_standard_layout_v<ipl_device_buffer_descriptor_t>);

static_assert(offsetof(impeller::DeviceBufferDescriptor, storage_mode) ==
              offsetof(ipl_device_buffer_descriptor_t, storage_mode));
static_assert(offsetof(impeller::DeviceBufferDescriptor, size) ==
              offsetof(ipl_device_buffer_descriptor_t, size));
static_assert(offsetof(impeller::DeviceBufferDescriptor, readback) ==
              offsetof(ipl_device_buffer_descriptor_t, readback));
