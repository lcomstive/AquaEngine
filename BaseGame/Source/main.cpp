#include <spdlog/spdlog.h>
#include <AquaEngine/API.hpp>

#include <memory>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
void InitLogger()
{
    auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
#ifndef NDEBUG // Debug mode
    console_sink->set_level(spdlog::level::debug);
#else
    console_sink->set_level(spdlog::level::info);
#endif
    console_sink->set_pattern("[%H:%M:%S %z] [%^%L%$] %v");

    auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("log.txt", true);
    file_sink->set_level(spdlog::level::trace);

    spdlog::logger logger("logger", { console_sink, file_sink });
    logger.set_level(spdlog::level::debug);
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

	return 0;
}
