#include <dawn/dawnDevice.hpp>

namespace gfx
{
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
                case wgpu::DeviceLostReason::InstanceDropped:
                    reasonName = "InstanceDropped";
                    break;
                case wgpu::DeviceLostReason::FailedCreation:
                    reasonName = "FailedCreation";
                    break;
                default:
                    reasonName = "Unknown";
                    break;
                }

                std::cerr << "Device lost due to: " << "[" << reasonName << "] " << std::string_view(message) << std::endl;
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

                std::cerr << "Device error: " << "[" << errorType << "] " << std::string_view(message) << std::endl;
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
        std::cout << "VendorID: " << std::hex << adapterInfo.vendorID << std::dec << "\n";
        std::cout << "Vendor: " << std::string_view(adapterInfo.vendor) << "\n";
        std::cout << "Architecture: " << std::string_view(adapterInfo.architecture) << "\n";
        std::cout << "DeviceID: " << std::hex << adapterInfo.deviceID << std::dec << "\n";
        std::cout << "Name: " << std::string_view(adapterInfo.device) << "\n";
        std::cout << "Driver description: " << std::string_view(adapterInfo.description) << "\n";
        
        DeviceDescriptor desc =
        {
            .vendorID = adapterInfo.vendorID,
            .vendor = std::string(adapterInfo.vendor),
            .architecture = std::string(adapterInfo.architecture),
            .deviceID = adapterInfo.deviceID,
            .name = std::string(adapterInfo.device),
            .driver = std::string(adapterInfo.description)
        }; 
        
        SetDeviceDescriptor(desc);

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

    void DawnDevice::SetDeviceDescriptor(const DeviceDescriptor &desc)
    {
        m_Descriptor = desc;
    }

    const DeviceDescriptor& DawnDevice::GetDeviceDescriptor()
    {
        return m_Descriptor;
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
