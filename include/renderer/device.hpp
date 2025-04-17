#ifndef __DEVICE_HPP__
#define __DEVICE_HPP__

#include <string>
#include <cstdlib>
#include <cstddef>
#include <cstdint>

namespace gfx
{
    struct DeviceDescriptor
    {
        uint32_t vendorID;
        std::string vendor;
        std::string architecture;
        uint32_t deviceID;
        std::string name;
        std::string driver;
    };

    struct AdapterDescriptor
    {
        uint32_t maxTextureDimension1D = 0;
        uint32_t maxTextureDimension2D = 0;
        uint32_t maxTextureDimension3D = 0;
        uint32_t maxTextureArrayLayers = 0;
        uint32_t maxBindGroups = 0;
        uint32_t maxBindGroupsPlusVertexBuffers = 0;
        uint32_t maxBindingsPerBindGroup = 0;
        uint32_t maxDynamicUniformBuffersPerPipelineLayout = 0;
        uint32_t maxDynamicStorageBuffersPerPipelineLayout = 0;
        uint32_t maxSampledTexturesPerShaderStage = 0;
        uint32_t maxSamplersPerShaderStage = 0;
        uint32_t maxStorageBuffersPerShaderStage = 0;
        uint32_t maxStorageTexturesPerShaderStage = 0;
        uint32_t maxUniformBuffersPerShaderStage = 0;
        uint64_t maxUniformBufferBindingSize = 0;
        uint64_t maxStorageBufferBindingSize = 0;
        uint32_t minUniformBufferOffsetAlignment = 0;
        uint32_t minStorageBufferOffsetAlignment = 0;
        uint32_t maxVertexBuffers = 0;
        uint64_t maxBufferSize = 0;
        uint32_t maxVertexAttributes = 0;
        uint32_t maxVertexBufferArrayStride = 0;
        uint32_t maxInterStageShaderVariables = 0;
        uint32_t maxColorAttachments = 0;
        uint32_t maxColorAttachmentBytesPerSample = 0;
        uint32_t maxComputeWorkgroupStorageSize = 0;
        uint32_t maxComputeInvocationsPerWorkgroup = 0;
        uint32_t maxComputeWorkgroupSizeX = 0;
        uint32_t maxComputeWorkgroupSizeY = 0;
        uint32_t maxComputeWorkgroupSizeZ = 0;
        uint32_t maxComputeWorkgroupsPerDimension = 0;
    };
    
    class Device
    {
    public:
        static inline Device* instance = nullptr;
        
        virtual ~Device() = default;
        
        virtual void Init() = 0;
        virtual void ShutDown() = 0;

    public:
        DeviceDescriptor s_DeviceDesc;
        AdapterDescriptor s_AdapterDesc;
    };
}

#endif
