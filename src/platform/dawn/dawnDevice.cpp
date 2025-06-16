#include <dawn/dawnDevice.hpp>

#include <log.hpp>
#include <assert.hpp>

#include <sstream>
#include <string>

#include <dawn/native/DawnNative.h>

namespace AdapterInfo
{
    // Wraps a string to about 75 characters and prints indented. Splits on whitespace instead of
// between characters in a word.
    std::string WrapString(const std::string& in, const std::string& indent) {
        std::stringstream out;

        size_t last_space = 0;
        size_t start_pos = 0;
        for (size_t i = 0; i < in.size(); ++i) {
            if (in[i] == ' ') {
                last_space = i;
            }
            else if (in[i] == '\n') {
                last_space = i;
            }

            if ((i - start_pos) != 0 && ((i - start_pos) % 75) == 0) {
                out << indent << in.substr(start_pos, last_space - start_pos) << "\n";
                start_pos = last_space + 1;
                last_space = start_pos;
            }
        }
        out << indent << in.substr(start_pos, in.size() - start_pos);

        return out.str();
    }

    std::string AdapterTypeToString(wgpu::AdapterType type) {
        switch (type) {
        case wgpu::AdapterType::DiscreteGPU:
            return "discrete GPU";
        case wgpu::AdapterType::IntegratedGPU:
            return "integrated GPU";
        case wgpu::AdapterType::CPU:
            return "CPU";
        case wgpu::AdapterType::Unknown:
            break;
        }
        return "unknown";
    }

    std::string BackendTypeToString(wgpu::BackendType type) {
        switch (type) {
        case wgpu::BackendType::Null:
            return "Null";
        case wgpu::BackendType::WebGPU:
            return "WebGPU";
        case wgpu::BackendType::D3D11:
            return "D3D11";
        case wgpu::BackendType::D3D12:
            return "D3D12";
        case wgpu::BackendType::Metal:
            return "Metal";
        case wgpu::BackendType::Vulkan:
            return "Vulkan";
        case wgpu::BackendType::OpenGL:
            return "OpenGL";
        case wgpu::BackendType::OpenGLES:
            return "OpenGLES";
        case wgpu::BackendType::Undefined:
            return "Undefined";
        }
        return "unknown";
    }

    std::string PowerPreferenceToString(const wgpu::DawnAdapterPropertiesPowerPreference& prop) {
        switch (prop.powerPreference) {
        case wgpu::PowerPreference::LowPower:
            return "low power";
        case wgpu::PowerPreference::HighPerformance:
            return "high performance";
        case wgpu::PowerPreference::Undefined:
            return "<undefined>";
        }
        return "<unknown>";
    }

    std::string AsHex(uint32_t val) {
        std::stringstream hex;
        hex << "0x" << std::uppercase << std::setfill('0') << std::setw(4) << std::hex << val;
        return hex.str();
    }

    std::string AdapterInfoToString(const wgpu::AdapterInfo& info) {
        std::stringstream out;
        out << "VendorID: " << AsHex(info.vendorID) << "\n";
        out << "Vendor: " << info.vendor << "\n";
        out << "Architecture: " << info.architecture << "\n";
        out << "DeviceID: " << AsHex(info.deviceID) << "\n";
        out << "Name: " << info.device << "\n";
        out << "Driver description: " << info.description << "\n";
        out << "Adapter Type: " << AdapterTypeToString(info.adapterType) << "\n";
        out << "Backend Type: " << BackendTypeToString(info.backendType) << "\n";

        return out.str();
    }

    std::string FormatNumber(uint64_t num) {
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

    std::string LimitsToString(const wgpu::Limits& limits, const std::string& indent) {
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
    
    std::string DumpAdapterInfo(const wgpu::Adapter& adapter) {
        wgpu::AdapterPropertiesSubgroups subgroup_props{};

        wgpu::DawnAdapterPropertiesPowerPreference power_props{};
        power_props.nextInChain = &subgroup_props;

        wgpu::AdapterInfo info{};
        info.nextInChain = &power_props;

        std::stringstream out;
        adapter.GetInfo(&info);
        out << AdapterInfoToString(info);
        out << "Subgroup min size: " << subgroup_props.subgroupMinSize << "\n";
        out << "Subgroup max size: " << subgroup_props.subgroupMaxSize << "\n";
        out << "Power: " << PowerPreferenceToString(power_props) << "\n";
        out << "\n";

        return out.str();
    }

    std::string DumpAdapterFeatures(const wgpu::Adapter& adapter) {
        wgpu::SupportedFeatures supportedFeatures;

        std::stringstream out;
        adapter.GetFeatures(&supportedFeatures);
        out << "  Features\n";
        out << "  ========\n";
        for (uint32_t i = 0; i < supportedFeatures.featureCount; ++i) {
            wgpu::FeatureName f = supportedFeatures.features[i];
            auto info = dawn::native::GetFeatureInfo(f);
            out << "   * " << info->name << "\n";
            out << WrapString(info->description, "      ") << "\n";
            out << "      " << info->url << "\n";
        }

        return out.str();
    }

    std::string DumpAdapterLimits(const wgpu::Adapter& adapter) {
        wgpu::Limits adapterLimits;

        std::stringstream out;
        if (adapter.GetLimits(&adapterLimits)) {
            out << "\n";
            out << "  Adapter Limits\n";
            out << "  ==============\n";
            out << LimitsToString(adapterLimits, "    ") << "\n";
        }

        return out.str();
    }

    std::string DumpAdapter(const wgpu::Adapter& adapter) {
        std::stringstream out;

        out << "Adapter\n";
        out << "=======\n";

        out << DumpAdapterInfo(adapter);
        out << DumpAdapterFeatures(adapter);
        out << DumpAdapterLimits(adapter);

        return out.str();
    }
}


namespace gfx
{
    void DawnDevice::Init()
    {
        wgpu::InstanceDescriptor idesc = {};
        idesc.capabilities.timedWaitAnyEnable = true;
        m_Instance = wgpu::CreateInstance(&idesc);

        GFX_ASSERT(m_Instance != nullptr, "Not able to fetch gpu instance!");

        wgpu::RequestAdapterOptions adapterOptions =
        {
            .powerPreference = wgpu::PowerPreference::HighPerformance,
            .backendType = wgpu::BackendType::Vulkan
        };

        m_Instance.WaitAny(
            m_Instance.RequestAdapter(
                &adapterOptions, wgpu::CallbackMode::WaitAnyOnly,
                [&](wgpu::RequestAdapterStatus status, wgpu::Adapter adapter, wgpu::StringView message)
                {
                    if (status != wgpu::RequestAdapterStatus::Success)
                    {
                        std::stringstream out;
                        out << "Not able to fetch gpu adatper: " << std::string_view(message);
                        GFX_ASSERT(false, out.str());
                    }

                    m_Adapter = std::move(adapter);
                }
            ),
            UINT64_MAX
        );
        GFX_ASSERT(m_Adapter != nullptr, "Adapter Request failed!");

        wgpu::Limits adapterLimits;
        m_Adapter.GetLimits(&adapterLimits);

        wgpu::FeatureName features[] =
        {
            wgpu::FeatureName::CoreFeaturesAndLimits
        };

        wgpu::DeviceDescriptor deviceDesc = {};
        deviceDesc.requiredFeatureCount = sizeof(features) / sizeof(wgpu::FeatureName);
        deviceDesc.requiredFeatures = features;

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
        deviceDesc.requiredLimits = &adapterLimits;

        m_Instance.WaitAny(
            m_Adapter.RequestDevice(
                &deviceDesc, wgpu::CallbackMode::WaitAnyOnly,
                [&](wgpu::RequestDeviceStatus status, wgpu::Device device, wgpu::StringView message)
                {
                    if (status != wgpu::RequestDeviceStatus::Success)
                    {
                        std::stringstream out;
                        out << "not able to fetch device from adapter: " << std::string_view(message);
                        GFX_ASSERT(false, out.str());
                    }

                    m_Device = std::move(device);
                }
            ),
            UINT64_MAX
        );
        GFX_ASSERT(m_Device != nullptr, "Device Request failed!");

        wgpu::DawnAdapterPropertiesPowerPreference power_procs = {};
        wgpu::AdapterInfo adapterInfo = {};
        adapterInfo.nextInChain = &power_procs;
        m_Adapter.GetInfo(&adapterInfo);
        
        s_DeviceDesc =
        {
            .vendorID = adapterInfo.vendorID,
            .vendor = std::string(adapterInfo.vendor),
            .architecture = std::string(adapterInfo.architecture),
            .deviceID = adapterInfo.deviceID,
            .name = std::string(adapterInfo.device),
            .driver = std::string(adapterInfo.description)
        }; 

        GFX_TRACE(AdapterInfo::DumpAdapter(m_Adapter));

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
