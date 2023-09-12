#pragma once

#include <memory>

#include <spdlog/spdlog.h>

#include "Core.h"


namespace CE
{
		class CT_DLL Log
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
#define CT_CORE_TRACE(...)	::CE::Log::GetCoreLogger()->trace(__VA_ARGS__);
#define CT_CORE_DEBUG(...)	::CE::Log::GetCoreLogger()->debug(__VA_ARGS__);
#define CT_CORE_INFO(...)	::CE::Log::GetCoreLogger()->info(__VA_ARGS__);
#define CT_CORE_WARN(...)	::CE::Log::GetCoreLogger()->warn(__VA_ARGS__);
#define CT_CORE_ERROR(...)	::CE::Log::GetCoreLogger()->error(__VA_ARGS__);
#define CT_CORE_FATAL(...)	::CE::Log::GetCoreLogger()->critical(__VA_ARGS__);

// client logging system
#define CT_TRACE(...)		::CE::Log::GetClientLogger()->trace(__VA_ARGS__);
#define CT_DEBUG(...)		::CE::Log::GetClientLogger()->debug(__VA_ARGS__);
#define CT_INFO(...)		::CE::Log::GetClientLogger()->info(__VA_ARGS__);
#define CT_WARN(...)		::CE::Log::GetClientLogger()->warn(__VA_ARGS__);
#define CT_ERROR(...)		::CE::Log::GetClientLogger()->error(__VA_ARGS__);
#define CT_FATAL(...)		::CE::Log::GetClientLogger()->critical(__VA_ARGS__);