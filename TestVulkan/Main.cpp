#include "Main.hpp"
#include <memory>
/*
Vk::Instance inst;
Vk::SurfaceKhr surf;
Vk::PhysicalDevice phyDev;
Vk::Device dev;
Vk::Queue queue;
Vk::SwapchainKhr swapchain;

std::vector<Vk::Image> rts;
std::vector<Vk::ImageView> rtvs;

Vk::Fence fence;
Vk::Semaphore acquireSemaphore;
Vk::Semaphore renderSemaphore;

uint32_t currRtIndex;
uint32_t rtCount = 2;
uint32_t queueFamilyIndex;

VkSurfaceFormatKHR surfFormat;
VkSurfaceCapabilitiesKHR surfCapabilities;
VkPresentInfoKHR presentInfo;

Vk::CommandPool cmdPool;
std::vector<Vk::CommandBuffer> cmdBuffs(1);

struct MemoryIndex {
	uint32_t map;
	uint32_t device;
} memIndex;

bool initVulkan(HINSTANCE hInstance, HWND hWnd) {
	try {
		// Create Instance
		{
			uint32_t apiVer;
			Vk::enumerateInstanceVersion(&apiVer);

			VkApplicationInfo applicationInfo;
			{
				auto&& s = Vk::setSType(applicationInfo);
				s.pNext = nullptr;
				s.apiVersion = apiVer;
				s.pApplicationName = "Test Vulkan";
				s.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
				s.pEngineName = nullptr;
				s.engineVersion = 0;
			}

			const char *instExt[] = { "VK_KHR_surface", "VK_KHR_win32_surface" };
			const char *instLayer[] = { "VK_LAYER_LUNARG_object_tracker", "VK_LAYER_LUNARG_assistant_layer", "VK_LAYER_LUNARG_core_validation" };

			VkInstanceCreateInfo instanceCreateInfo;
			{
				auto&& s = Vk::setSType(instanceCreateInfo);
				s.pNext = nullptr;
				s.flags = 0;
				s.pApplicationInfo = &applicationInfo;
				s.enabledLayerCount = _countof(instLayer);
				s.ppEnabledLayerNames = instLayer;
				s.enabledExtensionCount = _countof(instExt);
				s.ppEnabledExtensionNames = instExt;
			}

			inst.createAndInit(&instanceCreateInfo);
		}

		// Create Surface
		{
			VkWin32SurfaceCreateInfoKHR win32SurfaceCreateInfoKHR;
			{
				auto&& s = Vk::setSType(win32SurfaceCreateInfoKHR);
				s.pNext = nullptr;
				s.flags = 0;
				s.hinstance = hInstance;
				s.hwnd = hWnd;
			}
			inst.createWin32Surface(&surf, &win32SurfaceCreateInfoKHR);
		}

		// Select PhysicalDevice
		{
			uint32_t phyDevCount;
			inst.enumeratePhysicalDevices(&phyDevCount);
			std::vector<VkPhysicalDevice> phyDevs(phyDevCount);
			inst.enumeratePhysicalDevices(&phyDevCount, phyDevs.data());

			bool isSuccess = false;
			for (uint32_t i = 0; i < phyDevCount; i++) {
				phyDev = phyDevs[0];
				VkPhysicalDeviceProperties prop;
				phyDev.getProperties(&prop);
				if (prop.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) {
					isSuccess = true;
					break;
				}
			}
			if (!isSuccess) return false;
		}

		// Retrieve Memory Info
		{
			VkPhysicalDeviceMemoryProperties memProp;
			phyDev.getMemoryProperties(&memProp);

			bool mapMem = true;
			bool devLocal = true;
			for (uint32_t i = 0; i < memProp.memoryTypeCount && (mapMem || devLocal); i++) {
				if (memProp.memoryTypes[i].propertyFlags & (VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT)) {
					memIndex.map = i;
					mapMem = false;
				}
				else if (memProp.memoryTypes[i].propertyFlags & VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT) {
					memIndex.device = i;
					devLocal = false;
				}
			}
		}

		// Retrieve QueueFamily Info
		{	
			uint32_t queueFamilyCount;
			phyDev.getQueueFamilyProperties(&queueFamilyCount);
			std::vector<VkQueueFamilyProperties> queueFamilyProperties(queueFamilyCount);
			phyDev.getQueueFamilyProperties(&queueFamilyCount, queueFamilyProperties.data());

			bool isSuccess = false;
			for (uint32_t i = 0; i < queueFamilyCount; i++) {
				VkBool32 supportSurface;
				phyDev.getSurfaceSupport(&supportSurface, i, surf);
				if (queueFamilyProperties[i].queueFlags & VK_QUEUE_GRAPHICS_BIT && supportSurface == VK_TRUE) {
					queueFamilyIndex = i;
					isSuccess = true;
					break; 
				}
			}
		}

		// Create Device
		{
			float queuePriorty[] = { 1.0f };

			VkDeviceQueueCreateInfo devQueueInfo[1];
			{
				auto&& s = VkFW::Vk::setSType(devQueueInfo[0]);
				s.pNext = nullptr;
				s.flags = 0;
				s.queueCount = _countof(queuePriorty);
				s.pQueuePriorities = queuePriorty;
				s.queueFamilyIndex = queueFamilyIndex;
			}

			const char *devExt[] = { "VK_KHR_swapchain" };

			VkDeviceCreateInfo deviceCreateInfo;
			{
				auto&& s = VkFW::Vk::setSType(deviceCreateInfo);
				s.pNext = nullptr;
				s.flags = 0;
				s.enabledLayerCount = 0;
				s.ppEnabledLayerNames = nullptr;
				s.enabledExtensionCount = _countof(devExt);
				s.ppEnabledExtensionNames = devExt;
				s.pEnabledFeatures = nullptr;
				s.queueCreateInfoCount = _countof(devQueueInfo);
				s.pQueueCreateInfos = devQueueInfo;
			}
			phyDev.createAndInitDevice(dev, &deviceCreateInfo);
		}
		
		// Retrieve Queue
		{
			dev.getQueue(&queue, queueFamilyIndex, 0);
		}

		// Retrieve Surface info
		{
			phyDev.getSurfaceCapabilities(&surfCapabilities, surf);

			uint32_t surfaceFormatCount;
			phyDev.getSurfaceFormats(surf, &surfaceFormatCount);
			std::vector<VkSurfaceFormatKHR> surfaceFormats(surfaceFormatCount);
			phyDev.getSurfaceFormats(surf, &surfaceFormatCount, surfaceFormats.data());
			surfFormat = surfaceFormats[0];
		}

		// Create Swapchain
		{
			VkSwapchainCreateInfoKHR swapchainCreateInfoKHR;
			{
				auto&& s = Vk::setSType(swapchainCreateInfoKHR);
				s.pNext = nullptr;
				s.flags = 0;
				s.surface = surf;
				s.clipped = VK_TRUE;
				s.minImageCount = rtCount;
				s.imageFormat = surfFormat.format;
				s.imageColorSpace = surfFormat.colorSpace;
				s.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT;
				s.imageExtent = surfCapabilities.currentExtent;
				s.imageArrayLayers = 1;
				s.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
				s.presentMode = VK_PRESENT_MODE_FIFO_KHR;
				s.preTransform = surfCapabilities.currentTransform;
				s.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
				s.queueFamilyIndexCount = 0;
				s.pQueueFamilyIndices = nullptr;
				s.oldSwapchain = VK_NULL_HANDLE;
			}

			dev.createSwapchain(&swapchain, &swapchainCreateInfoKHR);
		}

		{
			rts.resize(rtCount);
			rtvs.resize(rtCount);
			swapchain.getImages(&rtCount, &rts[0]);

			VkImageViewCreateInfo imgViewInfo;
			{
				auto&& s = VkFW::Vk::setSType(imgViewInfo);
				s.pNext = nullptr;
				s.flags = 0;
				s.viewType = VK_IMAGE_VIEW_TYPE_2D;
				s.format = VK_FORMAT_B8G8R8A8_UNORM;
				
				s.components.a = VK_COMPONENT_SWIZZLE_A;
				s.components.b = VK_COMPONENT_SWIZZLE_B;
				s.components.g = VK_COMPONENT_SWIZZLE_G;
				s.components.r = VK_COMPONENT_SWIZZLE_R;

				s.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
				s.subresourceRange.levelCount = 1;
				s.subresourceRange.baseMipLevel = 0;
				s.subresourceRange.layerCount = 1;
				s.subresourceRange.baseArrayLayer = 0;

				for (uint32_t i = 0; i < rtCount; i++) {
					s.image = rts[i];
					dev.createImageView(&rtvs[i], &imgViewInfo);
				}
			}
		}

		// Create Semaphore
		{
			VkSemaphoreCreateInfo semaphoreInfo;
			{
				auto&& s = VkFW::Vk::setSType(semaphoreInfo);
				s.pNext = nullptr;
				s.flags = 0;
			}

			dev.createSemaphore(&acquireSemaphore, &semaphoreInfo);
			dev.createSemaphore(&renderSemaphore, &semaphoreInfo);
		}

		// Set PresentInfo
		{
			auto&& s = VkFW::Vk::setSType(presentInfo);
			s.pNext = nullptr;
			s.waitSemaphoreCount = 1;
			s.pWaitSemaphores = &renderSemaphore;
			s.swapchainCount = 1;
			s.pSwapchains = &swapchain;
			s.pImageIndices = &currRtIndex;
			s.pResults = nullptr;
		}

		VkImageCreateInfo imgInfo;
		{
			auto&& s = Vk::setSType(imgInfo);
			s.pNext = nullptr;
			s.flags = 0;
			s.arrayLayers = 1;					
			s.extent.width = 10;
			s.extent.height = 10;
			s.extent.depth = 10;					
			s.format = VK_FORMAT_R8G8B8A8_UNORM;
			s.imageType = VK_IMAGE_TYPE_3D;		
			s.usage = VK_IMAGE_USAGE_SAMPLED_BIT;
			s.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
			s.tiling = VK_IMAGE_TILING_LINEAR;	
			s.mipLevels = 1;					
			s.samples = VK_SAMPLE_COUNT_1_BIT;	
			s.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
			s.pQueueFamilyIndices = nullptr;
			s.queueFamilyIndexCount = 0;
		}

		Vk::Image texture;
		dev.createImage(&texture, &imgInfo);

		VkMemoryRequirements memReq;
		texture.getMemoryRequirements(&memReq);

		MessageBoxA(nullptr, std::to_string(memReq.size).c_str(), "", 0);

		
		return true;
	}
	catch (const char *str) {
		MessageBoxA(nullptr, str, "Error : VkResult", 0);
		return false;
	}
}

bool startVulkan() {
	try {
		// Create CommandPool
		{
			VkCommandPoolCreateInfo cmdPoolInfo;
			{
				auto&& s = VkFW::Vk::setSType(cmdPoolInfo);
				s.pNext = nullptr;
				s.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
				s.queueFamilyIndex = queueFamilyIndex;
			}

			dev.createCommandPool(&cmdPool, &cmdPoolInfo);
		}

		// Allocate CommandBuffer
		{
			VkCommandBufferAllocateInfo cmdBuffAllcInfo;
			{
				auto&& s = Vk::setSType(cmdBuffAllcInfo);
				s.pNext = nullptr;
				s.commandPool = cmdPool;
				s.commandBufferCount = 1;
				s.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
			}

			dev.allocateCommandBuffers(&cmdBuffs[0], &cmdBuffAllcInfo);
		}

		// Create Fence
		{
			VkFenceCreateInfo fenceInfo;
			{
				auto&& s = Vk::setSType(fenceInfo);
				s.pNext = nullptr;
				s.flags = 0;
			}

			dev.createFence(&fence, &fenceInfo);
		}

		VkCommandBufferBeginInfo commandBufferBeginInfo;
		{
			auto&& s = Vk::setSType(commandBufferBeginInfo);
			s.pNext = nullptr;
			s.flags = 0;
			s.pInheritanceInfo = nullptr;
		}
		cmdBuffs[0].begin(&commandBufferBeginInfo);

		VkClearColorValue clearColor;
		clearColor.float32[0] = 1;
		clearColor.float32[1] = 0;
		clearColor.float32[2] = 0;
		clearColor.float32[3] = 1;

		VkImageSubresourceRange range;
		range.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		range.baseArrayLayer = 0;
		range.baseMipLevel = 0;
		range.layerCount = 1;
		range.levelCount = 1;

		VkImageMemoryBarrier imgBarrier;
		{
			auto&& s = Vk::setSType(imgBarrier);
			s.pNext = nullptr;
			s.image = rts[currRtIndex];
			s.oldLayout = VK_IMAGE_LAYOUT_UNDEFINED;
			s.newLayout = VK_IMAGE_LAYOUT_GENERAL;
			s.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
			s.subresourceRange.baseArrayLayer = 0;
			s.subresourceRange.baseMipLevel = 0;
			s.subresourceRange.layerCount = 1;
			s.subresourceRange.levelCount = 1;
			s.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
			s.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
			s.srcAccessMask = 0;
			s.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
		}

		cmdBuffs[0].cmdPipelineBarrier(VK_PIPELINE_STAGE_ALL_GRAPHICS_BIT, VK_PIPELINE_STAGE_ALL_GRAPHICS_BIT, 0,
			0, nullptr,
			0, nullptr,
			1, &imgBarrier);

		cmdBuffs[0].cmdClearColorImage(rts[currRtIndex], VK_IMAGE_LAYOUT_GENERAL, &clearColor, 1, &range);

		{
			auto&& s = imgBarrier;
			s.oldLayout = VK_IMAGE_LAYOUT_GENERAL;
			s.newLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
			s.srcAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
			s.dstAccessMask = 0;
		}

		cmdBuffs[0].cmdPipelineBarrier(VK_PIPELINE_STAGE_ALL_GRAPHICS_BIT, VK_PIPELINE_STAGE_ALL_GRAPHICS_BIT, 0,
			0, nullptr,
			0, nullptr,
			1, &imgBarrier);

		cmdBuffs[0].end();
		

		VkPipelineStageFlags pipelineStage = VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT;

		swapchain.acquireNextImageWithSemaphore(&currRtIndex, acquireSemaphore);

		VkSubmitInfo submitInfo[1];
		{
			auto&& s = Vk::setSType(submitInfo[0]);
			s.pNext = nullptr;
			s.commandBufferCount = cmdBuffs.size();
			s.pCommandBuffers = &cmdBuffs[0];
			s.waitSemaphoreCount = 1;
			s.pWaitSemaphores = &acquireSemaphore;
			s.pWaitDstStageMask = &pipelineStage;
			s.signalSemaphoreCount = 1;
			s.pSignalSemaphores = &renderSemaphore;
		}

		queue.submit(_countof(submitInfo), submitInfo, fence);

		presentInfo.waitSemaphoreCount = 1;
		presentInfo.pWaitSemaphores = &renderSemaphore;
		presentInfo.pImageIndices = &currRtIndex;

		queue.present(&presentInfo);
		return true;
	}
	catch (const char *str) {
		MessageBoxA(nullptr, str, "Error : VkResult", 0);
		return false;
	}
}
*/

Vk::Instance inst;
Vk::PhysicalDevice phyDev;

struct VkFunc {
	Vk::FnType<decltype(vkDestroyInstance)>::Eval vkDestroyInstance;
	Vk::FnType<decltype(vkEnumeratePhysicalDevices)>::Eval vkEnumeratePhysicalDevices;
	Vk::FnType<decltype(vkGetPhysicalDeviceProperties)>::Eval vkGetPhysicalDeviceProperties;
} vkFunc;

bool initVulkan(HINSTANCE hInstance, HWND hWnd) {
	uint32_t apiVer;
	Vk::EnumerateInstanceVersion(&apiVer);

	VkApplicationInfo applicationInfo;
	{
		auto&& s = Vk::SType(applicationInfo);
		s.pNext = nullptr;
		s.apiVersion = apiVer;
		s.pApplicationName = "Test Vulkan";
		s.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
		s.pEngineName = nullptr;
		s.engineVersion = 0;
	}

	const char *instExt[] = { "VK_KHR_surface", "VK_KHR_win32_surface" };
	const char *instLayer[] = { "VK_LAYER_LUNARG_object_tracker", "VK_LAYER_LUNARG_assistant_layer", "VK_LAYER_LUNARG_core_validation" };

	VkInstanceCreateInfo instanceCreateInfo;
	{
		auto&& s = Vk::SType(instanceCreateInfo);
		s.pNext = nullptr;
		s.flags = 0;
		s.pApplicationInfo = &applicationInfo;
		s.enabledLayerCount = _countof(instLayer);
		s.ppEnabledLayerNames = instLayer;
		s.enabledExtensionCount = _countof(instExt);
		s.ppEnabledExtensionNames = instExt;
	}

	VKFW_DEBUG(&applicationInfo);
	VKFW_DEBUG(Vk::CreateInstance(&instanceCreateInfo, &inst));

	Vk::GetInstanceProcAddrs(inst, &vkFunc);

	uint32_t count;
	VKFW_DEBUG(inst.enumeratePhysicalDevices(&vkFunc, &count));
	std::vector<VkPhysicalDevice> phyDevs(count);
	VKFW_DEBUG(inst.enumeratePhysicalDevices(&vkFunc, &count, phyDevs.data()));

	phyDev = phyDevs[0];

	VkPhysicalDeviceProperties prop;
	phyDev.getProperties(&vkFunc, &prop);
	MessageBoxA(nullptr, prop.deviceName, "Device name", 0);

	return true;
}

void destroyVulkan() {
	inst.destroy(&vkFunc);
}

int main(HINSTANCE hInstance, char *lpCmdLine, int nCmdShow) {
	window = Window::New(WindowConfig::New(WinClass::New(WinClassConfig::New(L"Class1", WndProc)), WINDOW_WIDTH, WINDOW_HEIGHT));
	initVulkan(hInstance, window->get());
	window->show();
	//startVulkan();

	keyboard = Keyboard::New();
	mouse = Mouse::New();
	Mouse::useRawInputMouse();

	EventLoop::init();

	while (EventLoop::isActive()) {
		if (EventLoop::fps(60)) {
			
		}
	}

	destroyVulkan();
	return 0; 
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
	case WM_INPUT:
		mouse->updateRawMouseMove(lParam);
		break;
	case WM_DESTROY:
		EventLoop::destroy();
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}