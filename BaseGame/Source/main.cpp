#include <spdlog/spdlog.h>
#include <AquaEngine/API.hpp>

#include <memory>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

void InitLogger()
{
    auto logger = spdlog::basic_logger_mt("Engine Core", "Logs/Engine.txt", true);
    logger->set_level(spdlog::level::trace);
    spdlog::set_default_logger(logger);
}

int main()
{
	InitLogger();

	spdlog::info("Loading game...");

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

    spdlog::shutdown();
	return 0;
}
