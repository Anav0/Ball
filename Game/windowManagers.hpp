#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <vector>
#include <cstring>
#include <cstdlib>
#include <stdexcept>

class GlfwWindowManager {

private:
	GLFWwindow* window;

public:
	bool isWindowOpen() {
		return !glfwWindowShouldClose(window);
	}

	void pullEvents() {
		glfwPollEvents();
	}

	void createSurface(VkInstance instance, VkSurfaceKHR* surface) {
		if (glfwCreateWindowSurface(instance, window, nullptr, surface) != VK_SUCCESS) {
			throw std::runtime_error("failed to create window surface!");
		}
	}

	void init(GLFWframebuffersizefun onResizeCallback) {
		glfwInit();

		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

		window = glfwCreateWindow(800, 600, "Vulkan", nullptr, nullptr);
		glfwSetWindowUserPointer(window, this);
		glfwSetFramebufferSizeCallback(window, onResizeCallback);
	}

	void getSize(int* width, int* height) {
		glfwGetFramebufferSize(window, width, height);
	}

	std::vector<const char*> getRequiredExtensions(bool enableValidationLayers) {
		uint32_t glfwExtensionCount = 0;
		const char** glfwExtensions;
		glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

		std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

		if (enableValidationLayers) {
			extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
		}

		return extensions;
	}

	void cleanup() {
		glfwDestroyWindow(window);
		glfwTerminate();
	}

};
