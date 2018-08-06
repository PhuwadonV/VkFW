#pragma once
#include <memory>
#include <vector>

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

#pragma push_macro("VKFW_SET_STYPE")
#define VKFW_SET_STYPE(Type, val)				\
	inline Type& setSType(Type &ref) {			\
		ref.sType =  VK_STRUCTURE_TYPE_##val;	\
		return ref;								\
	}

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
		return vkCreateInstance(pCreateInfo, pAllocator, pInstance);
	}

	inline VkResult enumerateInstanceExtensionProperties(const char *pLayerName, uint32_t *pPropertyCount, VkExtensionProperties *pProperties = nullptr) {
		return vkEnumerateInstanceExtensionProperties(pLayerName, pPropertyCount, pProperties);
	}

	inline VkResult enumerateInstanceLayerProperties(uint32_t *pPropertyCount, VkLayerProperties *pProperties = nullptr) {
		return vkEnumerateInstanceLayerProperties(pPropertyCount, pProperties);
	}

#if VKFW_V_MAJOR >= 1 && VKFW_V_MINOR >= 1
	inline VkResult enumerateInstanceVersion(uint32_t *pApiVersion) {
		return vkEnumerateInstanceVersion(pApiVersion);
	}
#endif

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

#if VKFW_V_MAJOR >= 1 && VKFW_V_MINOR >= 1
			inline static typename FnType<decltype(vkGetPhysicalDeviceProperties2)>::Eval vkGetPhysicalDeviceProperties2;
			inline static typename FnType<decltype(vkGetPhysicalDeviceQueueFamilyProperties2)>::Eval vkGetPhysicalDeviceQueueFamilyProperties2;
			inline static typename FnType<decltype(vkEnumeratePhysicalDeviceGroups)>::Eval vkEnumeratePhysicalDeviceGroups;
#endif
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

#if VKFW_V_MAJOR >= 1 && VKFW_V_MINOR >= 1
				getInstanceProcAddr(handle, "vkGetPhysicalDeviceProperties2", vkGetPhysicalDeviceProperties2);
				getInstanceProcAddr(handle, "vkGetPhysicalDeviceQueueFamilyProperties2", vkGetPhysicalDeviceQueueFamilyProperties2);
				getInstanceProcAddr(handle, "vkEnumeratePhysicalDeviceGroups", vkEnumeratePhysicalDeviceGroups);
#endif
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

	class Exception {
		const char *m_msg;
	public:
		Exception(const char *msg) : m_msg(msg) {}

		virtual const char* getMsg() const {
			return m_msg;
		}
	};

	class ResultException : public Exception {
		VkResult m_result;
	public:
		static ResultException* New(VkResult result) {
			const char *msg = "Unknown Error";
			switch (result)
			{
			case VK_ERROR_OUT_OF_HOST_MEMORY: msg = "VK_ERROR_OUT_OF_HOST_MEMORY";
			case VK_ERROR_OUT_OF_DEVICE_MEMORY: msg = "VK_ERROR_OUT_OF_DEVICE_MEMORY";
			case VK_ERROR_INITIALIZATION_FAILED: msg = "VK_ERROR_INITIALIZATION_FAILED";
			case VK_ERROR_DEVICE_LOST: msg = "VK_ERROR_DEVICE_LOST";
			case VK_ERROR_MEMORY_MAP_FAILED: msg = "VK_ERROR_MEMORY_MAP_FAILED";
			case VK_ERROR_LAYER_NOT_PRESENT: msg = "VK_ERROR_LAYER_NOT_PRESENT";
			case VK_ERROR_EXTENSION_NOT_PRESENT: msg = "VK_ERROR_EXTENSION_NOT_PRESENT";
			case VK_ERROR_FEATURE_NOT_PRESENT: msg = "VK_ERROR_FEATURE_NOT_PRESENT";
			case VK_ERROR_INCOMPATIBLE_DRIVER: msg = "VK_ERROR_INCOMPATIBLE_DRIVER";
			case VK_ERROR_TOO_MANY_OBJECTS: msg = "VK_ERROR_TOO_MANY_OBJECTS";
			case VK_ERROR_FORMAT_NOT_SUPPORTED: msg = "VK_ERROR_FORMAT_NOT_SUPPORTED";
			case VK_ERROR_FRAGMENTED_POOL: msg = "VK_ERROR_FRAGMENTED_POOL";
			case VK_ERROR_OUT_OF_POOL_MEMORY: msg = "VK_ERROR_OUT_OF_POOL_MEMORY";
			case VK_ERROR_INVALID_EXTERNAL_HANDLE: msg = "VK_ERROR_INVALID_EXTERNAL_HANDLE";
			case VK_ERROR_SURFACE_LOST_KHR: msg = "VK_ERROR_SURFACE_LOST_KHR";
			case VK_ERROR_NATIVE_WINDOW_IN_USE_KHR: msg = "VK_ERROR_NATIVE_WINDOW_IN_USE_KHR";
			case VK_SUBOPTIMAL_KHR: msg = "VK_SUBOPTIMAL_KHR";
			case VK_ERROR_OUT_OF_DATE_KHR: msg = "VK_ERROR_OUT_OF_DATE_KHR";
			case VK_ERROR_INCOMPATIBLE_DISPLAY_KHR: msg = "VK_ERROR_INCOMPATIBLE_DISPLAY_KHR";
			}
			return new ResultException(result, msg);
		}

		ResultException(VkResult result, const char *msg) : Exception(msg), m_result(result) {}

		VkResult getVkResult() const {
			return m_result;
		}
	};

	namespace Hidden {
		VkResult vkResultAssert(VkResult result) {
			if (result >= 0) return result;
			switch (result)
			{
			case VK_ERROR_OUT_OF_HOST_MEMORY: throw new ResultException(result, "VK_ERROR_OUT_OF_HOST_MEMORY");
			case VK_ERROR_OUT_OF_DEVICE_MEMORY: throw new ResultException(result, "VK_ERROR_OUT_OF_DEVICE_MEMORY");
			case VK_ERROR_INITIALIZATION_FAILED: throw new ResultException(result, "VK_ERROR_INITIALIZATION_FAILED");
			case VK_ERROR_DEVICE_LOST: throw new ResultException(result, "VK_ERROR_DEVICE_LOST");
			case VK_ERROR_MEMORY_MAP_FAILED: throw new ResultException(result, "VK_ERROR_MEMORY_MAP_FAILED");
			case VK_ERROR_LAYER_NOT_PRESENT: throw new ResultException(result, "VK_ERROR_LAYER_NOT_PRESENT");
			case VK_ERROR_EXTENSION_NOT_PRESENT: throw new ResultException(result, "VK_ERROR_EXTENSION_NOT_PRESENT");
			case VK_ERROR_FEATURE_NOT_PRESENT: throw new ResultException(result, "VK_ERROR_FEATURE_NOT_PRESENT");
			case VK_ERROR_INCOMPATIBLE_DRIVER: throw new ResultException(result, "VK_ERROR_INCOMPATIBLE_DRIVER");
			case VK_ERROR_TOO_MANY_OBJECTS: throw new ResultException(result, "VK_ERROR_TOO_MANY_OBJECTS");
			case VK_ERROR_FORMAT_NOT_SUPPORTED: throw new ResultException(result, "VK_ERROR_FORMAT_NOT_SUPPORTED");
			case VK_ERROR_FRAGMENTED_POOL: throw new ResultException(result, "VK_ERROR_FRAGMENTED_POOL");
			case VK_ERROR_OUT_OF_POOL_MEMORY: throw new ResultException(result, "VK_ERROR_OUT_OF_POOL_MEMORY");
			case VK_ERROR_INVALID_EXTERNAL_HANDLE: throw new ResultException(result, "VK_ERROR_INVALID_EXTERNAL_HANDLE");
			case VK_ERROR_SURFACE_LOST_KHR: throw new ResultException(result, "VK_ERROR_SURFACE_LOST_KHR");
			case VK_ERROR_NATIVE_WINDOW_IN_USE_KHR: throw new ResultException(result, "VK_ERROR_NATIVE_WINDOW_IN_USE_KHR");
			case VK_SUBOPTIMAL_KHR: throw new ResultException(result, "VK_SUBOPTIMAL_KHR");
			case VK_ERROR_OUT_OF_DATE_KHR: throw new ResultException(result, "VK_ERROR_OUT_OF_DATE_KHR");
			case VK_ERROR_INCOMPATIBLE_DISPLAY_KHR: throw new ResultException(result, "VK_ERROR_INCOMPATIBLE_DISPLAY_KHR");
			default: throw new ResultException(result, "Unknown Error");
			}
		}
	}

	class PhysicalDevice;

	class Instance {
		std::shared_ptr<VkInstance> m_handle;
		std::shared_ptr<Hidden::PFN::Core::Instance> m_pfn;
	public:
		static Instance New(const VkInstanceCreateInfo *pCreateInfo, const VkAllocationCallbacks *pAllocator = nullptr) {
			VkInstance handle;
			Hidden::vkResultAssert(createInstance(&handle, pCreateInfo, pAllocator));
			return Instance(handle);
		}

		Instance() = default;

		Instance(VkInstance handle) : m_handle(std::make_shared<VkInstance>(handle)), m_pfn(std::make_shared<Hidden::PFN::Core::Instance>()) {
			m_pfn->init(handle);
		}

		void destroy(const VkAllocationCallbacks *pAllocator = nullptr) {
			m_pfn->vkDestroyInstance(*m_handle, pAllocator);
		}
		
		VkResult enumeratePhysicalDevices(uint32_t *pPhysicalDeviceCount, PhysicalDevice *pPhysicalDevices = nullptr);
	};

	class PhysicalDevice {
		std::shared_ptr<VkPhysicalDevice> m_handle;
		std::shared_ptr<VkInstance> m_parent;
		std::shared_ptr<Hidden::PFN::Core::Instance> m_pfn;
	public:
		PhysicalDevice() = default;

		PhysicalDevice(VkPhysicalDevice handle, std::shared_ptr<VkInstance> parent, std::shared_ptr<Hidden::PFN::Core::Instance> pfn) : m_handle(std::make_shared<VkPhysicalDevice>(handle)), m_parent(parent), m_pfn(pfn) {}

		void getProperties(VkPhysicalDeviceProperties *properties) const {
			m_pfn->vkGetPhysicalDeviceProperties(*m_handle, properties);
		}
	};

	VkResult Instance::enumeratePhysicalDevices(uint32_t *pPhysicalDeviceCount, PhysicalDevice *pPhysicalDevices) {
		if (pPhysicalDevices == nullptr) return Hidden::vkResultAssert(m_pfn->vkEnumeratePhysicalDevices(*m_handle, pPhysicalDeviceCount, nullptr));
		else {
			std::vector<VkPhysicalDevice> phyDevs(*pPhysicalDeviceCount);
			VkResult result = Hidden::vkResultAssert(m_pfn->vkEnumeratePhysicalDevices(*m_handle, pPhysicalDeviceCount, phyDevs.data()));
			for (uint32_t i = 0; i < *pPhysicalDeviceCount; i++) {
				pPhysicalDevices[i] = PhysicalDevice(phyDevs[i], m_handle, m_pfn);
			}
			return result;
		}
	}

#ifdef VKFW_KHR_surface
#if defined(VKFW_KHR_win32_surface) || defined(_WIN32) || defined(_WIN64)
	/*class Instance {
		std::shared_ptr<VkInstance> m_handle;
		std::shared_ptr<Hidden::PFN::Core::Instance> m_pfn;
	public:
		static Instance New(const VkInstanceCreateInfo *pCreateInfo, const VkAllocationCallbacks *pAllocator = nullptr) {
			VkInstance handle;
			Hidden::vkResultAssert(createInstance(&handle, pCreateInfo, pAllocator));
			return Instance(handle);
		}

		Instance() = default;

		Instance(VkInstance handle) : m_handle(std::make_shared<VkInstance>(handle)), m_pfn(std::make_shared<Hidden::PFN::Core::Instance>()) {
			m_pfn->init(handle);
		}

		inline static VkResult createWin32Surface(VkSurfaceKHR *pSurface, const VkWin32SurfaceCreateInfoKHR *pCreateInfo, const VkAllocationCallbacks *pAllocator = nullptr) {
			return VKFW_DEBUG_VKRESULT(KHR_win32_surfacePFN::vkCreateWin32SurfaceKHR(Hidden::PFN::instance, pCreateInfo, pAllocator, pSurface));
		}
	};

	*/
#endif
#endif
}

#pragma pop_macro("VKFW_SET_STYPE")

#ifdef VKFW_KHR_surface
#if defined(VKFW_KHR_win32_surface) || defined(_WIN32) || defined(_WIN64)
#pragma pop_macro("VK_USE_PLATFORM_WIN32_KHR")
#pragma pop_macro("WIN32_LEAN_AND_MEAN")
#endif
#endif