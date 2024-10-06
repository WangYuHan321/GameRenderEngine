#pragma once
#ifdef VULKAN_API
#include "vulkan/vulkan.h"
#include "../Util/common.h"
#include <optional>
#include <set>

class RHIVulkan
{
public:

	RHIVulkan();
	~RHIVulkan();

	void InitWindow();
	void InitVulkan();
	void MainLoop();

private:

#ifdef NDEBUG
const bool enableValidationLayers = false;
#else
const bool enableValidationLayers = true;
#endif

const std::vector<const char*> validationLayers = {
	"VK_LAYER_LUNARG_standard_validation"
};

const std::vector<const char*> deviceExtensions = {
	VK_KHR_SWAPCHAIN_EXTENSION_NAME
};

private:
	VkInstance m_vkInstance;
	VkDevice m_vkDevice;
	VkDebugUtilsMessengerEXT m_debugMessenger;//Debug

	VkSemaphore m_vkImageAvailableSemaphore;
	VkSemaphore m_vkRenderFinishedSemaphore;
	VkFence m_vkInFlightFence;
	
	VkSwapchainKHR m_vkSwapChain;
	std::vector<VkImage> m_vkSwapChainImages;
	VkFormat m_vkSwapChainImageFormat;
	VkExtent2D m_vkSwapChainExtent;
	std::vector<VkImageView> m_vkSwapChainImageViews;
	std::vector<VkFramebuffer> m_vkSwapChainFrameBuffers;

	VkRenderPass m_vkRenderPass;
	VkPipelineLayout m_vkPipeLineLayout;
	VkPipeline m_vkGraphicsPipeline;

	GLFWwindow* m_glfwWindow;
	VkSurfaceKHR m_surfaceWindow;
	VkPhysicalDevice m_physicalDevice = VK_NULL_HANDLE;

	VkQueue m_graphicsQueue;
	VkQueue m_presentQueue;

	std::vector<VkCommandBuffer> m_vkCommandBuffer;
	VkCommandPool m_vkCommandPool;

	uint32 m_windowWidth = 800;
	uint32 m_windowHeight = 600;

private:

	struct QueueFamilyIndices {
		std::optional<uint32_t> graphicsFamily;
		std::optional<uint32_t> presentFamily;

		bool isComplete() {
			return graphicsFamily.has_value() && presentFamily.has_value();
		}
	};

	struct SwapChainSupportDetails {
		VkSurfaceCapabilitiesKHR capabilities;
		std::vector<VkSurfaceFormatKHR> formats;
		std::vector<VkPresentModeKHR> presentModes;
	};


	std::vector<const char*> GetRequiredExtensions();
	void PopulateDebugMessagerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
	bool CheckValidationLayerSupport();
	SwapChainSupportDetails QuerySwapChainSupport(VkPhysicalDevice device);

	bool CheckDeviceExtensionSupport(VkPhysicalDevice device);
	
	QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device);
	bool IsDeviceSuitable(VkPhysicalDevice device);

	VkShaderModule CreateShaderModule(const std::vector<char>& code);

	VkPresentModeKHR ChooseSwapPresentMode(const std::vector<VkPresentModeKHR> availablePresentModes);
	VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
	VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
	
	void CreateInstance();
	void SetupDebugMessage();
	void CreateSurface();
	void PickPhysicalDevice();
	void CreateLogicalDevice();
	void CreateSwapChain();
	void CreateImageView();
	void CreateRenderPass();
	void CreateGraphicsPipeline();
	void CreateFrameBuffer();
	void CreateCommandPool();
	void CreateCommandBuffers();
	void CreateSyncObjects();
	void DrawFrame();
	void Cleanup();
};

#endif

