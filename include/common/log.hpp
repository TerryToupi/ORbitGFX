#ifndef __LOGGING_HPP__
#define __LOGGING_HPP__

#pragma warning(push, 0)
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#pragma warning(pop)

namespace diag 
{
	class Logger
	{
	public:
		static void Init();
		static void ShutDown();

		static std::shared_ptr<spdlog::logger>& GetLogger();

	private:
		static inline std::shared_ptr<spdlog::logger> s_Logger; 
	};

}

#define GFX_TRACE(...)         ::diag::Logger::GetLogger()->trace(__VA_ARGS__)
#define GFX_INFO(...)          ::diag::Logger::GetLogger()->info(__VA_ARGS__)
#define GFX_WARN(...)          ::diag::Logger::GetLogger()->warn(__VA_ARGS__)
#define GFX_ERROR(...)         ::diag::Logger::GetLogger()->error(__VA_ARGS__)
#define GFX_CRITICAL(...)      ::diag::Logger::GetLogger()->critical(__VA_ARGS__)

#endif