#include "SD_PCH.h"

#include "Logger.h"

#include <spdlog/sinks/stdout_color_sinks.h>

namespace Soda
{
	std::shared_ptr<spdlog::logger> Log::s_EngineLogger;
	std::shared_ptr<spdlog::logger> Log::s_UserLogger;

	void Log::Init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");

		s_EngineLogger = spdlog::stdout_color_mt("ENGINE");
		s_EngineLogger->set_level(spdlog::level::trace);

		s_UserLogger = spdlog::stdout_color_mt("USER");
		s_UserLogger->set_level(spdlog::level::trace);
	}
}