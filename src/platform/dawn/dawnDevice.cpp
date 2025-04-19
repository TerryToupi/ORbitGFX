#include <dawn/dawnDevice.hpp>

#include <log.hpp>

#include <sstream>
#include <string>

namespace gfx
{
    static std::string FormatNumber(uint64_t num) {
        auto s = std::to_string(num);
        std::stringstream ret;

        auto remainder = s.length() % 3;
        ret << s.substr(0, remainder);
        for (size_t i = remainder; i < s.length(); i += 3) {
            if (i > 0) {
                ret << ",";
            }
            ret << s.substr(i, 3);
        }
        return ret.str();
    }

    static std::string LimitsToString(const wgpu::Limits& limits, const std::string& indent) {
        std::stringstream out;

        out << indent << "maxTextureDimension1D: " << FormatNumber(limits.maxTextureDimension1D)
            << "\n";
        out << indent << "maxTextureDimension2D: " << FormatNumber(limits.maxTextureDimension2D)
            << "\n";
        out << indent << "maxTextureDimension3D: " << FormatNumber(limits.maxTextureDimension3D)
            << "\n";
        out << indent << "maxTextureArrayLayers: " << FormatNumber(limits.maxTextureArrayLayers)
            << "\n";
        out << indent << "maxBindGroups: " << FormatNumber(limits.maxBindGroups) << "\n";
        out << indent
            << "maxBindGroupsPlusVertexBuffers: " << FormatNumber(limits.maxBindGroupsPlusVertexBuffers)
            << "\n";
        out << indent << "maxBindingsPerBindGroup: " << FormatNumber(limits.maxBindingsPerBindGroup)
            << "\n";
        out << indent << "maxDynamicUniformBuffersPerPipelineLayout: "
            << FormatNumber(limits.maxDynamicUniformBuffersPerPipelineLayout) << "\n";
        out << indent << "maxDynamicStorageBuffersPerPipelineLayout: "
            << FormatNumber(limits.maxDynamicStorageBuffersPerPipelineLayout) << "\n";
        out << indent << "maxSampledTexturesPerShaderStage: "
            << FormatNumber(limits.maxSampledTexturesPerShaderStage) << "\n";
        out << indent << "maxSamplersPerShaderStage: " << FormatNumber(limits.maxSamplersPerShaderStage)
            << "\n";
        out << indent << "maxStorageBuffersPerShaderStage: "
            << FormatNumber(limits.maxStorageBuffersPerShaderStage) << "\n";
        out << indent << "maxStorageTexturesPerShaderStage: "
            << FormatNumber(limits.maxStorageTexturesPerShaderStage) << "\n";
        out << indent << "maxUniformBuffersPerShaderStage: "
            << FormatNumber(limits.maxUniformBuffersPerShaderStage) << "\n";
        out << indent
            << "maxUniformBufferBindingSize: " << FormatNumber(limits.maxUniformBufferBindingSize)
            << "\n";
        out << indent
            << "maxStorageBufferBindingSize: " << FormatNumber(limits.maxStorageBufferBindingSize)
            << "\n";
        out << indent << "minUniformBufferOffsetAlignment: "
            << FormatNumber(limits.minUniformBufferOffsetAlignment) << "\n";
        out << indent << "minStorageBufferOffsetAlignment: "
            << FormatNumber(limits.minStorageBufferOffsetAlignment) << "\n";
        out << indent << "maxVertexBuffers: " << FormatNumber(limits.maxVertexBuffers) << "\n";
        out << indent << "maxBufferSize: " << FormatNumber(limits.maxBufferSize) << "\n";
        out << indent << "maxVertexAttributes: " << FormatNumber(limits.maxVertexAttributes) << "\n";
        out << indent
            << "maxVertexBufferArrayStride: " << FormatNumber(limits.maxVertexBufferArrayStride)
            << "\n";
        out << indent
            << "maxInterStageShaderVariables: " << FormatNumber(limits.maxInterStageShaderVariables)
            << "\n";
        out << indent << "maxColorAttachments: " << FormatNumber(limits.maxColorAttachments) << "\n";
        out << indent << "maxColorAttachmentBytesPerSample: "
            << FormatNumber(limits.maxColorAttachmentBytesPerSample) << "\n";
        out << indent
            << "maxComputeWorkgroupStorageSize: " << FormatNumber(limits.maxComputeWorkgroupStorageSize)
            << "\n";
        out << indent << "maxComputeInvocationsPerWorkgroup: "
            << FormatNumber(limits.maxComputeInvocationsPerWorkgroup) << "\n";
        out << indent << "maxComputeWorkgroupSizeX: " << FormatNumber(limits.maxComputeWorkgroupSizeX)
            << "\n";
        out << indent << "maxComputeWorkgroupSizeY: " << FormatNumber(limits.maxComputeWorkgroupSizeY)
            << "\n";
        out << indent << "maxComputeWorkgroupSizeZ: " << FormatNumber(limits.maxComputeWorkgroupSizeZ)
            << "\n";
        out << indent << "maxComputeWorkgroupsPerDimension: "
            << FormatNumber(limits.maxComputeWorkgroupsPerDimension) << "\n";

        return out.str();
    }

    void DawnDevice::Init()
    {
        wgpu::InstanceDescriptor idesc = {};
        idesc.capabilities.timedWaitAnyEnable = true;
        m_Instance = wgpu::CreateInstance(&idesc);

        if (m_Instance == nullptr)
        {
            std::cerr << "not able to fetch gpu instance";
            exit(EXIT_FAILURE);
        }

        wgpu::RequestAdapterOptions adapterOptions =
        {
            .powerPreference = wgpu::PowerPreference::HighPerformance,
            .backendType = wgpu::BackendType::Undefined,
        };

        m_Instance.WaitAny(
            m_Instance.RequestAdapter(
                &adapterOptions, wgpu::CallbackMode::WaitAnyOnly,
                [&](wgpu::RequestAdapterStatus status, wgpu::Adapter adapter, wgpu::StringView message)
                {
                    if (status != wgpu::RequestAdapterStatus::Success)
                    {
                        std::cerr << "not able to fetch gpu adapter: " << std::string_view(message);
                        exit(EXIT_FAILURE);
                    }

                    m_Adapter = std::move(adapter);
                }
            ),
            UINT64_MAX
        );

        if (m_Adapter == nullptr)
        {
            std::cerr << "RequestAdapter failed!\n";
            exit(EXIT_FAILURE);
        }

        wgpu::DeviceDescriptor deviceDesc = {};
        deviceDesc.SetDeviceLostCallback(
            wgpu::CallbackMode::AllowSpontaneous,
            [](const wgpu::Device&, wgpu::DeviceLostReason reason, wgpu::StringView message)
            {
                const char* reasonName = "";
                switch (reason)
                {
                case wgpu::DeviceLostReason::Unknown:
                    reasonName = "Unknown";
                    break;
                case wgpu::DeviceLostReason::Destroyed:
                    reasonName = "Destroyed";
                    break;
                case wgpu::DeviceLostReason::CallbackCancelled:
                    reasonName = "CallbackCancelled";
                    break;
                case wgpu::DeviceLostReason::FailedCreation:
                    reasonName = "FailedCreation";
                    break;
                default:
                    reasonName = "Unknown";
                    break;
                }
                
                std::stringstream out;
                out << "Device lost due to: " << "[" << reasonName << "] " << std::string_view(message) << std::endl;

                GFX_ERROR(out.str());
            }
        );
        deviceDesc.SetUncapturedErrorCallback(
            [](const wgpu::Device&, wgpu::ErrorType type, wgpu::StringView message)
            {
                const char* errorType = "";
                switch (type)
                {
                case wgpu::ErrorType::Validation:
                    errorType = "Validation";
                    break;
                case wgpu::ErrorType::OutOfMemory:
                    errorType = "Out of memory";
                    break;
                case wgpu::ErrorType::Internal:
                    errorType = "Interanl";
                    break;
                case wgpu::ErrorType::Unknown:
                    errorType = "Unknown";
                    break;
                default:
                    errorType = "case default error callback";
                    break;
                }

                std::stringstream out;
                out << "Device error: " << "[" << errorType << "] " << std::string_view(message) << std::endl;

                GFX_ERROR(out.str());
            }
        );

        m_Instance.WaitAny(
            m_Adapter.RequestDevice(
                &deviceDesc, wgpu::CallbackMode::WaitAnyOnly,
                [&](wgpu::RequestDeviceStatus status, wgpu::Device device, wgpu::StringView message)
                {
                    if (status != wgpu::RequestDeviceStatus::Success)
                    {
                        std::cerr << "not able to fetch device from adapter: " << std::string_view(message);
                        exit(EXIT_FAILURE);
                    }

                    m_Device = std::move(device);
                }
            ),
            UINT64_MAX
        );

        if (m_Device == nullptr)
        {
            std::cerr << "RequestDevice failed!\n";
            exit(EXIT_FAILURE);
        }

        wgpu::DawnAdapterPropertiesPowerPreference power_procs = {};
        wgpu::AdapterInfo adapterInfo = {};
        adapterInfo.nextInChain = &power_procs;

        m_Adapter.GetInfo(&adapterInfo);
        std::stringstream infoStream;
        infoStream << "VendorID: " << std::hex << adapterInfo.vendorID << std::dec << "\n";
        infoStream << "Vendor: " << std::string_view(adapterInfo.vendor) << "\n";
        infoStream << "Architecture: " << std::string_view(adapterInfo.architecture) << "\n";
        infoStream << "DeviceID: " << std::hex << adapterInfo.deviceID << std::dec << "\n";
        infoStream << "Name: " << std::string_view(adapterInfo.device) << "\n";
        infoStream << "Driver description: " << std::string_view(adapterInfo.description) << "\n";
        GFX_TRACE(infoStream.str());
        
        s_DeviceDesc =
        {
            .vendorID = adapterInfo.vendorID,
            .vendor = std::string(adapterInfo.vendor),
            .architecture = std::string(adapterInfo.architecture),
            .deviceID = adapterInfo.deviceID,
            .name = std::string(adapterInfo.device),
            .driver = std::string(adapterInfo.description)
        }; 

        wgpu::Limits adapterLimits;
        m_Adapter.GetLimits(&adapterLimits);
        std::stringstream limitsStream;
        limitsStream << "\n";
        limitsStream << "  Adapter Limits\n";
        limitsStream << "  ==============\n";
        limitsStream << LimitsToString(adapterLimits, "    ") << "\n";
        GFX_TRACE(limitsStream.str());
        
        s_AdapterDesc =
        {
			.maxTextureDimension1D = adapterLimits.maxTextureDimension1D,
			.maxTextureDimension2D = adapterLimits.maxTextureDimension2D,
			.maxTextureDimension3D = adapterLimits.maxTextureDimension3D,
			.maxTextureArrayLayers = adapterLimits.maxTextureArrayLayers,
			.maxBindGroups = adapterLimits.maxBindGroups,
			.maxBindGroupsPlusVertexBuffers = adapterLimits.maxBindGroupsPlusVertexBuffers,
			.maxBindingsPerBindGroup = adapterLimits.maxBindingsPerBindGroup,
			.maxDynamicUniformBuffersPerPipelineLayout = adapterLimits.maxDynamicUniformBuffersPerPipelineLayout,
			.maxDynamicStorageBuffersPerPipelineLayout = adapterLimits.maxDynamicUniformBuffersPerPipelineLayout,
			.maxSampledTexturesPerShaderStage = adapterLimits.maxSampledTexturesPerShaderStage,
			.maxSamplersPerShaderStage = adapterLimits.maxSamplersPerShaderStage,
			.maxStorageBuffersPerShaderStage = adapterLimits.maxStorageBuffersPerShaderStage,
			.maxStorageTexturesPerShaderStage = adapterLimits.maxStorageTexturesPerShaderStage,
			.maxUniformBuffersPerShaderStage = adapterLimits.maxUniformBuffersPerShaderStage,
			.maxUniformBufferBindingSize = adapterLimits.maxUniformBufferBindingSize,
			.maxStorageBufferBindingSize = adapterLimits.maxStorageBufferBindingSize,
			.minUniformBufferOffsetAlignment = adapterLimits.minUniformBufferOffsetAlignment,
			.minStorageBufferOffsetAlignment = adapterLimits.minStorageBufferOffsetAlignment,
			.maxVertexBuffers = adapterLimits.maxVertexBuffers,
			.maxBufferSize = adapterLimits.maxBufferSize,
			.maxVertexAttributes = adapterLimits.maxVertexAttributes,
			.maxVertexBufferArrayStride = adapterLimits.maxVertexBufferArrayStride,
			.maxInterStageShaderVariables = adapterLimits.maxInterStageShaderVariables,
			.maxColorAttachments = adapterLimits.maxColorAttachments,
			.maxColorAttachmentBytesPerSample = adapterLimits.maxColorAttachmentBytesPerSample,
			.maxComputeWorkgroupStorageSize = adapterLimits.maxComputeWorkgroupStorageSize,
			.maxComputeInvocationsPerWorkgroup = adapterLimits.maxComputeInvocationsPerWorkgroup,
			.maxComputeWorkgroupSizeX = adapterLimits.maxComputeWorkgroupSizeX,
			.maxComputeWorkgroupSizeY = adapterLimits.maxComputeWorkgroupSizeY,
			.maxComputeWorkgroupSizeZ = adapterLimits.maxComputeWorkgroupSizeZ,
			.maxComputeWorkgroupsPerDimension = adapterLimits.maxComputeWorkgroupsPerDimension,
        };

        return;
    }
    
    void DawnDevice::ShutDown()
    {
        m_Device.Tick();
        m_Device.Destroy(); 
        m_Device = nullptr;
        m_Adapter = nullptr;
        m_Instance = nullptr;
    }

    const wgpu::Instance& DawnDevice::GetDawnInstance()
    {
        return m_Instance;
    }

    const wgpu::Adapter& DawnDevice::GetDawnAdapter()
    {
        return m_Adapter;
    }

    const wgpu::Device& DawnDevice::GetDawnDevice()
    {
        return m_Device;
    }
}
