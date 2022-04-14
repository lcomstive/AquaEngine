#include <stdlib.h> 
#include <iostream>
#include <filesystem>
#include <spdlog/spdlog.h>
#include <AquaEngine/API.hpp>

#include <memory>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

using namespace std;

string LogDirectory = "Aqua Engine/Logs/";
void InitLogger()
{
	auto consoleSink = make_shared<spdlog::sinks::stdout_color_sink_mt>();
	consoleSink->set_pattern("%^[%=8n][%7l] %v %$");
#ifndef NDEBUG
	consoleSink->set_level(spdlog::level::debug);
#else
	consoleSink->set_level(spdlog::level::info);
#endif

#if defined(AQUA_ENGINE_PLATFORM_WINDOWS)
	char* appdata = getenv("appdata");
	LogDirectory = string(appdata) + "/" + LogDirectory;
#elif defined(AQUA_ENGINE_PLATFORM_MAC)
	LogDirectory = string(getenv("HOME")) + "/Library/Caches/" + LogDirectory;
#elif defined(AQUA_ENGINE_PLATFORM_LINUX)
	LogDirectory = "./Logs/";
#endif

	auto fileSink = make_shared<spdlog::sinks::basic_file_sink_mt>(LogDirectory + "Engine.txt");
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
	spdlog::info("");
	spdlog::info("{:>12}: {}", "Log Folder", LogDirectory);
	spdlog::info("{:>12}: {}", "Launch Dir", std::filesystem::current_path().string());
	spdlog::error("Test error");
	spdlog::trace("Test tracing");
	spdlog::warn("Test warning");
	spdlog::debug("Test debug");

#if defined(AQUA_ENGINE_PLATFORM_MAC) || defined(AQUA_ENGINE_PLATFORM_LINUX)
	spdlog::info("DYLD_LIBRARY_PATH = {}", getenv("DYLD_LIBRARY_PATH"));
#endif

	cout << endl << endl << "Press ENTER to exit..." << endl;
	getchar();
    spdlog::shutdown();
	return 0;
}
