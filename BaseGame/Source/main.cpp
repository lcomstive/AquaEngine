#include <spdlog/spdlog.h>
#include <AquaEngine/API.hpp>

int main()
{
	spdlog::info("Loading game...");

    spdlog::info(" - {:>8}: {1}", "Engine", AQUA_ENGINE_VERSION_LONG);
    spdlog::info(" - {:>8}: {1}", "Platform", AquaEngine::PlatformName);
    spdlog::info(" - {:>8}: v{}.{}.{}", "SPDLog", SPDLOG_VER_MAJOR, SPDLOG_VER_MINOR, SPDLOG_VER_PATCH);

	return 0;
}
