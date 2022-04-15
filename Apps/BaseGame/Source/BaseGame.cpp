#include <flecs.h>
#include <filesystem>
#include <BaseGame.hpp>
#include <AquaEngine/API.hpp>
#include <BGFXEntry/bgfx_utils.h>

// spdlog
#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

// #ifndef NDEBUG // Debug mode
float BytesToGB(long long input)
{
	return input
		/ 1024.0f  // KB
		/ 1024.0f  // MB
		/ 1024.0f; // GB
}
// #endif

using namespace std;

BaseGame::BaseGame() : entry::AppI("Base Game", "Aqua Engine game launcher", "https://lcomstive.github.io/AquaEngine/") {}

void BaseGame::init(int argc, const char* const* argv, unsigned int width, unsigned int height)
{
#pragma region BGFX
	Args args(argc, argv);
	bgfx::Init init;
	init.type = args.m_type;
	init.vendorId = args.m_pciId;
	init.resolution.width = m_Width = width;
	init.resolution.height = m_Height = height;
	init.resolution.reset = m_Reset = BGFX_RESET_VSYNC;
	bgfx::init(init);

// #ifndef NDEBUG // Debug mode
	bgfx::setDebug(m_Debug = BGFX_DEBUG_TEXT);
/*
#else
	bgfx::setDebug(m_Debug = BGFX_DEBUG_NONE);
#endif
*/

	bgfx::setViewClear(
		0, // ID
		BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH,
		0 // RGBA Colour
	);

	setWindowSize(entry::WindowHandle{ 0 }, m_Width, m_Height);
#pragma endregion

#pragma region Logger
	InitLogger();

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
#ifndef NDEBUG
	spdlog::info("{:>12}: {}", "Build", "Debug");
#endif
	spdlog::info("");
	spdlog::info("{:>12}: {}", "Log Folder", m_LogDirectory);
	spdlog::info("{:>12}: {}", "Launch Dir", std::filesystem::current_path().string());
	spdlog::error("Test error");
	spdlog::trace("Test tracing");
	spdlog::warn("Test warning");
	spdlog::debug("Test debug");

#if defined(AQUA_ENGINE_PLATFORM_MAC) || defined(AQUA_ENGINE_PLATFORM_LINUX)
	spdlog::info("DYLD_LIBRARY_PATH = {}", getenv("DYLD_LIBRARY_PATH"));
#endif
#pragma endregion
}

int BaseGame::shutdown()
{
	bgfx::shutdown();
	spdlog::shutdown();
	return 0;
}

bool BaseGame::update()
{
	if (entry::processEvents(m_Width, m_Height, m_Debug, m_Reset, &m_MouseState))
		return false;

	bgfx::setViewRect(0, 0, 0, (unsigned short)m_Width, (unsigned short)m_Height);
	bgfx::touch(0); // Dummy draw call to ensure view is cleared

// #ifndef NDEBUG // Debug mode
	bgfx::dbgTextClear();

	const int LeftTextColour = 1;
	const int RightTextColour = LeftTextColour + 8;
	bgfx::dbgTextPrintf(1, 1, 0, "\x1b[%i;mAqua Engine \x1b[%i;m%s", LeftTextColour, RightTextColour, AQUA_ENGINE_VERSION_STRING.c_str());
	bgfx::dbgTextPrintf(1, 2, 0, "\x1b[%i;m   Renderer \x1b[%i;m%s", LeftTextColour, RightTextColour, bgfx::getRendererName(bgfx::getRendererType()));

	const bgfx::Stats* stats = bgfx::getStats();
	bgfx::dbgTextPrintf(1, 3, 0, "\x1b[%i;m Resolution \x1b[%i;m%ix%i", LeftTextColour, RightTextColour, stats->width, stats->height);
	bgfx::dbgTextPrintf(1, 4, 0, "\x1b[%i;m VRAM Usage \x1b[%i;m%.1fGB / %.1fGB", LeftTextColour, RightTextColour, BytesToGB(stats->gpuMemoryUsed), BytesToGB(stats->gpuMemoryMax));
// #endif

	bgfx::frame();
	return true;
}

void BaseGame::InitLogger()
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
	m_LogDirectory = string(appdata) + "/Aqua Engine/" + m_LogDirectory;
#elif defined(AQUA_ENGINE_PLATFORM_MAC)
	m_LogDirectory = string(getenv("HOME")) + "/Library/Caches/Aqua Engine/" + m_LogDirectory;
#elif defined(AQUA_ENGINE_PLATFORM_LINUX)
	m_LogDirectory = "./Logs/";
#endif

	auto fileSink = make_shared<spdlog::sinks::basic_file_sink_mt>(m_LogDirectory + "Engine.txt", true);
	fileSink->set_pattern("[%H:%M:%S %z][%t][%=8n][%7l] %v");
	fileSink->set_level(spdlog::level::trace);

	auto logger = make_shared<spdlog::logger>(spdlog::logger("Engine", { consoleSink, fileSink }));
	logger->set_level(spdlog::level::trace);
	spdlog::set_default_logger(logger);
}

int _main_(int _argc, char** _argv)
{
	BaseGame app;
	return entry::runApp(&app, _argc, _argv);
}