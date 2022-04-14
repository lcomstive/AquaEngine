#include <filesystem>
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

	auto fileSink = make_shared<spdlog::sinks::basic_file_sink_mt>("Logs/Engine.txt");
	fileSink->set_pattern("[%H:%M:%S %z][%t][%=8n][%7l] %v");
	fileSink->set_level(spdlog::level::trace);

	auto logger = make_shared<spdlog::logger>(spdlog::logger("Engine", { consoleSink, fileSink }));
	logger->set_level(spdlog::level::trace);
	spdlog::set_default_logger(logger);
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
	spdlog::info("{:>12}: {}", "Launch Dir", std::filesystem::current_path().string());
	spdlog::error("Test error");
	spdlog::trace("Test tracing");
	spdlog::warn("Test warning");
	spdlog::debug("Test debug");

	spdlog::info("\n\nPress ENTER to exit...");
	getchar();

    spdlog::shutdown();
	return 0;
}
