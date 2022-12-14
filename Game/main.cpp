#include <iostream>
#include <fstream>
#include <stdexcept>
#include <algorithm>
#include <chrono>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdint>
#include <limits>
#include <array>
#include <optional>
#include <set>

#include "vulkan.cpp"
#include "windowManagers.cpp"

class Basic3dProgram {
public:
	GlfwWindowManager windowManager{};
	Vulkan vulkan;

	void run() {
		windowManager.init(1024, 720, "Ball", vulkan.resizeCallback);
		vulkan.createInstance(&windowManager);
		windowManager.createSurface(vulkan.instance, &vulkan.surface);
		vulkan.init();

		//vulkan.drawRect(0.5f, 0.5f, 10, 10);

		while (windowManager.isWindowOpen()) {
			windowManager.pullEvents();
			vulkan.drawFrame();
		}

		vulkan.cleanup();
		windowManager.cleanup();
	}
};


int main() {
	Basic3dProgram app{};

	try {
		app.run();
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
