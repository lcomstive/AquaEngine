# Installation
## Download the editor

## Building from source
Clone the GitHub repo from `git clone --recursive https://github.com/lcomstive/AquaEngine.git`

## Test

```cpp
#include <stdlib.h> 
#include <iostream>
#include <filesystem>
#include <spdlog/spdlog.h>
#include <AquaEngine/API.hpp>

using namespace std;

int main()
{
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

	cout << endl << endl << "Press ENTER to exit..." << endl;
	getchar();
    spdlog::shutdown();
	return 0;
}
```