#include <stdlib.h> 
#include <spdlog/spdlog.h>
#include <AquaEngine/API.hpp>

#include <memory>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

using namespace std;

void InitLogger()
{
	auto consoleSink = make_shared<spdlog::sinks::stdout_color_sink_mt>();
	consoleSink->set_pattern("%^[%=8n][%7l] %v %$");
#ifndef NDEBUG
	consoleSink->set_level(spdlog::level::debug);
#else
	consoleSink->set_level(spdlog::level::info);
#endif

	std::string logDirectory = "Logs/";

#if defined(AQUA_ENGINE_PLATFORM_WINDOWS)
	char* appdata = getenv("appdata");
	logDirectory = string(appData) + logDirectory;
#elif defined(AQUA_ENGINE_PLATFORM_MAC)
	logDirectory = string(getenv("HOME")) + "/Library/Caches/Aqua Engine/" + logDirectory;
#endif

	auto fileSink = make_shared<spdlog::sinks::basic_file_sink_mt>(logDirectory + "/Engine.txt");
	fileSink->set_pattern("[%H:%M:%S %z][%t][%=8n][%7l] %v");
	fileSink->set_level(spdlog::level::trace);

	auto logger = make_shared<spdlog::logger>(spdlog::logger("Engine", { consoleSink, fileSink }));
	logger->set_level(spdlog::level::trace);
	spdlog::set_default_logger(logger);

	spdlog::info("{:>12}: {}", "Log Folder", logDirectory);
}

int main()
{
	InitLogger();

	spdlog::trace("\n\n");
    spdlog::info("{:>12}: v{}.{}.{}-{} [{}]",
					"Engine",
					AQUA_ENGINE_VERSION_MAJOR,
					AQUA_ENGINE_VERSION_MINOR,
					AQUA_ENGINE_VERSION_PATCH,
					AQUA_ENGINE_VERSION_REV,
					AQUA_ENGINE_VERSION_BRANCH
				);
    spdlog::info("{:>12}: {}", "Platform", AquaEngine::PlatformName);
    spdlog::info("{:>12}: v{}.{}.{}", "SPDLog", SPDLOG_VER_MAJOR, SPDLOG_VER_MINOR, SPDLOG_VER_PATCH);
	spdlog::error("Test error");
	spdlog::trace("Test tracing");
	spdlog::warn("Test warning");
	spdlog::debug("Test debug");

    spdlog::shutdown();
	return 0;
}
