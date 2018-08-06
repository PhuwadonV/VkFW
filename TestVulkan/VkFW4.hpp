#pragma once

#ifdef VKFW_KHR_surface
#if defined(VKFW_KHR_win32_surface) || defined(_WIN32) || defined(_WIN64)
#pragma push_macro("WIN32_LEAN_AND_MEAN")
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#pragma push_macro("VK_USE_PLATFORM_WIN32_KHR")
#define VK_USE_PLATFORM_WIN32_KHR
#endif
#endif

#include <vulkan\vulkan.h>

#ifdef VKFW_DEBUG
#pragma push_macro("VKFW_DEBUG_VKRESULT")
#define VKFW_DEBUG_VKRESULT(result) Hidden::vkResultAssert(result);
#else
#define VKFW_DEBUG_VKRESULT(result) result
#endif

#pragma push_macro("VKFW_SET_STYPE")
#define VKFW_SET_STYPE(Type, val)				\
	inline Type& setSType(Type &ref) {			\
		ref.sType =  VK_STRUCTURE_TYPE_##val;	\
		return ref;								\
	}

#pragma push_macro("VKFW_HANDLE")
#define VKFW_HANDLE(Class, HandleType, varName)				\
public:														\
	inline HandleType* operator&() {						\
		return &varName;									\
	}														\
															\
	inline operator HandleType&() {							\
		return varName;										\
	}														\
															\
	inline operator const HandleType&() const {				\
		return varName;										\
	}

#pragma push_macro("VKFW_HANDLE_PARENT")
#define VKFW_HANDLE_PARENT(Class, HandleType, varName)	\
public:													\
	inline Class() = default;							\
	inline Class(HandleType handle) {					\
		varName = handle;								\
	}													\
														\
	inline Class(const Class &rhs) {}					\
	inline Class(Class &&rhs) {}						\
														\
	inline Class& operator=(const Class &rhs) {			\
		return operator=(varName);						\
	}													\
														\
	inline Class& operator=(Class &&rhs) {				\
		return operator=(rhs);							\
	}													\
														\
	inline Class& operator=(HandleType rhs) {			\
		varName = rhs;									\
		return *this;									\
	}													\
														\
	VKFW_HANDLE(Class, HandleType, varName)

#pragma push_macro("VKFW_HANDLE_CHILD")
#define VKFW_HANDLE_CHILD(Class, HandleType, varName)			\
private:														\
	HandleType varName;											\
public:															\
	inline Class() = default;									\
	inline Class(HandleType handle) : varName(handle) {}		\
	inline Class(const Class &rhs) : varName(rhs.varName) {}	\
	inline Class(Class &&rhs) : Class(rhs) {}					\
																\
	inline Class& operator=(const Class &rhs) {					\
		return operator=(rhs.varName);							\
	}															\
																\
	inline Class& operator=(Class &&rhs) {						\
		return operator=(rhs);									\
	}															\
																\
	inline Class& operator=(HandleType rhs) {					\
		varName = rhs;											\
		return *this;											\
	}															\
																\
	VKFW_HANDLE(Class, HandleType, varName)

namespace VkFW::Vk {
	VKFW_SET_STYPE(VkApplicationInfo, APPLICATION_INFO)
		VKFW_SET_STYPE(VkInstanceCreateInfo, INSTANCE_CREATE_INFO)
		VKFW_SET_STYPE(VkDeviceQueueCreateInfo, DEVICE_QUEUE_CREATE_INFO)
		VKFW_SET_STYPE(VkDeviceCreateInfo, DEVICE_CREATE_INFO)
		VKFW_SET_STYPE(VkSubmitInfo, SUBMIT_INFO)
		VKFW_SET_STYPE(VkMemoryAllocateInfo, MEMORY_ALLOCATE_INFO)
		VKFW_SET_STYPE(VkMappedMemoryRange, MAPPED_MEMORY_RANGE)
		VKFW_SET_STYPE(VkBindSparseInfo, BIND_SPARSE_INFO)
		VKFW_SET_STYPE(VkFenceCreateInfo, FENCE_CREATE_INFO)
		VKFW_SET_STYPE(VkSemaphoreCreateInfo, SEMAPHORE_CREATE_INFO)
		VKFW_SET_STYPE(VkEventCreateInfo, EVENT_CREATE_INFO)
		VKFW_SET_STYPE(VkQueryPoolCreateInfo, QUERY_POOL_CREATE_INFO)
		VKFW_SET_STYPE(VkBufferCreateInfo, BUFFER_CREATE_INFO)
		VKFW_SET_STYPE(VkBufferViewCreateInfo, BUFFER_VIEW_CREATE_INFO)
		VKFW_SET_STYPE(VkImageCreateInfo, IMAGE_CREATE_INFO)
		VKFW_SET_STYPE(VkImageViewCreateInfo, IMAGE_VIEW_CREATE_INFO)
		VKFW_SET_STYPE(VkShaderModuleCreateInfo, SHADER_MODULE_CREATE_INFO)
		VKFW_SET_STYPE(VkPipelineCacheCreateInfo, PIPELINE_CACHE_CREATE_INFO)
		VKFW_SET_STYPE(VkPipelineShaderStageCreateInfo, PIPELINE_SHADER_STAGE_CREATE_INFO)
		VKFW_SET_STYPE(VkPipelineVertexInputStateCreateInfo, PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO)
		VKFW_SET_STYPE(VkPipelineInputAssemblyStateCreateInfo, PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO)
		VKFW_SET_STYPE(VkPipelineTessellationStateCreateInfo, PIPELINE_TESSELLATION_STATE_CREATE_INFO)
		VKFW_SET_STYPE(VkPipelineViewportStateCreateInfo, PIPELINE_VIEWPORT_STATE_CREATE_INFO)
		VKFW_SET_STYPE(VkPipelineRasterizationStateCreateInfo, PIPELINE_RASTERIZATION_STATE_CREATE_INFO)
		VKFW_SET_STYPE(VkPipelineMultisampleStateCreateInfo, PIPELINE_MULTISAMPLE_STATE_CREATE_INFO)
		VKFW_SET_STYPE(VkPipelineDepthStencilStateCreateInfo, PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO)
		VKFW_SET_STYPE(VkPipelineColorBlendStateCreateInfo, PIPELINE_COLOR_BLEND_STATE_CREATE_INFO)
		VKFW_SET_STYPE(VkPipelineDynamicStateCreateInfo, PIPELINE_DYNAMIC_STATE_CREATE_INFO)
		VKFW_SET_STYPE(VkGraphicsPipelineCreateInfo, GRAPHICS_PIPELINE_CREATE_INFO)
		VKFW_SET_STYPE(VkComputePipelineCreateInfo, COMPUTE_PIPELINE_CREATE_INFO)
		VKFW_SET_STYPE(VkPipelineLayoutCreateInfo, PIPELINE_LAYOUT_CREATE_INFO)
		VKFW_SET_STYPE(VkSamplerCreateInfo, SAMPLER_CREATE_INFO)
		VKFW_SET_STYPE(VkDescriptorSetLayoutCreateInfo, DESCRIPTOR_SET_LAYOUT_CREATE_INFO)
		VKFW_SET_STYPE(VkDescriptorPoolCreateInfo, DESCRIPTOR_POOL_CREATE_INFO)
		VKFW_SET_STYPE(VkDescriptorSetAllocateInfo, DESCRIPTOR_SET_ALLOCATE_INFO)
		VKFW_SET_STYPE(VkWriteDescriptorSet, WRITE_DESCRIPTOR_SET)
		VKFW_SET_STYPE(VkCopyDescriptorSet, COPY_DESCRIPTOR_SET)
		VKFW_SET_STYPE(VkFramebufferCreateInfo, FRAMEBUFFER_CREATE_INFO)
		VKFW_SET_STYPE(VkRenderPassCreateInfo, RENDER_PASS_CREATE_INFO)
		VKFW_SET_STYPE(VkCommandPoolCreateInfo, COMMAND_POOL_CREATE_INFO)
		VKFW_SET_STYPE(VkCommandBufferAllocateInfo, COMMAND_BUFFER_ALLOCATE_INFO)
		VKFW_SET_STYPE(VkCommandBufferInheritanceInfo, COMMAND_BUFFER_INHERITANCE_INFO)
		VKFW_SET_STYPE(VkCommandBufferBeginInfo, COMMAND_BUFFER_BEGIN_INFO)
		VKFW_SET_STYPE(VkRenderPassBeginInfo, RENDER_PASS_BEGIN_INFO)
		VKFW_SET_STYPE(VkBufferMemoryBarrier, BUFFER_MEMORY_BARRIER)
		VKFW_SET_STYPE(VkImageMemoryBarrier, IMAGE_MEMORY_BARRIER)
		VKFW_SET_STYPE(VkMemoryBarrier, MEMORY_BARRIER)

#ifdef VKFW_KHR_surface
#ifdef VKFW_KHR_swapchain
		VKFW_SET_STYPE(VkSwapchainCreateInfoKHR, SWAPCHAIN_CREATE_INFO_KHR)
		VKFW_SET_STYPE(VkPresentInfoKHR, PRESENT_INFO_KHR)
#endif

#if defined(VKFW_KHR_win32_surface) || defined(_WIN32) || defined(_WIN64)
		VKFW_SET_STYPE(VkWin32SurfaceCreateInfoKHR, WIN32_SURFACE_CREATE_INFO_KHR)
#endif
#endif

	namespace Hidden {
		template<typename Type>
		class Evalable {
		public:
			using Eval = Type;
		};

		VkResult vkResultAssert(VkResult result) {
			switch (result) {
			case -1: throw "VK_ERROR_OUT_OF_HOST_MEMORY";
			case -2: throw "VK_ERROR_OUT_OF_DEVICE_MEMORY";
			case -3: throw "VK_ERROR_INITIALIZATION_FAILED";
			case -4: throw "VK_ERROR_DEVICE_LOST";
			case -5: throw "VK_ERROR_MEMORY_MAP_FAILED";
			case -6: throw "VK_ERROR_LAYER_NOT_PRESENT";
			case -7: throw "VK_ERROR_EXTENSION_NOT_PRESENT";
			case -8: throw "VK_ERROR_FEATURE_NOT_PRESENT";
			case -9: throw "VK_ERROR_INCOMPATIBLE_DRIVER";
			case -10: throw "VK_ERROR_TOO_MANY_OBJECTS";
			case -11: throw "VK_ERROR_FORMAT_NOT_SUPPORTED";
			case -12: throw "VK_ERROR_FRAGMENTED_POOL";
			case -1000069000: throw "VK_ERROR_OUT_OF_POOL_MEMORY";
			case -1000072003: throw "VK_ERROR_INVALID_EXTERNAL_HANDLE";
			case -1000000000: throw "VK_ERROR_SURFACE_LOST_KHR";
			case -1000000001: throw "VK_ERROR_NATIVE_WINDOW_IN_USE_KHR";
			case -1000001003: throw "VK_SUBOPTIMAL_KHR";
			case -1000001004: throw "VK_ERROR_OUT_OF_DATE_KHR";
			case -1000003001: throw "VK_ERROR_INCOMPATIBLE_DISPLAY_KHR";
			default: if(result < 0) throw "Unknowm Error";
			}
			return result;
		}
	}

	template<typename>
	class FnType;

	template<typename Return, typename... Args>
	class FnType<Return(VKAPI_PTR)(Args...)> : public Hidden::Evalable<Return(VKAPI_PTR*)(Args...)> {};

	template<typename Return, typename... Args>
	inline void getInstanceProcAddr(VkInstance instance, const char *pName, Return(VKAPI_PTR*&f)(Args...)) {
		f = reinterpret_cast<Return(VKAPI_PTR*)(Args...)>(vkGetInstanceProcAddr(instance, pName));
	}

	template<typename Return, typename... Args>
	inline void getInstanceProcAddr(const char *pName, Return(VKAPI_PTR*&f)(Args...)) {
		getInstanceProcAddr(VK_NULL_HANDLE, pName, f);
	}

	template<typename Return, typename... Args>
	inline void getDeviceProcAddr(VkDevice device, const char *pName, Return(VKAPI_PTR*&f)(Args...)) {
		f = reinterpret_cast<Return(VKAPI_PTR*)(Args...)>(vkGetDeviceProcAddr(device, pName));
	}

	inline VkResult createInstance(VkInstance *pInstance, const VkInstanceCreateInfo *pCreateInfo, const VkAllocationCallbacks *pAllocator = nullptr) {
		return VKFW_DEBUG_VKRESULT(vkCreateInstance(pCreateInfo, pAllocator, pInstance));
	}

	inline VkResult enumerateInstanceExtensionProperties(const char *pLayerName, uint32_t *pPropertyCount, VkExtensionProperties *pProperties = nullptr) {
		return VKFW_DEBUG_VKRESULT(vkEnumerateInstanceExtensionProperties(pLayerName, pPropertyCount, pProperties));
	}

	inline VkResult enumerateInstanceLayerProperties(uint32_t *pPropertyCount, VkLayerProperties *pProperties = nullptr) {
		return VKFW_DEBUG_VKRESULT(vkEnumerateInstanceLayerProperties(pPropertyCount, pProperties));
	}

#if VKFW_V_MAJOR >= 1 && VKFW_V_MINOR >= 1
	inline VkResult enumerateInstanceVersion(uint32_t *pApiVersion) {
		return VKFW_DEBUG_VKRESULT(vkEnumerateInstanceVersion(pApiVersion));
	}
#endif

	namespace Hidden::PFN {
		VkInstance instance;
		VkDevice device;
	}

	namespace Hidden::PFN::Core {
		class Instance {
		public:
			inline static typename FnType<decltype(vkCreateDevice)>::Eval vkCreateDevice;
			inline static typename FnType<decltype(vkDestroyInstance)>::Eval vkDestroyInstance;
			inline static typename FnType<decltype(vkEnumerateDeviceExtensionProperties)>::Eval vkEnumerateDeviceExtensionProperties;
			inline static typename FnType<decltype(vkEnumerateDeviceLayerProperties)>::Eval vkEnumerateDeviceLayerProperties;
			inline static typename FnType<decltype(vkEnumeratePhysicalDevices)>::Eval vkEnumeratePhysicalDevices;
			inline static typename FnType<decltype(vkGetPhysicalDeviceFeatures)>::Eval vkGetPhysicalDeviceFeatures;
			inline static typename FnType<decltype(vkGetPhysicalDeviceFormatProperties)>::Eval vkGetPhysicalDeviceFormatProperties;
			inline static typename FnType<decltype(vkGetPhysicalDeviceImageFormatProperties)>::Eval vkGetPhysicalDeviceImageFormatProperties;
			inline static typename FnType<decltype(vkGetPhysicalDeviceMemoryProperties)>::Eval vkGetPhysicalDeviceMemoryProperties;
			inline static typename FnType<decltype(vkGetPhysicalDeviceProperties)>::Eval vkGetPhysicalDeviceProperties;
			inline static typename FnType<decltype(vkGetPhysicalDeviceQueueFamilyProperties)>::Eval vkGetPhysicalDeviceQueueFamilyProperties;
			inline static typename FnType<decltype(vkGetPhysicalDeviceSparseImageFormatProperties)>::Eval vkGetPhysicalDeviceSparseImageFormatProperties;

			inline static void init(VkInstance handle) {
				getInstanceProcAddr(handle, "vkCreateDevice", vkCreateDevice);
				getInstanceProcAddr(handle, "vkDestroyInstance", vkDestroyInstance);
				getInstanceProcAddr(handle, "vkEnumerateDeviceExtensionProperties", vkEnumerateDeviceExtensionProperties);
				getInstanceProcAddr(handle, "vkEnumerateDeviceLayerProperties", vkEnumerateDeviceLayerProperties);
				getInstanceProcAddr(handle, "vkEnumeratePhysicalDevices", vkEnumeratePhysicalDevices);
				getInstanceProcAddr(handle, "vkGetPhysicalDeviceFeatures", vkGetPhysicalDeviceFeatures);
				getInstanceProcAddr(handle, "vkGetPhysicalDeviceFormatProperties", vkGetPhysicalDeviceFormatProperties);
				getInstanceProcAddr(handle, "vkGetPhysicalDeviceImageFormatProperties", vkGetPhysicalDeviceImageFormatProperties);
				getInstanceProcAddr(handle, "vkGetPhysicalDeviceMemoryProperties", vkGetPhysicalDeviceMemoryProperties);
				getInstanceProcAddr(handle, "vkGetPhysicalDeviceProperties", vkGetPhysicalDeviceProperties);
				getInstanceProcAddr(handle, "vkGetPhysicalDeviceQueueFamilyProperties", vkGetPhysicalDeviceQueueFamilyProperties);
				getInstanceProcAddr(handle, "vkGetPhysicalDeviceSparseImageFormatProperties", vkGetPhysicalDeviceSparseImageFormatProperties);
			}
		};

		class Device {
		public:
			inline static typename FnType<decltype(vkAllocateCommandBuffers)>::Eval vkAllocateCommandBuffers;
			inline static typename FnType<decltype(vkAllocateDescriptorSets)>::Eval vkAllocateDescriptorSets;
			inline static typename FnType<decltype(vkAllocateMemory)>::Eval vkAllocateMemory;
			inline static typename FnType<decltype(vkBeginCommandBuffer)>::Eval vkBeginCommandBuffer;
			inline static typename FnType<decltype(vkBindBufferMemory)>::Eval vkBindBufferMemory;
			inline static typename FnType<decltype(vkBindImageMemory)>::Eval vkBindImageMemory;
			inline static typename FnType<decltype(vkCmdBeginQuery)>::Eval vkCmdBeginQuery;
			inline static typename FnType<decltype(vkCmdBeginRenderPass)>::Eval vkCmdBeginRenderPass;
			inline static typename FnType<decltype(vkCmdBindDescriptorSets)>::Eval vkCmdBindDescriptorSets;
			inline static typename FnType<decltype(vkCmdBindIndexBuffer)>::Eval vkCmdBindIndexBuffer;
			inline static typename FnType<decltype(vkCmdBindPipeline)>::Eval vkCmdBindPipeline;
			inline static typename FnType<decltype(vkCmdBindVertexBuffers)>::Eval vkCmdBindVertexBuffers;
			inline static typename FnType<decltype(vkCmdBlitImage)>::Eval vkCmdBlitImage;
			inline static typename FnType<decltype(vkCmdClearAttachments)>::Eval vkCmdClearAttachments;
			inline static typename FnType<decltype(vkCmdClearColorImage)>::Eval vkCmdClearColorImage;
			inline static typename FnType<decltype(vkCmdClearDepthStencilImage)>::Eval vkCmdClearDepthStencilImage;
			inline static typename FnType<decltype(vkCmdCopyBuffer)>::Eval vkCmdCopyBuffer;
			inline static typename FnType<decltype(vkCmdCopyBufferToImage)>::Eval vkCmdCopyBufferToImage;
			inline static typename FnType<decltype(vkCmdCopyImage)>::Eval vkCmdCopyImage;
			inline static typename FnType<decltype(vkCmdCopyImageToBuffer)>::Eval vkCmdCopyImageToBuffer;
			inline static typename FnType<decltype(vkCmdCopyQueryPoolResults)>::Eval vkCmdCopyQueryPoolResults;
			inline static typename FnType<decltype(vkCmdDispatch)>::Eval vkCmdDispatch;
			inline static typename FnType<decltype(vkCmdDispatchIndirect)>::Eval vkCmdDispatchIndirect;
			inline static typename FnType<decltype(vkCmdDraw)>::Eval vkCmdDraw;
			inline static typename FnType<decltype(vkCmdDrawIndexed)>::Eval vkCmdDrawIndexed;
			inline static typename FnType<decltype(vkCmdDrawIndexedIndirect)>::Eval vkCmdDrawIndexedIndirect;
			inline static typename FnType<decltype(vkCmdDrawIndirect)>::Eval vkCmdDrawIndirect;
			inline static typename FnType<decltype(vkCmdEndQuery)>::Eval vkCmdEndQuery;
			inline static typename FnType<decltype(vkCmdEndRenderPass)>::Eval vkCmdEndRenderPass;
			inline static typename FnType<decltype(vkCmdExecuteCommands)>::Eval vkCmdExecuteCommands;
			inline static typename FnType<decltype(vkCmdFillBuffer)>::Eval vkCmdFillBuffer;
			inline static typename FnType<decltype(vkCmdNextSubpass)>::Eval vkCmdNextSubpass;
			inline static typename FnType<decltype(vkCmdPipelineBarrier)>::Eval vkCmdPipelineBarrier;
			inline static typename FnType<decltype(vkCmdPushConstants)>::Eval vkCmdPushConstants;
			inline static typename FnType<decltype(vkCmdResetEvent)>::Eval vkCmdResetEvent;
			inline static typename FnType<decltype(vkCmdResetQueryPool)>::Eval vkCmdResetQueryPool;
			inline static typename FnType<decltype(vkCmdResolveImage)>::Eval vkCmdResolveImage;
			inline static typename FnType<decltype(vkCmdSetBlendConstants)>::Eval vkCmdSetBlendConstants;
			inline static typename FnType<decltype(vkCmdSetDepthBias)>::Eval vkCmdSetDepthBias;
			inline static typename FnType<decltype(vkCmdSetDepthBounds)>::Eval vkCmdSetDepthBounds;
			inline static typename FnType<decltype(vkCmdSetEvent)>::Eval vkCmdSetEvent;
			inline static typename FnType<decltype(vkCmdSetLineWidth)>::Eval vkCmdSetLineWidth;
			inline static typename FnType<decltype(vkCmdSetScissor)>::Eval vkCmdSetScissor;
			inline static typename FnType<decltype(vkCmdSetStencilCompareMask)>::Eval vkCmdSetStencilCompareMask;
			inline static typename FnType<decltype(vkCmdSetStencilReference)>::Eval vkCmdSetStencilReference;
			inline static typename FnType<decltype(vkCmdSetStencilWriteMask)>::Eval vkCmdSetStencilWriteMask;
			inline static typename FnType<decltype(vkCmdSetViewport)>::Eval vkCmdSetViewport;
			inline static typename FnType<decltype(vkCmdUpdateBuffer)>::Eval vkCmdUpdateBuffer;
			inline static typename FnType<decltype(vkCmdWaitEvents)>::Eval vkCmdWaitEvents;
			inline static typename FnType<decltype(vkCmdWriteTimestamp)>::Eval vkCmdWriteTimestamp;
			inline static typename FnType<decltype(vkCreateBuffer)>::Eval vkCreateBuffer;
			inline static typename FnType<decltype(vkCreateBufferView)>::Eval vkCreateBufferView;
			inline static typename FnType<decltype(vkCreateCommandPool)>::Eval vkCreateCommandPool;
			inline static typename FnType<decltype(vkCreateComputePipelines)>::Eval vkCreateComputePipelines;
			inline static typename FnType<decltype(vkCreateDescriptorPool)>::Eval vkCreateDescriptorPool;
			inline static typename FnType<decltype(vkCreateDescriptorSetLayout)>::Eval vkCreateDescriptorSetLayout;
			inline static typename FnType<decltype(vkCreateEvent)>::Eval vkCreateEvent;
			inline static typename FnType<decltype(vkCreateFence)>::Eval vkCreateFence;
			inline static typename FnType<decltype(vkCreateFramebuffer)>::Eval vkCreateFramebuffer;
			inline static typename FnType<decltype(vkCreateGraphicsPipelines)>::Eval vkCreateGraphicsPipelines;
			inline static typename FnType<decltype(vkCreateImage)>::Eval vkCreateImage;
			inline static typename FnType<decltype(vkCreateImageView)>::Eval vkCreateImageView;
			inline static typename FnType<decltype(vkCreatePipelineCache)>::Eval vkCreatePipelineCache;
			inline static typename FnType<decltype(vkCreatePipelineLayout)>::Eval vkCreatePipelineLayout;
			inline static typename FnType<decltype(vkCreateQueryPool)>::Eval vkCreateQueryPool;
			inline static typename FnType<decltype(vkCreateRenderPass)>::Eval vkCreateRenderPass;
			inline static typename FnType<decltype(vkCreateSampler)>::Eval vkCreateSampler;
			inline static typename FnType<decltype(vkCreateSemaphore)>::Eval vkCreateSemaphore;
			inline static typename FnType<decltype(vkCreateShaderModule)>::Eval vkCreateShaderModule;
			inline static typename FnType<decltype(vkDestroyBuffer)>::Eval vkDestroyBuffer;
			inline static typename FnType<decltype(vkDestroyBufferView)>::Eval vkDestroyBufferView;
			inline static typename FnType<decltype(vkDestroyCommandPool)>::Eval vkDestroyCommandPool;
			inline static typename FnType<decltype(vkDestroyDescriptorPool)>::Eval vkDestroyDescriptorPool;
			inline static typename FnType<decltype(vkDestroyDescriptorSetLayout)>::Eval vkDestroyDescriptorSetLayout;
			inline static typename FnType<decltype(vkDestroyDevice)>::Eval vkDestroyDevice;
			inline static typename FnType<decltype(vkDestroyEvent)>::Eval vkDestroyEvent;
			inline static typename FnType<decltype(vkDestroyFence)>::Eval vkDestroyFence;
			inline static typename FnType<decltype(vkDestroyFramebuffer)>::Eval vkDestroyFramebuffer;
			inline static typename FnType<decltype(vkDestroyImage)>::Eval vkDestroyImage;
			inline static typename FnType<decltype(vkDestroyImageView)>::Eval vkDestroyImageView;
			inline static typename FnType<decltype(vkDestroyPipeline)>::Eval vkDestroyPipeline;
			inline static typename FnType<decltype(vkDestroyPipelineCache)>::Eval vkDestroyPipelineCache;
			inline static typename FnType<decltype(vkDestroyPipelineLayout)>::Eval vkDestroyPipelineLayout;
			inline static typename FnType<decltype(vkDestroyQueryPool)>::Eval vkDestroyQueryPool;
			inline static typename FnType<decltype(vkDestroyRenderPass)>::Eval vkDestroyRenderPass;
			inline static typename FnType<decltype(vkDestroySampler)>::Eval vkDestroySampler;
			inline static typename FnType<decltype(vkDestroySemaphore)>::Eval vkDestroySemaphore;
			inline static typename FnType<decltype(vkDestroyShaderModule)>::Eval vkDestroyShaderModule;
			inline static typename FnType<decltype(vkDeviceWaitIdle)>::Eval vkDeviceWaitIdle;
			inline static typename FnType<decltype(vkEndCommandBuffer)>::Eval vkEndCommandBuffer;
			inline static typename FnType<decltype(vkFlushMappedMemoryRanges)>::Eval vkFlushMappedMemoryRanges;
			inline static typename FnType<decltype(vkFreeCommandBuffers)>::Eval vkFreeCommandBuffers;
			inline static typename FnType<decltype(vkFreeDescriptorSets)>::Eval vkFreeDescriptorSets;
			inline static typename FnType<decltype(vkFreeMemory)>::Eval vkFreeMemory;
			inline static typename FnType<decltype(vkGetBufferMemoryRequirements)>::Eval vkGetBufferMemoryRequirements;
			inline static typename FnType<decltype(vkGetDeviceMemoryCommitment)>::Eval vkGetDeviceMemoryCommitment;
			inline static typename FnType<decltype(vkGetDeviceQueue)>::Eval vkGetDeviceQueue;
			inline static typename FnType<decltype(vkGetEventStatus)>::Eval vkGetEventStatus;
			inline static typename FnType<decltype(vkGetFenceStatus)>::Eval vkGetFenceStatus;
			inline static typename FnType<decltype(vkGetImageMemoryRequirements)>::Eval vkGetImageMemoryRequirements;
			inline static typename FnType<decltype(vkGetImageSparseMemoryRequirements)>::Eval vkGetImageSparseMemoryRequirements;
			inline static typename FnType<decltype(vkGetImageSubresourceLayout)>::Eval vkGetImageSubresourceLayout;
			inline static typename FnType<decltype(vkGetPipelineCacheData)>::Eval vkGetPipelineCacheData;
			inline static typename FnType<decltype(vkGetQueryPoolResults)>::Eval vkGetQueryPoolResults;
			inline static typename FnType<decltype(vkGetRenderAreaGranularity)>::Eval vkGetRenderAreaGranularity;
			inline static typename FnType<decltype(vkInvalidateMappedMemoryRanges)>::Eval vkInvalidateMappedMemoryRanges;
			inline static typename FnType<decltype(vkMapMemory)>::Eval vkMapMemory;
			inline static typename FnType<decltype(vkMergePipelineCaches)>::Eval vkMergePipelineCaches;
			inline static typename FnType<decltype(vkQueueBindSparse)>::Eval vkQueueBindSparse;
			inline static typename FnType<decltype(vkQueueSubmit)>::Eval vkQueueSubmit;
			inline static typename FnType<decltype(vkQueueWaitIdle)>::Eval vkQueueWaitIdle;
			inline static typename FnType<decltype(vkResetCommandBuffer)>::Eval vkResetCommandBuffer;
			inline static typename FnType<decltype(vkResetCommandPool)>::Eval vkResetCommandPool;
			inline static typename FnType<decltype(vkResetDescriptorPool)>::Eval vkResetDescriptorPool;
			inline static typename FnType<decltype(vkResetEvent)>::Eval vkResetEvent;
			inline static typename FnType<decltype(vkResetFences)>::Eval vkResetFences;
			inline static typename FnType<decltype(vkSetEvent)>::Eval vkSetEvent;
			inline static typename FnType<decltype(vkUnmapMemory)>::Eval vkUnmapMemory;
			inline static typename FnType<decltype(vkUpdateDescriptorSets)>::Eval vkUpdateDescriptorSets;
			inline static typename FnType<decltype(vkWaitForFences)>::Eval vkWaitForFences;

			void static init(VkDevice handle) {
				getDeviceProcAddr(handle, "vkAllocateCommandBuffers", vkAllocateCommandBuffers);
				getDeviceProcAddr(handle, "vkAllocateDescriptorSets", vkAllocateDescriptorSets);
				getDeviceProcAddr(handle, "vkAllocateMemory", vkAllocateMemory);
				getDeviceProcAddr(handle, "vkBeginCommandBuffer", vkBeginCommandBuffer);
				getDeviceProcAddr(handle, "vkBindBufferMemory", vkBindBufferMemory);
				getDeviceProcAddr(handle, "vkBindImageMemory", vkBindImageMemory);
				getDeviceProcAddr(handle, "vkCmdBeginQuery", vkCmdBeginQuery);
				getDeviceProcAddr(handle, "vkCmdBeginRenderPass", vkCmdBeginRenderPass);
				getDeviceProcAddr(handle, "vkCmdBindDescriptorSets", vkCmdBindDescriptorSets);
				getDeviceProcAddr(handle, "vkCmdBindIndexBuffer", vkCmdBindIndexBuffer);
				getDeviceProcAddr(handle, "vkCmdBindPipeline", vkCmdBindPipeline);
				getDeviceProcAddr(handle, "vkCmdBindVertexBuffers", vkCmdBindVertexBuffers);
				getDeviceProcAddr(handle, "vkCmdBlitImage", vkCmdBlitImage);
				getDeviceProcAddr(handle, "vkCmdClearAttachments", vkCmdClearAttachments);
				getDeviceProcAddr(handle, "vkCmdClearColorImage", vkCmdClearColorImage);
				getDeviceProcAddr(handle, "vkCmdClearDepthStencilImage", vkCmdClearDepthStencilImage);
				getDeviceProcAddr(handle, "vkCmdCopyBuffer", vkCmdCopyBuffer);
				getDeviceProcAddr(handle, "vkCmdCopyBufferToImage", vkCmdCopyBufferToImage);
				getDeviceProcAddr(handle, "vkCmdCopyImage", vkCmdCopyImage);
				getDeviceProcAddr(handle, "vkCmdCopyImageToBuffer", vkCmdCopyImageToBuffer);
				getDeviceProcAddr(handle, "vkCmdCopyQueryPoolResults", vkCmdCopyQueryPoolResults);
				getDeviceProcAddr(handle, "vkCmdDispatch", vkCmdDispatch);
				getDeviceProcAddr(handle, "vkCmdDispatchIndirect", vkCmdDispatchIndirect);
				getDeviceProcAddr(handle, "vkCmdDraw", vkCmdDraw);
				getDeviceProcAddr(handle, "vkCmdDrawIndexed", vkCmdDrawIndexed);
				getDeviceProcAddr(handle, "vkCmdDrawIndexedIndirect", vkCmdDrawIndexedIndirect);
				getDeviceProcAddr(handle, "vkCmdDrawIndirect", vkCmdDrawIndirect);
				getDeviceProcAddr(handle, "vkCmdEndQuery", vkCmdEndQuery);
				getDeviceProcAddr(handle, "vkCmdEndRenderPass", vkCmdEndRenderPass);
				getDeviceProcAddr(handle, "vkCmdExecuteCommands", vkCmdExecuteCommands);
				getDeviceProcAddr(handle, "vkCmdFillBuffer", vkCmdFillBuffer);
				getDeviceProcAddr(handle, "vkCmdNextSubpass", vkCmdNextSubpass);
				getDeviceProcAddr(handle, "vkCmdPipelineBarrier", vkCmdPipelineBarrier);
				getDeviceProcAddr(handle, "vkCmdPushConstants", vkCmdPushConstants);
				getDeviceProcAddr(handle, "vkCmdResetEvent", vkCmdResetEvent);
				getDeviceProcAddr(handle, "vkCmdResetQueryPool", vkCmdResetQueryPool);
				getDeviceProcAddr(handle, "vkCmdResolveImage", vkCmdResolveImage);
				getDeviceProcAddr(handle, "vkCmdSetBlendConstants", vkCmdSetBlendConstants);
				getDeviceProcAddr(handle, "vkCmdSetDepthBias", vkCmdSetDepthBias);
				getDeviceProcAddr(handle, "vkCmdSetDepthBounds", vkCmdSetDepthBounds);
				getDeviceProcAddr(handle, "vkCmdSetEvent", vkCmdSetEvent);
				getDeviceProcAddr(handle, "vkCmdSetLineWidth", vkCmdSetLineWidth);
				getDeviceProcAddr(handle, "vkCmdSetScissor", vkCmdSetScissor);
				getDeviceProcAddr(handle, "vkCmdSetStencilCompareMask", vkCmdSetStencilCompareMask);
				getDeviceProcAddr(handle, "vkCmdSetStencilReference", vkCmdSetStencilReference);
				getDeviceProcAddr(handle, "vkCmdSetStencilWriteMask", vkCmdSetStencilWriteMask);
				getDeviceProcAddr(handle, "vkCmdSetViewport", vkCmdSetViewport);
				getDeviceProcAddr(handle, "vkCmdUpdateBuffer", vkCmdUpdateBuffer);
				getDeviceProcAddr(handle, "vkCmdWaitEvents", vkCmdWaitEvents);
				getDeviceProcAddr(handle, "vkCmdWriteTimestamp", vkCmdWriteTimestamp);
				getDeviceProcAddr(handle, "vkCreateBuffer", vkCreateBuffer);
				getDeviceProcAddr(handle, "vkCreateBufferView", vkCreateBufferView);
				getDeviceProcAddr(handle, "vkCreateCommandPool", vkCreateCommandPool);
				getDeviceProcAddr(handle, "vkCreateComputePipelines", vkCreateComputePipelines);
				getDeviceProcAddr(handle, "vkCreateDescriptorPool", vkCreateDescriptorPool);
				getDeviceProcAddr(handle, "vkCreateDescriptorSetLayout", vkCreateDescriptorSetLayout);
				getDeviceProcAddr(handle, "vkCreateEvent", vkCreateEvent);
				getDeviceProcAddr(handle, "vkCreateFence", vkCreateFence);
				getDeviceProcAddr(handle, "vkCreateFramebuffer", vkCreateFramebuffer);
				getDeviceProcAddr(handle, "vkCreateGraphicsPipelines", vkCreateGraphicsPipelines);
				getDeviceProcAddr(handle, "vkCreateImage", vkCreateImage);
				getDeviceProcAddr(handle, "vkCreateImageView", vkCreateImageView);
				getDeviceProcAddr(handle, "vkCreatePipelineCache", vkCreatePipelineCache);
				getDeviceProcAddr(handle, "vkCreatePipelineLayout", vkCreatePipelineLayout);
				getDeviceProcAddr(handle, "vkCreateQueryPool", vkCreateQueryPool);
				getDeviceProcAddr(handle, "vkCreateRenderPass", vkCreateRenderPass);
				getDeviceProcAddr(handle, "vkCreateSampler", vkCreateSampler);
				getDeviceProcAddr(handle, "vkCreateSemaphore", vkCreateSemaphore);
				getDeviceProcAddr(handle, "vkCreateShaderModule", vkCreateShaderModule);
				getDeviceProcAddr(handle, "vkDestroyBuffer", vkDestroyBuffer);
				getDeviceProcAddr(handle, "vkDestroyBufferView", vkDestroyBufferView);
				getDeviceProcAddr(handle, "vkDestroyCommandPool", vkDestroyCommandPool);
				getDeviceProcAddr(handle, "vkDestroyDescriptorPool", vkDestroyDescriptorPool);
				getDeviceProcAddr(handle, "vkDestroyDescriptorSetLayout", vkDestroyDescriptorSetLayout);
				getDeviceProcAddr(handle, "vkDestroyDevice", vkDestroyDevice);
				getDeviceProcAddr(handle, "vkDestroyEvent", vkDestroyEvent);
				getDeviceProcAddr(handle, "vkDestroyFence", vkDestroyFence);
				getDeviceProcAddr(handle, "vkDestroyFramebuffer", vkDestroyFramebuffer);
				getDeviceProcAddr(handle, "vkDestroyImage", vkDestroyImage);
				getDeviceProcAddr(handle, "vkDestroyImageView", vkDestroyImageView);
				getDeviceProcAddr(handle, "vkDestroyPipeline", vkDestroyPipeline);
				getDeviceProcAddr(handle, "vkDestroyPipelineCache", vkDestroyPipelineCache);
				getDeviceProcAddr(handle, "vkDestroyPipelineLayout", vkDestroyPipelineLayout);
				getDeviceProcAddr(handle, "vkDestroyQueryPool", vkDestroyQueryPool);
				getDeviceProcAddr(handle, "vkDestroyRenderPass", vkDestroyRenderPass);
				getDeviceProcAddr(handle, "vkDestroySampler", vkDestroySampler);
				getDeviceProcAddr(handle, "vkDestroySemaphore", vkDestroySemaphore);
				getDeviceProcAddr(handle, "vkDestroyShaderModule", vkDestroyShaderModule);
				getDeviceProcAddr(handle, "vkDeviceWaitIdle", vkDeviceWaitIdle);
				getDeviceProcAddr(handle, "vkEndCommandBuffer", vkEndCommandBuffer);
				getDeviceProcAddr(handle, "vkFlushMappedMemoryRanges", vkFlushMappedMemoryRanges);
				getDeviceProcAddr(handle, "vkFreeCommandBuffers", vkFreeCommandBuffers);
				getDeviceProcAddr(handle, "vkFreeDescriptorSets", vkFreeDescriptorSets);
				getDeviceProcAddr(handle, "vkFreeMemory", vkFreeMemory);
				getDeviceProcAddr(handle, "vkGetBufferMemoryRequirements", vkGetBufferMemoryRequirements);
				getDeviceProcAddr(handle, "vkGetDeviceMemoryCommitment", vkGetDeviceMemoryCommitment);
				getDeviceProcAddr(handle, "vkGetDeviceQueue", vkGetDeviceQueue);
				getDeviceProcAddr(handle, "vkGetEventStatus", vkGetEventStatus);
				getDeviceProcAddr(handle, "vkGetFenceStatus", vkGetFenceStatus);
				getDeviceProcAddr(handle, "vkGetImageMemoryRequirements", vkGetImageMemoryRequirements);
				getDeviceProcAddr(handle, "vkGetImageSparseMemoryRequirements", vkGetImageSparseMemoryRequirements);
				getDeviceProcAddr(handle, "vkGetImageSubresourceLayout", vkGetImageSubresourceLayout);
				getDeviceProcAddr(handle, "vkGetPipelineCacheData", vkGetPipelineCacheData);
				getDeviceProcAddr(handle, "vkGetQueryPoolResults", vkGetQueryPoolResults);
				getDeviceProcAddr(handle, "vkGetRenderAreaGranularity", vkGetRenderAreaGranularity);
				getDeviceProcAddr(handle, "vkInvalidateMappedMemoryRanges", vkInvalidateMappedMemoryRanges);
				getDeviceProcAddr(handle, "vkMapMemory", vkMapMemory);
				getDeviceProcAddr(handle, "vkMergePipelineCaches", vkMergePipelineCaches);
				getDeviceProcAddr(handle, "vkQueueBindSparse", vkQueueBindSparse);
				getDeviceProcAddr(handle, "vkQueueSubmit", vkQueueSubmit);
				getDeviceProcAddr(handle, "vkQueueWaitIdle", vkQueueWaitIdle);
				getDeviceProcAddr(handle, "vkResetCommandBuffer", vkResetCommandBuffer);
				getDeviceProcAddr(handle, "vkResetCommandPool", vkResetCommandPool);
				getDeviceProcAddr(handle, "vkResetDescriptorPool", vkResetDescriptorPool);
				getDeviceProcAddr(handle, "vkResetEvent", vkResetEvent);
				getDeviceProcAddr(handle, "vkResetFences", vkResetFences);
				getDeviceProcAddr(handle, "vkSetEvent", vkSetEvent);
				getDeviceProcAddr(handle, "vkUnmapMemory", vkUnmapMemory);
				getDeviceProcAddr(handle, "vkUpdateDescriptorSets", vkUpdateDescriptorSets);
				getDeviceProcAddr(handle, "vkWaitForFences", vkWaitForFences);
			}
		};
	}

#if VKFW_V_MAJOR >= 1 && VKFW_V_MINOR >= 1
	namespace Hidden::PFN::Core1_1 {
		class Instance {
		public:
			inline static typename FnType<decltype(vkEnumeratePhysicalDeviceGroups)>::Eval vkEnumeratePhysicalDeviceGroups;
			inline static typename FnType<decltype(vkGetPhysicalDeviceProperties2)>::Eval vkGetPhysicalDeviceProperties2;
			inline static typename FnType<decltype(vkGetPhysicalDeviceQueueFamilyProperties2)>::Eval vkGetPhysicalDeviceQueueFamilyProperties2;
			inline static typename FnType<decltype(vkGetPhysicalDeviceSparseImageFormatProperties2)>::Eval vkGetPhysicalDeviceSparseImageFormatProperties2;

			inline static void init(VkInstance handle) {
				getInstanceProcAddr(handle, "vkEnumeratePhysicalDeviceGroups", vkEnumeratePhysicalDeviceGroups);
				getInstanceProcAddr(handle, "vkGetPhysicalDeviceProperties2", vkGetPhysicalDeviceProperties2);
				getInstanceProcAddr(handle, "vkGetPhysicalDeviceQueueFamilyProperties2", vkGetPhysicalDeviceQueueFamilyProperties2);
				getInstanceProcAddr(handle, "vkGetPhysicalDeviceSparseImageFormatProperties2", vkGetPhysicalDeviceSparseImageFormatProperties2);
			}
		};

		class Device {
		public:
			inline static typename FnType<decltype(vkBindBufferMemory2)>::Eval vkBindBufferMemory2;
			inline static typename FnType<decltype(vkBindImageMemory2)>::Eval vkBindImageMemory2;
			inline static typename FnType<decltype(vkCreateDescriptorUpdateTemplate)>::Eval vkCreateDescriptorUpdateTemplate;
			inline static typename FnType<decltype(vkCreateSamplerYcbcrConversion)>::Eval vkCreateSamplerYcbcrConversion;
			inline static typename FnType<decltype(vkDestroyDescriptorUpdateTemplate)>::Eval vkDestroyDescriptorUpdateTemplate;
			inline static typename FnType<decltype(vkDestroySamplerYcbcrConversion)>::Eval vkDestroySamplerYcbcrConversion;
			inline static typename FnType<decltype(vkGetBufferMemoryRequirements2)>::Eval vkGetBufferMemoryRequirements2;
			inline static typename FnType<decltype(vkGetDescriptorSetLayoutSupport)>::Eval vkGetDescriptorSetLayoutSupport;
			inline static typename FnType<decltype(vkGetDeviceGroupPeerMemoryFeatures)>::Eval vkGetDeviceGroupPeerMemoryFeatures;
			inline static typename FnType<decltype(vkGetDeviceQueue2)>::Eval vkGetDeviceQueue2;
			inline static typename FnType<decltype(vkGetImageMemoryRequirements2)>::Eval vkGetImageMemoryRequirements2;
			inline static typename FnType<decltype(vkGetImageSparseMemoryRequirements2)>::Eval vkGetImageSparseMemoryRequirements2;
			inline static typename FnType<decltype(vkTrimCommandPool)>::Eval vkTrimCommandPool;
			inline static typename FnType<decltype(vkUpdateDescriptorSetWithTemplate)>::Eval vkUpdateDescriptorSetWithTemplate;

			
			void static init(VkDevice handle) {
				getDeviceProcAddr(handle, "vkBindBufferMemory2", vkBindBufferMemory2);
				getDeviceProcAddr(handle, "vkBindImageMemory2", vkBindImageMemory2);
				getDeviceProcAddr(handle, "vkCreateDescriptorUpdateTemplate", vkCreateDescriptorUpdateTemplate);
				getDeviceProcAddr(handle, "vkCreateSamplerYcbcrConversion", vkCreateSamplerYcbcrConversion);
				getDeviceProcAddr(handle, "vkDestroyDescriptorUpdateTemplate", vkDestroyDescriptorUpdateTemplate);
				getDeviceProcAddr(handle, "vkDestroySamplerYcbcrConversion", vkDestroySamplerYcbcrConversion);
				getDeviceProcAddr(handle, "vkGetBufferMemoryRequirements2", vkGetBufferMemoryRequirements2);
				getDeviceProcAddr(handle, "vkGetDescriptorSetLayoutSupport", vkGetDescriptorSetLayoutSupport);
				getDeviceProcAddr(handle, "vkGetDeviceGroupPeerMemoryFeatures", vkGetDeviceGroupPeerMemoryFeatures);
				getDeviceProcAddr(handle, "vkGetDeviceQueue2", vkGetDeviceQueue2);
				getDeviceProcAddr(handle, "vkGetImageMemoryRequirements2", vkGetImageMemoryRequirements2);
				getDeviceProcAddr(handle, "vkGetImageSparseMemoryRequirements2", vkGetImageSparseMemoryRequirements2);
				getDeviceProcAddr(handle, "vkTrimCommandPool", vkTrimCommandPool);
				getDeviceProcAddr(handle, "vkUpdateDescriptorSetWithTemplate", vkUpdateDescriptorSetWithTemplate);
			}
		};
	}
#endif

#ifdef VKFW_KHR_surface
	namespace Hidden::PFN::KHR_surface {
		class Instance {
		public:
			inline static typename FnType<decltype(vkDestroySurfaceKHR)>::Eval vkDestroySurfaceKHR;
			inline static typename FnType<decltype(vkGetPhysicalDeviceSurfaceSupportKHR)>::Eval vkGetPhysicalDeviceSurfaceSupportKHR;
			inline static typename FnType<decltype(vkGetPhysicalDeviceSurfaceCapabilitiesKHR)>::Eval vkGetPhysicalDeviceSurfaceCapabilitiesKHR;
			inline static typename FnType<decltype(vkGetPhysicalDeviceSurfaceFormatsKHR)>::Eval vkGetPhysicalDeviceSurfaceFormatsKHR;
			inline static typename FnType<decltype(vkGetPhysicalDeviceSurfacePresentModesKHR)>::Eval vkGetPhysicalDeviceSurfacePresentModesKHR;

			void static init(VkInstance handle) {
				getInstanceProcAddr(handle, "vkDestroySurfaceKHR", vkDestroySurfaceKHR);
				getInstanceProcAddr(handle, "vkGetPhysicalDeviceSurfaceSupportKHR", vkGetPhysicalDeviceSurfaceSupportKHR);
				getInstanceProcAddr(handle, "vkGetPhysicalDeviceSurfaceCapabilitiesKHR", vkGetPhysicalDeviceSurfaceCapabilitiesKHR);
				getInstanceProcAddr(handle, "vkGetPhysicalDeviceSurfaceFormatsKHR", vkGetPhysicalDeviceSurfaceFormatsKHR);
				getInstanceProcAddr(handle, "vkGetPhysicalDeviceSurfacePresentModesKHR", vkGetPhysicalDeviceSurfacePresentModesKHR);
			}
		};
	}

#ifdef VKFW_KHR_swapchain
	namespace Hidden::PFN::KHR_swapchain {
		class Device {
		public:
			inline static typename FnType<decltype(vkCreateSwapchainKHR)>::Eval vkCreateSwapchainKHR;
			inline static typename FnType<decltype(vkDestroySwapchainKHR)>::Eval vkDestroySwapchainKHR;
			inline static typename FnType<decltype(vkQueuePresentKHR)>::Eval vkQueuePresentKHR;
			inline static typename FnType<decltype(vkAcquireNextImageKHR)>::Eval vkAcquireNextImageKHR;
			inline static typename FnType<decltype(vkGetSwapchainImagesKHR)>::Eval vkGetSwapchainImagesKHR;

			void static init(VkDevice handle) {
				getDeviceProcAddr(handle, "vkCreateSwapchainKHR", vkCreateSwapchainKHR);
				getDeviceProcAddr(handle, "vkDestroySwapchainKHR", vkDestroySwapchainKHR);
				getDeviceProcAddr(handle, "vkQueuePresentKHR", vkQueuePresentKHR);
				getDeviceProcAddr(handle, "vkAcquireNextImageKHR", vkAcquireNextImageKHR);
				getDeviceProcAddr(handle, "vkGetSwapchainImagesKHR", vkGetSwapchainImagesKHR);
			}
		};
	}
#endif

#if defined(VKFW_KHR_win32_surface) || defined(_WIN32) || defined(_WIN64)
	namespace Hidden::PFN::KHR_win32_surface {
		class Instance {
		public:
			inline static typename FnType<decltype(vkCreateWin32SurfaceKHR)>::Eval vkCreateWin32SurfaceKHR;
			inline static typename FnType<decltype(vkGetPhysicalDeviceWin32PresentationSupportKHR)>::Eval vkGetPhysicalDeviceWin32PresentationSupportKHR;

			void static init(VkInstance handle) {
				getInstanceProcAddr(handle, "vkCreateWin32SurfaceKHR", vkCreateWin32SurfaceKHR);
				getInstanceProcAddr(handle, "vkGetPhysicalDeviceWin32PresentationSupportKHR", vkGetPhysicalDeviceWin32PresentationSupportKHR);
			}
		};
	}
#endif
#endif

	class Buffer {
		using CorePFN = Hidden::PFN::Core::Device;
		VKFW_HANDLE_CHILD(Buffer, VkBuffer, m_handle)

		inline VkResult bindMemory(VkDeviceMemory memory, VkDeviceSize memoryOffset) {
			return VKFW_DEBUG_VKRESULT(CorePFN::vkBindBufferMemory(Hidden::PFN::device, m_handle, memory, memoryOffset));
		}

		inline void destroy(const VkAllocationCallbacks *pAllocator = nullptr) {
			CorePFN::vkDestroyBuffer(Hidden::PFN::device, m_handle, pAllocator);
		}

		inline void getMemoryRequirements(VkMemoryRequirements *pMemoryRequirements) const {
			CorePFN::vkGetBufferMemoryRequirements(Hidden::PFN::device, m_handle, pMemoryRequirements);
		}
	};

	class BufferView {
		using CorePFN = Hidden::PFN::Core::Device;
		VKFW_HANDLE_CHILD(BufferView, VkBufferView, m_handle)

		void destroy(const VkAllocationCallbacks *pAllocator = nullptr) {
			CorePFN::vkDestroyBufferView(Hidden::PFN::device, m_handle, pAllocator);
		}
	};

	class CommandBuffer {
		using CorePFN = Hidden::PFN::Core::Device;
		VKFW_HANDLE_CHILD(CommandBuffer, VkCommandBuffer, m_handle)

		inline VkResult begin(const VkCommandBufferBeginInfo *pBeginInfo) {
			return VKFW_DEBUG_VKRESULT(CorePFN::vkBeginCommandBuffer(m_handle, pBeginInfo));
		}

		inline void cmdBeginQuery(VkQueryPool queryPool, uint32_t query, VkQueryControlFlags flags) {
			CorePFN::vkCmdBeginQuery(m_handle, queryPool, query, flags);
		}

		inline void cmdBeginRenderPass(const VkRenderPassBeginInfo *pRenderPassBegin, VkSubpassContents contents) {
			CorePFN::vkCmdBeginRenderPass(m_handle, pRenderPassBegin, contents);
		}

		inline void cmdBindDescriptorSets(VkPipelineBindPoint pipelineBindPoint, VkPipelineLayout layout,
			uint32_t firstSet, uint32_t descriptorSetCount, const VkDescriptorSet *pDescriptorSets,
			uint32_t dynamicOffsetCount, const uint32_t *pDynamicOffsets) {
			CorePFN::vkCmdBindDescriptorSets(m_handle, pipelineBindPoint, layout, firstSet, descriptorSetCount, pDescriptorSets, dynamicOffsetCount, pDynamicOffsets);
		}

		inline void cmdBindIndexBuffer(VkBuffer buffer, VkDeviceSize offset, VkIndexType indexType) {
			CorePFN::vkCmdBindIndexBuffer(m_handle, buffer, offset, indexType);
		}

		inline void cmdBindPipeline(VkPipelineBindPoint pipelineBindPoint, VkPipeline pipeline) {
			CorePFN::vkCmdBindPipeline(m_handle, pipelineBindPoint, pipeline);
		}

		inline void cmdBindVertexBuffers(uint32_t firstBinding, uint32_t bindingCount, const VkBuffer *pBuffers, const VkDeviceSize *pOffsets) {
			CorePFN::vkCmdBindVertexBuffers(m_handle, firstBinding, bindingCount, pBuffers, pOffsets);
		}

		inline void cmdBlitImage(VkImage srcImage, VkImageLayout srcImageLayout, VkImage dstImage, VkImageLayout dstImageLayout,
			uint32_t regionCount, const VkImageBlit *pRegions, VkFilter filter) {
			CorePFN::vkCmdBlitImage(m_handle, srcImage, srcImageLayout, dstImage, dstImageLayout, regionCount, pRegions, filter);
		}

		inline void cmdClearAttachments(uint32_t attachmentCount, const VkClearAttachment *pAttachments, uint32_t rectCount, const VkClearRect *pRects) {
			CorePFN::vkCmdClearAttachments(m_handle, attachmentCount, pAttachments, rectCount, pRects);
		}

		inline void cmdClearColorImage(VkImage image, VkImageLayout imageLayout, const VkClearColorValue *pColor, uint32_t rangeCount, const VkImageSubresourceRange *pRanges) {
			CorePFN::vkCmdClearColorImage(m_handle, image, imageLayout, pColor, rangeCount, pRanges);
		}

		inline void cmdClearDepthStencilImage(VkImage image, VkImageLayout imageLayout, const VkClearDepthStencilValue *pDepthStencil,
			uint32_t rangeCount, const VkImageSubresourceRange *pRanges) {
			CorePFN::vkCmdClearDepthStencilImage(m_handle, image, imageLayout, pDepthStencil, rangeCount, pRanges);
		}

		inline void cmdCopyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, uint32_t regionCount, const VkBufferCopy *pRegions) {
			CorePFN::vkCmdCopyBuffer(m_handle, srcBuffer, dstBuffer, regionCount, pRegions);
		}

		inline void cmdCopyBufferToImage(VkBuffer srcBuffer, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t regionCount, const VkBufferImageCopy *pRegions) {
			CorePFN::vkCmdCopyBufferToImage(m_handle, srcBuffer, dstImage, dstImageLayout, regionCount, pRegions);
		}

		inline void cmdCopyImage(VkImage srcImage, VkImageLayout srcImageLayout, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t regionCount, const VkImageCopy *pRegions) {
			CorePFN::vkCmdCopyImage(m_handle, srcImage, srcImageLayout, dstImage, dstImageLayout, regionCount, pRegions);
		}

		inline void cmdCopyImageToBuffer(VkImage srcImage, VkImageLayout srcImageLayout, VkBuffer dstBuffer, uint32_t regionCount, const VkBufferImageCopy *pRegions) {
			CorePFN::vkCmdCopyImageToBuffer(m_handle, srcImage, srcImageLayout, dstBuffer, regionCount, pRegions);
		}

		inline void cmdCopyQueryPoolResults(VkQueryPool queryPool, uint32_t firstQuery, uint32_t queryCount, VkBuffer dstBuffer, VkDeviceSize dstOffset,
			VkDeviceSize stride, VkQueryResultFlags flags) {
			CorePFN::vkCmdCopyQueryPoolResults(m_handle, queryPool, firstQuery, queryCount, dstBuffer, dstOffset, stride, flags);
		}

		inline void cmdDispatch(uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ) {
			CorePFN::vkCmdDispatch(m_handle, groupCountX, groupCountY, groupCountZ);
		}

		inline void cmdDispatchIndirect(VkBuffer buffer, VkDeviceSize offset) {
			CorePFN::vkCmdDispatchIndirect(m_handle, buffer, offset);
		}

		inline void cmdDraw(uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance) {
			CorePFN::vkCmdDraw(m_handle, vertexCount, instanceCount, firstVertex, firstInstance);
		}

		inline void cmdDrawIndexed(uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t vertexOffset, uint32_t firstInstance) {
			CorePFN::vkCmdDrawIndexed(m_handle, indexCount, instanceCount, firstIndex, vertexOffset, firstInstance);
		}

		inline void cmdDrawIndexedIndirect(VkBuffer buffer, VkDeviceSize offset, uint32_t drawCount, uint32_t stride) {
			CorePFN::vkCmdDrawIndexedIndirect(m_handle, buffer, offset, drawCount, stride);
		}

		inline void cmdDrawIndirect(VkBuffer buffer, VkDeviceSize offset, uint32_t drawCount, uint32_t stride) {
			CorePFN::vkCmdDrawIndirect(m_handle, buffer, offset, drawCount, stride);
		}

		inline void cmdEndQuery(VkQueryPool queryPool, uint32_t query) {
			CorePFN::vkCmdEndQuery(m_handle, queryPool, query);
		}

		inline void cmdEndRenderPass() {
			CorePFN::vkCmdEndRenderPass(m_handle);
		}

		inline void cmdExecuteCommands(uint32_t commandBufferCount, const VkCommandBuffer *pCommandBuffers) {
			CorePFN::vkCmdExecuteCommands(m_handle, commandBufferCount, pCommandBuffers);
		}

		inline void cmdFillBuffer(VkBuffer dstBuffer, VkDeviceSize dstOffset, VkDeviceSize size, uint32_t data) {
			CorePFN::vkCmdFillBuffer(m_handle, dstBuffer, dstOffset, size, data);
		}

		inline void cmdNextSubpass(VkSubpassContents contents) {
			CorePFN::vkCmdNextSubpass(m_handle, contents);
		}

		inline void cmdPipelineBarrier(VkPipelineStageFlags srcStageMask, VkPipelineStageFlags dstStageMask, VkDependencyFlags dependencyFlags,
			uint32_t memoryBarrierCount, const VkMemoryBarrier *pMemoryBarriers, uint32_t bufferMemoryBarrierCount,
			const VkBufferMemoryBarrier *pBufferMemoryBarriers, uint32_t imageMemoryBarrierCount, const VkImageMemoryBarrier *pImageMemoryBarriers) {
			CorePFN::vkCmdPipelineBarrier(m_handle, srcStageMask, dstStageMask, dependencyFlags, memoryBarrierCount,
				pMemoryBarriers, bufferMemoryBarrierCount, pBufferMemoryBarriers, imageMemoryBarrierCount, pImageMemoryBarriers);
		}

		inline void cmdPushConstants(VkPipelineLayout layout, VkShaderStageFlags stageFlags, uint32_t offset, uint32_t size, const void *pValues) {
			CorePFN::vkCmdPushConstants(m_handle, layout, stageFlags, offset, size, pValues);
		}

		inline void cmdResetEvent(VkEvent event, VkPipelineStageFlags stageMask) {
			CorePFN::vkCmdResetEvent(m_handle, event, stageMask);
		}

		inline void cmdResetQueryPool(VkQueryPool queryPool, uint32_t firstQuery, uint32_t queryCount) {
			CorePFN::vkCmdResetQueryPool(m_handle, queryPool, firstQuery, queryCount);
		}

		inline void cmdResolveImage(VkImage srcImage, VkImageLayout srcImageLayout, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t regionCount, const VkImageResolve *pRegions) {
			CorePFN::vkCmdResolveImage(m_handle, srcImage, srcImageLayout, dstImage, dstImageLayout, regionCount, pRegions);
		}

		inline void cmdSetBlendConstants(const float blendConstants[4]) {
			CorePFN::vkCmdSetBlendConstants(m_handle, blendConstants);
		}

		inline void cmdSetDepthBias(float depthBiasConstantFactor, float depthBiasClamp, float depthBiasSlopeFactor) {
			CorePFN::vkCmdSetDepthBias(m_handle, depthBiasConstantFactor, depthBiasClamp, depthBiasSlopeFactor);
		}

		inline void cmdSetDepthBounds(float minDepthBounds, float maxDepthBounds) {
			CorePFN::vkCmdSetDepthBounds(m_handle, minDepthBounds, maxDepthBounds);
		}

		inline void cmdSetEvent(VkEvent event, VkPipelineStageFlags stageMask) {
			CorePFN::vkCmdSetEvent(m_handle, event, stageMask);
		}

		inline void cmdSetLineWidth(float lineWidth) {
			CorePFN::vkCmdSetLineWidth(m_handle, lineWidth);
		}

		inline void cmdSetScissor(uint32_t firstScissor, uint32_t scissorCount, const VkRect2D *pScissors) {
			CorePFN::vkCmdSetScissor(m_handle, firstScissor, scissorCount, pScissors);
		}

		inline void cmdSetStencilCompareMask(VkStencilFaceFlags faceMask, uint32_t compareMask) {
			CorePFN::vkCmdSetStencilCompareMask(m_handle, faceMask, compareMask);
		}

		inline void cmdSetStencilReference(VkStencilFaceFlags faceMask, uint32_t reference) {
			CorePFN::vkCmdSetStencilReference(m_handle, faceMask, reference);
		}

		inline void cmdSetStencilWriteMask(VkStencilFaceFlags faceMask, uint32_t writeMask) {
			CorePFN::vkCmdSetStencilWriteMask(m_handle, faceMask, writeMask);
		}

		inline void cmdSetViewport(uint32_t firstViewport, uint32_t viewportCount, const VkViewport *pViewports) {
			CorePFN::vkCmdSetViewport(m_handle, firstViewport, viewportCount, pViewports);
		}

		inline void cmdUpdateBuffer(VkBuffer dstBuffer, VkDeviceSize dstOffset, VkDeviceSize dataSize, const void *pData) {
			CorePFN::vkCmdUpdateBuffer(m_handle, dstBuffer, dstOffset, dataSize, pData);
		}

		inline void cmdWaitEvents(uint32_t eventCount, const VkEvent *pEvents, VkPipelineStageFlags srcStageMask,
			VkPipelineStageFlags dstStageMask, uint32_t memoryBarrierCount, const VkMemoryBarrier *pMemoryBarriers,
			uint32_t bufferMemoryBarrierCount, const VkBufferMemoryBarrier *pBufferMemoryBarriers,
			uint32_t imageMemoryBarrierCount, const VkImageMemoryBarrier *pImageMemoryBarriers) {
			CorePFN::vkCmdWaitEvents(m_handle, eventCount, pEvents, srcStageMask, dstStageMask, memoryBarrierCount, pMemoryBarriers,
				bufferMemoryBarrierCount, pBufferMemoryBarriers, imageMemoryBarrierCount, pImageMemoryBarriers);
		}

		inline void cmdWriteTimestamp(VkPipelineStageFlagBits pipelineStage, VkQueryPool queryPool, uint32_t query) {
			CorePFN::vkCmdWriteTimestamp(m_handle, pipelineStage, queryPool, query);
		}

		inline VkResult end() {
			return VKFW_DEBUG_VKRESULT(CorePFN::vkEndCommandBuffer(m_handle));
		}

		inline VkResult reset(VkCommandBufferResetFlags flags = 0) {
			return VKFW_DEBUG_VKRESULT(CorePFN::vkResetCommandBuffer(m_handle, flags));
		}
	};

	class CommandPool {
		using CorePFN = Hidden::PFN::Core::Device;
#if VKFW_V_MAJOR >= 1 && VKFW_V_MINOR >= 1
		using Core1_1PFN = Hidden::PFN::Core1_1::Device;
#endif
		VKFW_HANDLE_CHILD(CommandPool, VkCommandPool, m_handle)

		inline void destroy(const VkAllocationCallbacks *pAllocator = nullptr) {
			CorePFN::vkDestroyCommandPool(Hidden::PFN::device, m_handle, pAllocator);
		}

		inline void freeCommandBuffers(uint32_t commandBufferCount, const VkCommandBuffer *pCommandBuffers) {
			CorePFN::vkFreeCommandBuffers(Hidden::PFN::device, m_handle, commandBufferCount, pCommandBuffers);
		}

		inline VkResult reset(VkCommandPoolResetFlags flags = 0) {
			return VKFW_DEBUG_VKRESULT(CorePFN::vkResetCommandPool(Hidden::PFN::device, m_handle, flags));
		}

#if VKFW_V_MAJOR >= 1 && VKFW_V_MINOR >= 1
		inline void trimCommandPool(VkCommandPoolTrimFlags flags) {
			Core1_1PFN::vkTrimCommandPool(Hidden::PFN::device, m_handle, flags);
		}
#endif
	};

	class DescriptorPool {
		using CorePFN = Hidden::PFN::Core::Device;
		VKFW_HANDLE_CHILD(DescriptorPool, VkDescriptorPool, m_handle)

		inline void destroy(const VkAllocationCallbacks *pAllocator = nullptr) {
			return CorePFN::vkDestroyDescriptorPool(Hidden::PFN::device, m_handle, pAllocator);
		}

		inline VkResult free(uint32_t descriptorSetCount, const VkDescriptorSet *pDescriptorSets) {
			return VKFW_DEBUG_VKRESULT(CorePFN::vkFreeDescriptorSets(Hidden::PFN::device, m_handle, descriptorSetCount, pDescriptorSets));
		}

		inline VkResult reset(VkDescriptorPoolResetFlags flags = 0) {
			return VKFW_DEBUG_VKRESULT(CorePFN::vkResetDescriptorPool(Hidden::PFN::device, m_handle, flags));
		}
	};

	class DescriptorSet {
#if VKFW_V_MAJOR >= 1 && VKFW_V_MINOR >= 1
		using Core1_1PFN = Hidden::PFN::Core1_1::Device;
#endif
		VKFW_HANDLE_CHILD(DescriptorSet, VkDescriptorSet, m_handle)

#if VKFW_V_MAJOR >= 1 && VKFW_V_MINOR >= 1
		inline void updateDescriptorSetWithTemplate(VkCommandPoolTrimFlags flags, void *pData) {
			Core1_1PFN::vkUpdateDescriptorSetWithTemplate(Hidden::PFN::device, m_handle, flags, pData);
		}
#endif
	};

	class DescriptorSetLayout {
		using CorePFN = Hidden::PFN::Core::Device;
		VKFW_HANDLE_CHILD(DescriptorSetLayout, VkDescriptorSetLayout, m_handle)

		inline void destroy(const VkAllocationCallbacks *pAllocator = nullptr) {
			CorePFN::vkDestroyDescriptorSetLayout(Hidden::PFN::device, m_handle, pAllocator);
		}
	};

	class Device {
		using CorePFN = Hidden::PFN::Core::Device;
#if VKFW_V_MAJOR >= 1 && VKFW_V_MINOR >= 1
		using Core1_1PFN = Hidden::PFN::Core1_1::Device;
#endif
#ifdef VKFW_KHR_surface
#ifdef VKFW_KHR_swapchain
		using KHR_swapchainPFN = Hidden::PFN::KHR_swapchain::Device;
#endif
#endif
		VKFW_HANDLE_PARENT(Device, VkDevice, Hidden::PFN::device)

		inline static void init() {
			Hidden::PFN::Core::Device::init(Hidden::PFN::device);
#ifdef VKFW_KHR_surface
#ifdef VKFW_KHR_swapchain
			Hidden::PFN::KHR_swapchain::Device::init(Hidden::PFN::device);
#endif
#endif
		}

		inline static VkResult allocateCommandBuffers(VkCommandBuffer *pCommandBuffers, const VkCommandBufferAllocateInfo *pAllocateInfo = nullptr) {
			return VKFW_DEBUG_VKRESULT(CorePFN::vkAllocateCommandBuffers(Hidden::PFN::device, pAllocateInfo, pCommandBuffers));
		}

		inline static VkResult allocateDescriptorSets(VkDescriptorSet *pDescriptorSets, const VkDescriptorSetAllocateInfo *pAllocateInfo = nullptr) {
			return VKFW_DEBUG_VKRESULT(CorePFN::vkAllocateDescriptorSets(Hidden::PFN::device, pAllocateInfo, pDescriptorSets));
		}

		inline static VkResult allocateMemory(VkDeviceMemory *pMemory, const VkMemoryAllocateInfo *pAllocateInfo, const VkAllocationCallbacks *pAllocator = nullptr) {
			return VKFW_DEBUG_VKRESULT(CorePFN::vkAllocateMemory(Hidden::PFN::device, pAllocateInfo, pAllocator, pMemory));
		}

		inline static VkResult bindBufferMemory(VkBuffer buffer, VkDeviceMemory memory, VkDeviceSize memoryOffset) {
			return VKFW_DEBUG_VKRESULT(CorePFN::vkBindBufferMemory(Hidden::PFN::device, buffer, memory, memoryOffset));
		}

		inline static VkResult bindImageMemory(VkImage image, VkDeviceMemory memory, VkDeviceSize memoryOffset) {
			return VKFW_DEBUG_VKRESULT(CorePFN::vkBindImageMemory(Hidden::PFN::device, image, memory, memoryOffset));
		}

		inline static VkResult createBuffer(VkBuffer *pBuffer, const VkBufferCreateInfo *pCreateInfo, const VkAllocationCallbacks *pAllocator = nullptr) {
			return VKFW_DEBUG_VKRESULT(CorePFN::vkCreateBuffer(Hidden::PFN::device, pCreateInfo, pAllocator, pBuffer));
		}

		inline static VkResult createBufferView(VkBufferView *pView, const VkBufferViewCreateInfo *pCreateInfo, const VkAllocationCallbacks *pAllocator = nullptr) {
			return VKFW_DEBUG_VKRESULT(CorePFN::vkCreateBufferView(Hidden::PFN::device, pCreateInfo, pAllocator, pView));
		}

		inline static VkResult createCommandPool(VkCommandPool *pCommandPool, const VkCommandPoolCreateInfo *pCreateInfo, const VkAllocationCallbacks *pAllocator = nullptr) {
			return VKFW_DEBUG_VKRESULT(CorePFN::vkCreateCommandPool(Hidden::PFN::device, pCreateInfo, pAllocator, pCommandPool));
		}

		inline static VkResult createComputePipelines(VkPipeline *pPipelines, VkPipelineCache pipelineCache, uint32_t createInfoCount, const VkComputePipelineCreateInfo *pCreateInfos,
			const VkAllocationCallbacks *pAllocator = nullptr) {
			return VKFW_DEBUG_VKRESULT(CorePFN::vkCreateComputePipelines(Hidden::PFN::device, pipelineCache, createInfoCount, pCreateInfos, pAllocator, pPipelines));
		}

		inline static VkResult createDescriptorPool(VkDescriptorPool *pDescriptorPool, const VkDescriptorPoolCreateInfo *pCreateInfo, const VkAllocationCallbacks *pAllocator = nullptr) {
			return VKFW_DEBUG_VKRESULT(CorePFN::vkCreateDescriptorPool(Hidden::PFN::device, pCreateInfo, pAllocator, pDescriptorPool));
		}

		inline static VkResult createDescriptorSetLayout(VkDescriptorSetLayout *pSetLayout, const VkDescriptorSetLayoutCreateInfo *pCreateInfo, const VkAllocationCallbacks *pAllocator = nullptr) {
			return VKFW_DEBUG_VKRESULT(CorePFN::vkCreateDescriptorSetLayout(Hidden::PFN::device, pCreateInfo, pAllocator, pSetLayout));
		}

		inline static VkResult createEvent(VkEvent *pEvent, const VkEventCreateInfo *pCreateInfo, const VkAllocationCallbacks *pAllocator = nullptr) {
			return VKFW_DEBUG_VKRESULT(CorePFN::vkCreateEvent(Hidden::PFN::device, pCreateInfo, pAllocator, pEvent));
		}

		inline static VkResult createFence(VkFence *pFence, const VkFenceCreateInfo *pCreateInfo, const VkAllocationCallbacks *pAllocator = nullptr) {
			return VKFW_DEBUG_VKRESULT(CorePFN::vkCreateFence(Hidden::PFN::device, pCreateInfo, pAllocator, pFence));
		}

		inline static VkResult createFramebuffer(VkFramebuffer *pFramebuffer, const VkFramebufferCreateInfo *pCreateInfo, const VkAllocationCallbacks *pAllocator = nullptr) {
			return VKFW_DEBUG_VKRESULT(CorePFN::vkCreateFramebuffer(Hidden::PFN::device, pCreateInfo, pAllocator, pFramebuffer));
		}

		inline static VkResult createGraphicsPipelines(VkPipeline *pPipelines, VkPipelineCache pipelineCache, uint32_t createInfoCount,
			const VkGraphicsPipelineCreateInfo *pCreateInfos, const VkAllocationCallbacks *pAllocator = nullptr) {
			return VKFW_DEBUG_VKRESULT(CorePFN::vkCreateGraphicsPipelines(Hidden::PFN::device, pipelineCache, createInfoCount, pCreateInfos, pAllocator, pPipelines));
		}

		inline static VkResult createImage(VkImage *pImage, const VkImageCreateInfo *pCreateInfo, const VkAllocationCallbacks *pAllocator = nullptr) {
			return VKFW_DEBUG_VKRESULT(CorePFN::vkCreateImage(Hidden::PFN::device, pCreateInfo, pAllocator, pImage));
		}

		inline static VkResult createImageView(VkImageView *pView, const VkImageViewCreateInfo *pCreateInfo, const VkAllocationCallbacks *pAllocator = nullptr) {
			return VKFW_DEBUG_VKRESULT(CorePFN::vkCreateImageView(Hidden::PFN::device, pCreateInfo, pAllocator, pView));
		}

		inline static VkResult createPipelineCache(VkPipelineCache *pPipelineCache, const VkPipelineCacheCreateInfo *pCreateInfo, const VkAllocationCallbacks *pAllocator = nullptr) {
			return VKFW_DEBUG_VKRESULT(CorePFN::vkCreatePipelineCache(Hidden::PFN::device, pCreateInfo, pAllocator, pPipelineCache));
		}

		inline static VkResult createPipelineLayout(VkPipelineLayout *pPipelineLayout, const VkPipelineLayoutCreateInfo *pCreateInfo, const VkAllocationCallbacks *pAllocator = nullptr) {
			return VKFW_DEBUG_VKRESULT(CorePFN::vkCreatePipelineLayout(Hidden::PFN::device, pCreateInfo, pAllocator, pPipelineLayout));
		}

		inline static VkResult createQueryPool(VkQueryPool *pQueryPool, const VkQueryPoolCreateInfo *pCreateInfo, const VkAllocationCallbacks *pAllocator = nullptr) {
			return VKFW_DEBUG_VKRESULT(CorePFN::vkCreateQueryPool(Hidden::PFN::device, pCreateInfo, pAllocator, pQueryPool));
		}

		inline static VkResult createRenderPass(VkRenderPass *pRenderPass, const VkRenderPassCreateInfo *pCreateInfo, const VkAllocationCallbacks *pAllocator = nullptr) {
			return VKFW_DEBUG_VKRESULT(CorePFN::vkCreateRenderPass(Hidden::PFN::device, pCreateInfo, pAllocator, pRenderPass));
		}

		inline static VkResult createSampler(VkSampler *pSampler, const VkSamplerCreateInfo *pCreateInfo, const VkAllocationCallbacks *pAllocator = nullptr) {
			return VKFW_DEBUG_VKRESULT(CorePFN::vkCreateSampler(Hidden::PFN::device, pCreateInfo, pAllocator, pSampler));
		}

		inline static VkResult createSemaphore(VkSemaphore *pSemaphore, const VkSemaphoreCreateInfo *pCreateInfo, const VkAllocationCallbacks *pAllocator = nullptr) {
			return VKFW_DEBUG_VKRESULT(CorePFN::vkCreateSemaphore(Hidden::PFN::device, pCreateInfo, pAllocator, pSemaphore));
		}


		inline static VkResult createShaderModule(VkShaderModule *pShaderModule, const VkShaderModuleCreateInfo *pCreateInfo, const VkAllocationCallbacks *pAllocator = nullptr) {
			return VKFW_DEBUG_VKRESULT(CorePFN::vkCreateShaderModule(Hidden::PFN::device, pCreateInfo, pAllocator, pShaderModule));
		}

		inline static void destroy(const VkAllocationCallbacks *pAllocator = nullptr) {
			CorePFN::vkDestroyDevice(Hidden::PFN::device, pAllocator);
		}

		inline static VkResult waitIdel() {
			return VKFW_DEBUG_VKRESULT(CorePFN::vkDeviceWaitIdle(Hidden::PFN::device));
		}

		inline static VkResult flushMappedMemoryRanges(uint32_t memoryRangeCount, const VkMappedMemoryRange *pMemoryRanges) {
			return VKFW_DEBUG_VKRESULT(CorePFN::vkFlushMappedMemoryRanges(Hidden::PFN::device, memoryRangeCount, pMemoryRanges));
		}

		inline void getQueue(VkQueue *pQueue, uint32_t queueFamilyIndex, uint32_t queueIndex) const {
			CorePFN::vkGetDeviceQueue(Hidden::PFN::device, queueFamilyIndex, queueIndex, pQueue);
		}

		inline static VkResult invalidateMappedMemoryRanges(uint32_t memoryRangeCount, const VkMappedMemoryRange *pMemoryRanges) {
			return VKFW_DEBUG_VKRESULT(CorePFN::vkInvalidateMappedMemoryRanges(Hidden::PFN::device, memoryRangeCount, pMemoryRanges));
		}

		inline static VkResult resetFences(uint32_t fenceCount, const VkFence *pFences) {
			return VKFW_DEBUG_VKRESULT(CorePFN::vkResetFences(Hidden::PFN::device, fenceCount, pFences));
		}

		inline static void updateDescriptorSets(uint32_t descriptorWriteCount, const VkWriteDescriptorSet *pDescriptorWrites,
			uint32_t descriptorCopyCount, const VkCopyDescriptorSet *pDescriptorCopies) {
			CorePFN::vkUpdateDescriptorSets(Hidden::PFN::device, descriptorWriteCount, pDescriptorWrites, descriptorCopyCount, pDescriptorCopies);
		}

		inline static VkResult waitForFences(uint32_t fenceCount, const VkFence *pFences, VkBool32 waitAll, uint64_t timeout) {
			return VKFW_DEBUG_VKRESULT(CorePFN::vkWaitForFences(Hidden::PFN::device, fenceCount, pFences, waitAll, timeout));
		}

#if VKFW_V_MAJOR >= 1 && VKFW_V_MINOR >= 1
		inline static VkResult bindBufferMemory2(uint32_t bindInfoCount, const VkBindBufferMemoryInfo *pBindInfos) {
			return VKFW_DEBUG_VKRESULT(Core1_1PFN::vkBindBufferMemory2(Hidden::PFN::device, bindInfoCount, pBindInfos));
		}

		inline static VkResult bindImageMemory2(uint32_t bindInfoCount, const VkBindImageMemoryInfo *pBindInfos) {
			return VKFW_DEBUG_VKRESULT(Core1_1PFN::vkBindImageMemory2(Hidden::PFN::device, bindInfoCount, pBindInfos));
		}

		VkResult createDescriptorUpdateTemplate(VkDescriptorUpdateTemplate *pDescriptorUpdateTemplate, 
			const VkDescriptorUpdateTemplateCreateInfo* pCreateInfo,
			const VkAllocationCallbacks *pAllocator = nullptr) {
			return VKFW_DEBUG_VKRESULT(Core1_1PFN::vkCreateDescriptorUpdateTemplate(Hidden::PFN::device, pCreateInfo, pAllocator, pDescriptorUpdateTemplate));
		}

		VkResult createSamplerYcbcrConversion(VkSamplerYcbcrConversion *pYcbcrConversion,
			const VkSamplerYcbcrConversionCreateInfo *pCreateInfo,
			const VkAllocationCallbacks *pAllocator) {
			return VKFW_DEBUG_VKRESULT(Core1_1PFN::vkCreateSamplerYcbcrConversion(Hidden::PFN::device, pCreateInfo, pAllocator, pYcbcrConversion));
		}

		void getBufferMemoryRequirements2(VkMemoryRequirements2 *pMemoryRequirements, const VkBufferMemoryRequirementsInfo2 *pInfo) {
			Core1_1PFN::vkGetBufferMemoryRequirements2(Hidden::PFN::device, pInfo, pMemoryRequirements);
		}

		void getDescriptorSetLayoutSupport(VkDescriptorSetLayoutSupport *pSupport, const VkDescriptorSetLayoutCreateInfo *pCreateInfo) {
			Core1_1PFN::vkGetDescriptorSetLayoutSupport(Hidden::PFN::device, pCreateInfo, pSupport);
		}

		void getDeviceGroupPeerMemoryFeatures(uint32_t heapIndex, uint32_t localDeviceIndex, uint32_t remoteDeviceIndex, 
			VkPeerMemoryFeatureFlags *pPeerMemoryFeatures) {
			Core1_1PFN::vkGetDeviceGroupPeerMemoryFeatures(Hidden::PFN::device, heapIndex, localDeviceIndex, remoteDeviceIndex, pPeerMemoryFeatures);
		}

		void getDeviceQueue2(VkQueue *pQueue, const VkDeviceQueueInfo2 *pQueueInfo) {
			Core1_1PFN::vkGetDeviceQueue2(Hidden::PFN::device, pQueueInfo, pQueue);
		}

		void getImageMemoryRequirements2(VkMemoryRequirements2 *pMemoryRequirements, const VkImageMemoryRequirementsInfo2 *pInfo) {
			Core1_1PFN::vkGetImageMemoryRequirements2(Hidden::PFN::device, pInfo, pMemoryRequirements);
		}

		void getImageSparseMemoryRequirements2(const VkImageSparseMemoryRequirementsInfo2* pInfo,
			uint32_t *pSparseMemoryRequirementCount,
			VkSparseImageMemoryRequirements2 *pSparseMemoryRequirements) {
			Core1_1PFN::vkGetImageSparseMemoryRequirements2(Hidden::PFN::device, pInfo, pSparseMemoryRequirementCount, pSparseMemoryRequirements);
		}
#endif

#ifdef VKFW_KHR_swapchain
		inline static VkResult createSwapchain(VkSwapchainKHR *pSwapchain, const VkSwapchainCreateInfoKHR *pCreateInfo, const VkAllocationCallbacks *pAllocator = nullptr) {
			return VKFW_DEBUG_VKRESULT(KHR_swapchainPFN::vkCreateSwapchainKHR(Hidden::PFN::device, pCreateInfo, pAllocator, pSwapchain));
		}
#endif
	};

	class DeviceMemory {
		using CorePFN = Hidden::PFN::Core::Device;
		VKFW_HANDLE_CHILD(DeviceMemory, VkDeviceMemory, m_handle)

		inline void free(const VkAllocationCallbacks *pAllocator = nullptr) {
			CorePFN::vkFreeMemory(Hidden::PFN::device, m_handle, pAllocator);
		}

		inline void getCommitment(VkDeviceSize *pCommittedMemoryInBytes) {
			CorePFN::vkGetDeviceMemoryCommitment(Hidden::PFN::device, m_handle, pCommittedMemoryInBytes);
		}

		inline VkResult map(void **ppData, VkDeviceSize offset, VkDeviceSize size, VkMemoryMapFlags flags = 0) {
			return VKFW_DEBUG_VKRESULT(CorePFN::vkMapMemory(Hidden::PFN::device, m_handle, offset, size, flags, ppData));
		}

		inline void unmap() {
			CorePFN::vkUnmapMemory(Hidden::PFN::device, m_handle);
		}
	};

	class Event {
		using CorePFN = Hidden::PFN::Core::Device;
		VKFW_HANDLE_CHILD(Event, VkEvent, m_handle)

		inline void destroy(const VkAllocationCallbacks *pAllocator = nullptr) {
			CorePFN::vkDestroyEvent(Hidden::PFN::device, m_handle, pAllocator);
		}

		inline VkResult getStatus() {
			return VKFW_DEBUG_VKRESULT(CorePFN::vkGetEventStatus(Hidden::PFN::device, m_handle));
		}

		inline VkResult reset() {
			return VKFW_DEBUG_VKRESULT(CorePFN::vkResetEvent(Hidden::PFN::device, m_handle));
		}

		inline VkResult set() {
			return VKFW_DEBUG_VKRESULT(CorePFN::vkSetEvent(Hidden::PFN::device, m_handle));
		}
	};

	class Fence {
		using CorePFN = Hidden::PFN::Core::Device;
		VKFW_HANDLE_CHILD(Fence, VkFence, m_handle)

		inline void destroy(const VkAllocationCallbacks *pAllocator = nullptr) {
			CorePFN::vkDestroyFence(Hidden::PFN::device, m_handle, pAllocator);
		}

		inline VkResult getStatus() {
			return VKFW_DEBUG_VKRESULT(CorePFN::vkGetFenceStatus(Hidden::PFN::device, m_handle));
		}
	};

	class Framebuffer {
		using CorePFN = Hidden::PFN::Core::Device;
		VKFW_HANDLE_CHILD(Framebuffer, VkFramebuffer, m_handle)

		inline void destroy(const VkAllocationCallbacks *pAllocator = nullptr) {
			CorePFN::vkDestroyFramebuffer(Hidden::PFN::device, m_handle, pAllocator);
		}
	};

	class Image {
		using CorePFN = Hidden::PFN::Core::Device;
		VKFW_HANDLE_CHILD(Image, VkImage, m_handle)

		inline VkResult bindMemory(VkDeviceMemory memory, VkDeviceSize memoryOffset) {
			return VKFW_DEBUG_VKRESULT(CorePFN::vkBindImageMemory(Hidden::PFN::device, m_handle, memory, memoryOffset));
		}

		inline void destroy(const VkAllocationCallbacks *pAllocator = nullptr) {
			CorePFN::vkDestroyImage(Hidden::PFN::device, m_handle, pAllocator);
		}

		inline void getMemoryRequirements(VkMemoryRequirements *pMemoryRequirements) {
			CorePFN::vkGetImageMemoryRequirements(Hidden::PFN::device, m_handle, pMemoryRequirements);
		}

		inline void getSparseMemoryRequirements(uint32_t *pSparseMemoryRequirementCount, VkSparseImageMemoryRequirements *pSparseMemoryRequirements) {
			CorePFN::vkGetImageSparseMemoryRequirements(Hidden::PFN::device, m_handle, pSparseMemoryRequirementCount, pSparseMemoryRequirements);
		}

		inline void getSubresourceLayout(const VkImageSubresource *pSubresource, VkSubresourceLayout *pLayout) {
			CorePFN::vkGetImageSubresourceLayout(Hidden::PFN::device, m_handle, pSubresource, pLayout);
		}
	};

	class ImageView {
		using CorePFN = Hidden::PFN::Core::Device;
		VKFW_HANDLE_CHILD(ImageView, VkImageView, m_handle)

		inline void destroy(const VkAllocationCallbacks *pAllocator = nullptr) {
			CorePFN::vkDestroyImageView(Hidden::PFN::device, m_handle, pAllocator);
		}
	};

	class Instance {
	public:
		using CorePFN = Hidden::PFN::Core::Instance;
#if VKFW_V_MAJOR >= 1 && VKFW_V_MINOR >= 1
		using Core1_1PFN = Hidden::PFN::Core1_1::Instance;
#endif
#ifdef VKFW_KHR_surface
#if defined(VKFW_KHR_win32_surface) || defined(_WIN32) || defined(_WIN64)
		using KHR_win32_surfacePFN = Hidden::PFN::KHR_win32_surface::Instance;
#endif
#endif
		VKFW_HANDLE_PARENT(Instance, VkInstance, Hidden::PFN::instance)

		inline static void init() {
			Hidden::PFN::Core::Instance::init(Hidden::PFN::instance);
#if VKFW_V_MAJOR >= 1 && VKFW_V_MINOR >= 1
			Hidden::PFN::Core1_1::Instance::init(Hidden::PFN::instance);
#endif
#ifdef VKFW_KHR_surface
			Hidden::PFN::KHR_surface::Instance::init(Hidden::PFN::instance);
#if defined(VKFW_KHR_win32_surface) || defined(_WIN32) || defined(_WIN64)
			Hidden::PFN::KHR_win32_surface::Instance::init(Hidden::PFN::instance);
#endif
#endif
		}

		inline void createAndInit(const VkInstanceCreateInfo *pCreateInfo, const VkAllocationCallbacks *pAllocator = nullptr) {
			createInstance(&Hidden::PFN::instance, pCreateInfo, pAllocator);
			init();
		}

		inline static void destroy(const VkAllocationCallbacks *pAllocator = nullptr) {
			CorePFN::vkDestroyInstance(Hidden::PFN::instance, pAllocator);
		}

		inline static VkResult enumeratePhysicalDevices(uint32_t *pPhysicalDeviceCount, VkPhysicalDevice* pPhysicalDevices = nullptr) {
			return VKFW_DEBUG_VKRESULT(CorePFN::vkEnumeratePhysicalDevices(Hidden::PFN::instance, pPhysicalDeviceCount, pPhysicalDevices));
		}

#if VKFW_V_MAJOR >= 1 && VKFW_V_MINOR >= 1
		inline static VkResult enumeratePhysicalDeviceGroups(uint32_t *pPhysicalDeviceGroupCount, VkPhysicalDeviceGroupProperties *pPhysicalDeviceGroupProperties) {
			return VKFW_DEBUG_VKRESULT(Core1_1PFN::vkEnumeratePhysicalDeviceGroups(Hidden::PFN::instance, pPhysicalDeviceGroupCount, pPhysicalDeviceGroupProperties));
		}
#endif

#ifdef VKFW_KHR_surface
#if defined(VKFW_KHR_win32_surface) || defined(_WIN32) || defined(_WIN64)
		inline static VkResult createWin32Surface(VkSurfaceKHR *pSurface, const VkWin32SurfaceCreateInfoKHR *pCreateInfo, const VkAllocationCallbacks *pAllocator = nullptr) {
			return VKFW_DEBUG_VKRESULT(KHR_win32_surfacePFN::vkCreateWin32SurfaceKHR(Hidden::PFN::instance, pCreateInfo, pAllocator, pSurface));
		}
#endif
#endif
	};

	class PhysicalDevice {
		using CorePFN = Hidden::PFN::Core::Instance;
#if VKFW_V_MAJOR >= 1 && VKFW_V_MINOR >= 1
		using Core1_1PFN = Hidden::PFN::Core1_1::Instance;
#endif
#ifdef VKFW_KHR_surface
		using KHR_surfacePFN = Hidden::PFN::KHR_surface::Instance;
#if defined(VKFW_KHR_win32_surface) || defined(_WIN32) || defined(_WIN64)
		using KHR_win32_surfacePFN = Hidden::PFN::KHR_win32_surface::Instance;
#endif
#endif
		VKFW_HANDLE_CHILD(PhysicalDevice, VkPhysicalDevice, m_handle)

		inline VkResult createDevice(VkDevice *pDevice, const VkDeviceCreateInfo *pCreateInfo, const VkAllocationCallbacks *pAllocator = nullptr) const {
			return VKFW_DEBUG_VKRESULT(CorePFN::vkCreateDevice(m_handle, pCreateInfo, pAllocator, pDevice));
		}

		inline VkResult createAndInitDevice(Device &device, const VkDeviceCreateInfo *pCreateInfo, const VkAllocationCallbacks *pAllocator = nullptr) const {
			VkResult result = createDevice(&device, pCreateInfo, pAllocator);
			device.init();
			return result;
		}

		inline VkResult enumerateDeviceExtensionProperties(const char *pLayerName, uint32_t *pPropertyCount, VkExtensionProperties *pProperties) const {
			return VKFW_DEBUG_VKRESULT(CorePFN::vkEnumerateDeviceExtensionProperties(m_handle, pLayerName, pPropertyCount, pProperties));
		}

		inline VkResult enumerateDeviceLayerProperties(uint32_t *pPropertyCount, VkLayerProperties *pProperties) const {
			return VKFW_DEBUG_VKRESULT(CorePFN::vkEnumerateDeviceLayerProperties(m_handle, pPropertyCount, pProperties));
		}

		inline void getProperties(VkPhysicalDeviceProperties *properties) const {
			CorePFN::vkGetPhysicalDeviceProperties(m_handle, properties);
		}

		inline void getQueueFamilyProperties(uint32_t *pQueueFamilyPropertyCount, VkQueueFamilyProperties *pQueueFamilyProperties = nullptr) const {
			CorePFN::vkGetPhysicalDeviceQueueFamilyProperties(m_handle, pQueueFamilyPropertyCount, pQueueFamilyProperties);
		}

		inline void getFeatures(VkPhysicalDeviceFeatures *pFeatures) const {
			CorePFN::vkGetPhysicalDeviceFeatures(m_handle, pFeatures);
		}

		inline void getFormatProperties(VkFormat format, VkFormatProperties *pFormatProperties) const {
			CorePFN::vkGetPhysicalDeviceFormatProperties(m_handle, format, pFormatProperties);
		}

		inline VkResult getImageFormatProperties(VkFormat format, VkImageType type, VkImageTiling tiling,
			VkImageUsageFlags usage, VkImageCreateFlags flags, VkImageFormatProperties *pImageFormatProperties) const {
			return VKFW_DEBUG_VKRESULT(CorePFN::vkGetPhysicalDeviceImageFormatProperties(m_handle, format, type, tiling, usage, flags, pImageFormatProperties));
		}

		inline void getMemoryProperties(VkPhysicalDeviceMemoryProperties *pMemoryProperties) const {
			CorePFN::vkGetPhysicalDeviceMemoryProperties(m_handle, pMemoryProperties);
		}

		inline void getSparseImageFormatProperties(VkFormat format, VkImageType type, VkSampleCountFlagBits samples,
			VkImageUsageFlags usage, VkImageTiling tiling, uint32_t *pPropertyCount, VkSparseImageFormatProperties *pProperties) const {
			CorePFN::vkGetPhysicalDeviceSparseImageFormatProperties(m_handle, format, type, samples, usage, tiling, pPropertyCount, pProperties);
		}

#if VKFW_V_MAJOR >= 1 && VKFW_V_MINOR >= 1
		void getProperties2(VkPhysicalDeviceProperties2 *pProperties) const {
			Core1_1PFN::vkGetPhysicalDeviceProperties2(m_handle, pProperties);
		}

		void getQueueFamilyProperties2(uint32_t *pQueueFamilyPropertyCount,
			VkQueueFamilyProperties2 *pQueueFamilyProperties) const {
			Core1_1PFN::vkGetPhysicalDeviceQueueFamilyProperties2(m_handle, pQueueFamilyPropertyCount, pQueueFamilyProperties);
		}

		void getSparseImageFormatProperties2(const VkPhysicalDeviceSparseImageFormatInfo2* pFormatInfo,
			uint32_t *pPropertyCount,
			VkSparseImageFormatProperties2 *pProperties) const {
			Core1_1PFN::vkGetPhysicalDeviceSparseImageFormatProperties2(m_handle, pFormatInfo, pPropertyCount, pProperties);
		}
#endif

#ifdef VKFW_KHR_surface
		inline VkResult getSurfaceSupport(VkBool32 *pSupported, uint32_t queueFamilyIndex, VkSurfaceKHR surface) const {
			return VKFW_DEBUG_VKRESULT(KHR_surfacePFN::vkGetPhysicalDeviceSurfaceSupportKHR(m_handle, queueFamilyIndex, surface, pSupported));
		}

		inline VkResult getSurfaceCapabilities(VkSurfaceCapabilitiesKHR *pSurfaceCapabilities, VkSurfaceKHR surface) const {
			return VKFW_DEBUG_VKRESULT(KHR_surfacePFN::vkGetPhysicalDeviceSurfaceCapabilitiesKHR(m_handle, surface, pSurfaceCapabilities));
		}

		inline VkResult getSurfaceFormats(VkSurfaceKHR surface, uint32_t *pSurfaceFormatCount, VkSurfaceFormatKHR *pSurfaceFormats = nullptr) const {
			return VKFW_DEBUG_VKRESULT(KHR_surfacePFN::vkGetPhysicalDeviceSurfaceFormatsKHR(m_handle, surface, pSurfaceFormatCount, pSurfaceFormats));
		}

		inline VkResult getSurfacePresentModes(VkSurfaceKHR surface, uint32_t *pPresentModeCount, VkPresentModeKHR *pPresentModes = nullptr) const {
			return VKFW_DEBUG_VKRESULT(KHR_surfacePFN::vkGetPhysicalDeviceSurfacePresentModesKHR(m_handle, surface, pPresentModeCount, pPresentModes));
		}

#if defined(VKFW_KHR_win32_surface) || defined(_WIN32) || defined(_WIN64)
		inline VkBool32 getWin32PresentationSupportKHR(uint32_t queueFamilyIndex) {
			return KHR_win32_surfacePFN::vkGetPhysicalDeviceWin32PresentationSupportKHR(m_handle, queueFamilyIndex);
		}
#endif
#endif
	};

	class Pipeline {
		using CorePFN = Hidden::PFN::Core::Device;
		VKFW_HANDLE_CHILD(Pipeline, VkPipeline, m_handle)
		
		inline void destroy(const VkAllocationCallbacks *pAllocator = nullptr) {
			CorePFN::vkDestroyPipeline(Hidden::PFN::device, m_handle, pAllocator);
		}
	};

	class PipelineCache {
		using CorePFN = Hidden::PFN::Core::Device;
		VKFW_HANDLE_CHILD(PipelineCache, VkPipelineCache, m_handle)

		inline void destroy(const VkAllocationCallbacks *pAllocator = nullptr) {
			CorePFN::vkDestroyPipelineCache(Hidden::PFN::device, m_handle, pAllocator);
		}

		inline VkResult getData(size_t *pDataSize, void *pData) {
			VKFW_DEBUG_VKRESULT(CorePFN::vkGetPipelineCacheData(Hidden::PFN::device, m_handle, pDataSize, pData));
		}

		inline VkResult merge(uint32_t srcCacheCount, const VkPipelineCache *pSrcCaches) {
			VKFW_DEBUG_VKRESULT(CorePFN::vkMergePipelineCaches(Hidden::PFN::device, m_handle, srcCacheCount, pSrcCaches));
		}
	};

	class PipelineLayout {
		using CorePFN = Hidden::PFN::Core::Device;
		VKFW_HANDLE_CHILD(PipelineLayout, VkPipelineLayout, m_handle)

		inline void destroy(const VkAllocationCallbacks *pAllocator = nullptr) {
			CorePFN::vkDestroyPipelineLayout(Hidden::PFN::device, m_handle, pAllocator);
		}
	};

	class QueryPool {
		using CorePFN = Hidden::PFN::Core::Device;
		VKFW_HANDLE_CHILD(QueryPool, VkQueryPool, m_handle)

		inline void destroy(const VkAllocationCallbacks *pAllocator = nullptr) {
			CorePFN::vkDestroyQueryPool(Hidden::PFN::device, m_handle, pAllocator);
		}

		inline VkResult getResults(uint32_t firstQuery, uint32_t queryCount, size_t dataSize, void *pData, VkDeviceSize stride, VkQueryResultFlags flags) {
			VKFW_DEBUG_VKRESULT(CorePFN::vkGetQueryPoolResults(Hidden::PFN::device, m_handle, firstQuery, queryCount, dataSize, pData, stride, flags));
		}
	};

	class Queue {
		using CorePFN = Hidden::PFN::Core::Device;
		VKFW_HANDLE_CHILD(Queue, VkQueue, m_handle)

		inline VkResult bindSparse(uint32_t bindInfoCount, const VkBindSparseInfo *pBindInfo, VkFence fence) {
			return VKFW_DEBUG_VKRESULT(CorePFN::vkQueueBindSparse(m_handle, bindInfoCount, pBindInfo, fence));
		}

		inline VkResult submit(uint32_t submitCount, const VkSubmitInfo *pSubmits, VkFence fence) {
			return VKFW_DEBUG_VKRESULT(CorePFN::vkQueueSubmit(m_handle, submitCount, pSubmits, fence));
		}

		inline VkResult waitIdle() {
			return VKFW_DEBUG_VKRESULT(CorePFN::vkQueueWaitIdle(m_handle));
		}

#ifdef VKFW_KHR_surface
#ifdef VKFW_KHR_swapchain
		inline VkResult present(const VkPresentInfoKHR *pPresentInfo) const {
			return VKFW_DEBUG_VKRESULT(vkQueuePresentKHR(m_handle, pPresentInfo));
		}
#endif
#endif
	};

	class RenderPass {
		using CorePFN = Hidden::PFN::Core::Device;
		VKFW_HANDLE_CHILD(RenderPass, VkRenderPass, m_handle)

		inline void destroy(const VkAllocationCallbacks *pAllocator = nullptr) {
			CorePFN::vkDestroyRenderPass(Hidden::PFN::device, m_handle, pAllocator);
		}

		inline void getGranularity(VkExtent2D *pGranularity) {
			CorePFN::vkGetRenderAreaGranularity(Hidden::PFN::device, m_handle, pGranularity);
		}
	};

	class Sampler {
		using CorePFN = Hidden::PFN::Core::Device;
		VKFW_HANDLE_CHILD(Sampler, VkSampler, m_handle)

		inline void destroy(const VkAllocationCallbacks *pAllocator = nullptr) {
			CorePFN::vkDestroySampler(Hidden::PFN::device, m_handle, pAllocator);
		}
	};

	class Semaphore {
		using CorePFN = Hidden::PFN::Core::Device;
		VKFW_HANDLE_CHILD(Semaphore, VkSemaphore, m_handle)

		inline void destroy(const VkAllocationCallbacks *pAllocator = nullptr) {
			CorePFN::vkDestroySemaphore(Hidden::PFN::device, m_handle, pAllocator);
		}
	};

	class ShaderModule {
		using CorePFN = Hidden::PFN::Core::Device;
		VKFW_HANDLE_CHILD(ShaderModule, VkShaderModule, m_handle)

		inline void destroy(const VkAllocationCallbacks *pAllocator = nullptr) {
			CorePFN::vkDestroyShaderModule(Hidden::PFN::device, m_handle, pAllocator);
		}
	};

#if VKFW_V_MAJOR >= 1 && VKFW_V_MINOR >= 1
	class DescriptorUpdateTemplate {
		using Core1_1PFN = Hidden::PFN::Core1_1::Device;

		VKFW_HANDLE_CHILD(DescriptorUpdateTemplate, VkDescriptorUpdateTemplate, m_handle)

		inline void destroy(const VkAllocationCallbacks *pAllocator = nullptr) {
			Core1_1PFN::vkDestroyDescriptorUpdateTemplate(Hidden::PFN::device, m_handle, pAllocator);
		}
	};

	class SamplerYcbcrConversion {
		using Core1_1PFN = Hidden::PFN::Core1_1::Device;

		VKFW_HANDLE_CHILD(SamplerYcbcrConversion, VkSamplerYcbcrConversion, m_handle)

		inline void destroy(const VkAllocationCallbacks *pAllocator = nullptr) {
			Core1_1PFN::vkDestroySamplerYcbcrConversion(Hidden::PFN::device, m_handle, pAllocator);
		}
	};
#endif

#ifdef VKFW_KHR_surface
	class SurfaceKhr {
		using KHR_surfacePFN = Hidden::PFN::KHR_surface::Instance;
		VKFW_HANDLE_CHILD(SurfaceKhr, VkSurfaceKHR, m_handle)
		
		inline void destroy(const VkAllocationCallbacks *pAllocator = nullptr) {
			KHR_surfacePFN::vkDestroySurfaceKHR(Hidden::PFN::instance, m_handle, pAllocator);
		}
	};

#ifdef VKFW_KHR_swapchain
	class SwapchainKhr {
		using KHR_swapchainPFN = Hidden::PFN::KHR_swapchain::Device;
		VKFW_HANDLE_CHILD(SwapchainKhr, VkSwapchainKHR, m_handle)

		inline VkResult acquireNextImage(uint32_t *pImageIndex, uint64_t timeout, VkSemaphore semaphore, VkFence fence) const {
			return VKFW_DEBUG_VKRESULT(KHR_swapchainPFN::vkAcquireNextImageKHR(Hidden::PFN::device, m_handle, timeout, semaphore, fence, pImageIndex));
		}

		inline VkResult acquireNextImageWithSemaphore(uint32_t *pImageIndex, VkSemaphore semaphore, uint64_t timeout = 0) const {
			return VKFW_DEBUG_VKRESULT(KHR_swapchainPFN::vkAcquireNextImageKHR(Hidden::PFN::device, m_handle, timeout, semaphore, VK_NULL_HANDLE, pImageIndex));
		}

		inline VkResult acquireNextImageWithFence(uint32_t *pImageIndex, VkFence fence, uint64_t timeout = 0) const {
			return VKFW_DEBUG_VKRESULT(KHR_swapchainPFN::vkAcquireNextImageKHR(Hidden::PFN::device, m_handle, timeout, VK_NULL_HANDLE, fence, pImageIndex));
		}

		inline void destroy(const VkAllocationCallbacks *pAllocator = nullptr) {
			KHR_swapchainPFN::vkDestroySwapchainKHR(Hidden::PFN::device, m_handle, pAllocator);
		}

		inline VkResult getImages(uint32_t *pSwapchainImageCount, VkImage *pSwapchainImages = nullptr) const {
			return VKFW_DEBUG_VKRESULT(KHR_swapchainPFN::vkGetSwapchainImagesKHR(Hidden::PFN::device, m_handle, pSwapchainImageCount, pSwapchainImages));
		}
	};
#endif
#endif
}

#pragma pop_macro("VKFW_DEBUG_VKRESULT")
#pragma pop_macro("VKFW_HANDLE_CHILD")
#pragma pop_macro("VKFW_HANDLE_PARENT")
#pragma pop_macro("VKFW_HANDLE")
#pragma pop_macro("VKFW_SET_STYPE")

#ifdef VKFW_KHR_surface
#if defined(VKFW_KHR_win32_surface) || defined(_WIN32) || defined(_WIN64)
#pragma pop_macro("VK_USE_PLATFORM_WIN32_KHR")
#pragma pop_macro("WIN32_LEAN_AND_MEAN")
#endif
#endif