#include<spdlog/sinks/stdout_color_sinks.h>

#include<Helios/Core/Log.h>

namespace Helios {
	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

	void Log::Init() {
		spdlog::set_pattern("%^[%T] [%l] %n: %v%$");

		spdlog::set_level(spdlog::level::trace);

		//MT is for multi-threaded
		s_CoreLogger = spdlog::stdout_color_mt("Helios");
		s_CoreLogger->set_level(spdlog::level::trace);

		s_ClientLogger = spdlog::stderr_color_mt("Sandbox");
		s_ClientLogger->set_level(spdlog::level::trace);
	}

}