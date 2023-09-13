#pragma once

#include <memory>

#include <spdlog/spdlog.h>

#include "Core.h"


namespace Soda
{
		class SD_DLL Log
		{
		public:
			static void Init();

			inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
			inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

		private:
			static std::shared_ptr<spdlog::logger> s_CoreLogger;
			static std::shared_ptr<spdlog::logger> s_ClientLogger;
		};
}


// core logging system
#define SD_CORE_TRACE(...)	::Soda::Log::GetCoreLogger()->trace(__VA_ARGS__);
#define SD_CORE_DEBUG(...)	::Soda::Log::GetCoreLogger()->debug(__VA_ARGS__);
#define SD_CORE_INFO(...)	::Soda::Log::GetCoreLogger()->info(__VA_ARGS__);
#define SD_CORE_WARN(...)	::Soda::Log::GetCoreLogger()->warn(__VA_ARGS__);
#define SD_CORE_ERROR(...)	::Soda::Log::GetCoreLogger()->error(__VA_ARGS__);
#define SD_CORE_FATAL(...)	::Soda::Log::GetCoreLogger()->critical(__VA_ARGS__);
							  
// clien logging system		  
#define SD_TRACE(...)		::Soda::Log::GetClientLogger()->trace(__VA_ARGS__);
#define SD_MSG(...)			::Soda::Log::GetClientLogger()->debug(__VA_ARGS__);
#define SD_INFO(...)		::Soda::Log::GetClientLogger()->info(__VA_ARGS__);
#define SD_WARN(...)		::Soda::Log::GetClientLogger()->warn(__VA_ARGS__);
#define SD_ERROR(...)		::Soda::Log::GetClientLogger()->error(__VA_ARGS__);
#define SD_FATAL(...)		::Soda::Log::GetClientLogger()->critical(__VA_ARGS__);