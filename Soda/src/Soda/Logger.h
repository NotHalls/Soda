#pragma once

#include "SD_PCH.h"

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

#include "Core.h"


namespace Soda
{
		class Log
		{
		public:
			// we have to initialize the spdlog before proceding
			static void Init();

			// the Geter functions for our two options
			inline static std::shared_ptr<spdlog::logger>& GetEngineLogger() { return s_EngineLogger; }
			inline static std::shared_ptr<spdlog::logger>& GetUserLogger() { return s_UserLogger; }

		private:
			// these are our two looging options
			// one for the Engine Development & one for the User Game Development
			static std::shared_ptr<spdlog::logger> s_EngineLogger;
			static std::shared_ptr<spdlog::logger> s_UserLogger;
		};
}


// core logging system
#define SD_ENGINE_TRACE(...)	::Soda::Log::GetEngineLogger()->trace(__VA_ARGS__);
#define SD_ENGINE_MSG(...)		::Soda::Log::GetEngineLogger()->debug(__VA_ARGS__);
#define SD_ENGINE_INFO(...)		::Soda::Log::GetEngineLogger()->info(__VA_ARGS__);
#define SD_ENGINE_WARN(...)		::Soda::Log::GetEngineLogger()->warn(__VA_ARGS__);
#define SD_ENGINE_ERROR(...)	::Soda::Log::GetEngineLogger()->error(__VA_ARGS__);
#define SD_ENGINE_FATAL(...)	::Soda::Log::GetEngineLogger()->critical(__VA_ARGS__);
							  
// clien logging system		  
#define SD_TRACE(...)		::Soda::Log::GetUserLogger()->trace(__VA_ARGS__);
#define SD_MSG(...)			::Soda::Log::GetUserLogger()->debug(__VA_ARGS__);
#define SD_INFO(...)		::Soda::Log::GetUserLogger()->info(__VA_ARGS__);
#define SD_WARN(...)		::Soda::Log::GetUserLogger()->warn(__VA_ARGS__);
#define SD_ERROR(...)		::Soda::Log::GetUserLogger()->error(__VA_ARGS__);
#define SD_FATAL(...)		::Soda::Log::GetUserLogger()->critical(__VA_ARGS__);