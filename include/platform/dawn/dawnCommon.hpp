#ifndef __DAWN_COMMON_HPP__
#define __DAWN_COMMON_HPP__

#include <webgpu/webgpu_cpp.h>
#include <webgpu/webgpu_cpp_print.h>
#include <webgpu/webgpu_enum_class_bitmasks.h>
#include <webgpu/webgpu_cpp_chained_struct.h>

constexpr uint8_t kMaxTextureViews = 8u;
constexpr uint8_t kMaxColorAttachments = 8u;
constexpr uint8_t kMaxLayoutBindings = 30u;
constexpr uint8_t kMaxBindGroupLayouts = 8u;
constexpr uint8_t kMaxPushConstantByteRange = 128u;
constexpr uint16_t minUniformBufferOffsetAlignment = 256u;

#endif // !__DAWN_COMMON_HPP__
