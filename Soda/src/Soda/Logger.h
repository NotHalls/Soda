#pragma once

#include "SD_PCH.h"

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

#include "Core.h"


namespace Soda
{
		class SD_DLL Log
		{
		public:
			static void Init();

			inline static std::shared_ptr<spdlog::logger>& GetEngineLogger() { return s_EngineLogger; }
			inline static std::shared_ptr<spdlog::logger>& GetUserLogger() { return s_UserLogger; }

		private:
			static std::shared_ptr<spdlog::logger> s_EngineLogger;
			static std::shared_ptr<spdlog::logger> s_UserLogger;
		};
}


// core logging system
#define SD_CORE_TRACE(...)	::Soda::Log::GetEngineLogger()->trace(__VA_ARGS__);
#define SD_CORE_MSG(...)	::Soda::Log::GetEngineLogger()->debug(__VA_ARGS__);
#define SD_CORE_INFO(...)	::Soda::Log::GetEngineLogger()->info(__VA_ARGS__);
#define SD_CORE_WARN(...)	::Soda::Log::GetEngineLogger()->warn(__VA_ARGS__);
#define SD_CORE_ERROR(...)	::Soda::Log::GetEngineLogger()->error(__VA_ARGS__);
#define SD_CORE_FATAL(...)	::Soda::Log::GetEngineLogger()->critical(__VA_ARGS__);
							  
// clien logging system		  
#define SD_TRACE(...)		::Soda::Log::GetUserLogger()->trace(__VA_ARGS__);
#define SD_MSG(...)			::Soda::Log::GetUserLogger()->debug(__VA_ARGS__);
#define SD_INFO(...)		::Soda::Log::GetUserLogger()->info(__VA_ARGS__);
#define SD_WARN(...)		::Soda::Log::GetUserLogger()->warn(__VA_ARGS__);
#define SD_ERROR(...)		::Soda::Log::GetUserLogger()->error(__VA_ARGS__);
#define SD_FATAL(...)		::Soda::Log::GetUserLogger()->critical(__VA_ARGS__);